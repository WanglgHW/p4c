# Doc 03 — MILP / BILP Formulation (the core model)

This is the mathematical heart of the project. Each sub-model (M1 PHV, M2
MAU/memory, M3 VLIW/action) is given with: **sets**, **parameters** (with the
exact Tofino spec constant and source), **decision variables**, **objective**,
and **constraints as explicit linear (in)equalities**. All constraints are
linear in binary/integer variables ⇒ the problem is a Mixed-Integer Linear
Program; the assignment cores are Binary ILP.

Spec constants (Doc 01) are referenced symbolically so the model is
device-portable; their Tofino-1 values are in `model-minizinc/include/ralloc/device_spec.h`.

---

## 1. Common notation

- Binary variables written `x ∈ {0,1}`. Integers `y ∈ ℤ₊`. Continuous `z ∈ ℝ₊`.
- `[[P]]` = 1 if predicate P holds at model-build time (a parameter), else 0.
- `𝟙[cond]` indicator constraint, linearized in §8.
- Gress set `R = {ingress, egress}` (and `ghost` on T2).

Device-spec symbols (values for Tofino-1):

| Symbol | Meaning | Value | Spec |
|---|---|---|---|
| `NSTAGE` | MAU stages | 12 | `device.h getNumStages()` |
| `NLID` | logical ids/stage | 16 | `MAX_LOGICAL_IDS` |
| `NSRAM` | SRAMs/stage | 80 | `MAX_SRAMS` |
| `NTCAM` | TCAMs/stage | 24 | `MAX_TCAMS` |
| `NMAP` | map RAMs/stage | 48 | `MAX_MAPRAMS` |
| `NXB` | exact ixbar bytes/stage | 128 | `MAX_IXBAR_BYTES` |
| `NTXB` | ternary ixbar groups/stage | 12 | `MAX_TERNARY_GROUPS` |
| `NSTATS` | stats ALUs/stage | 4 | `MAX_STATS_ALUS` |
| `NMETER` | meter ALUs/stage | 4 | `MAX_METER_ALUS` |
| `NHASHB` | hash bits/stage | 52 | `MAX_HASH_BITS` |
| `NHASHG` | hash groups/stage | 8 | `HASH_GROUPS` |
| `NGW` | gateways/stage | 16 | `GATEWAYS_PER_ROW`×rows |
| `IMROW` | imem rows/gress/stage | 32 | `TofinoIMemSpec::rows()` |
| `IMCOL` | imem colors/row | 2 | `colors()` |
| `W_T` | PHV container widths | {8,16,32} | `PHV::Size` |

---

## 2. Model M0 — parameter ingestion (not an optimization)

M0 builds the index sets and parameter tables from the IR (Doc 04). Outputs:
- `S` field slices, with width `w(s)`, kind requirement `kind(s)`, live range
  `lr(s)=[lo,hi]`, alignment requirement `align(s)`, and reference flags.
- mutex/overlay relation `MUTEX ⊆ S×S`; pack-conflict relation `CONF ⊆ S×S`.
- `T` (stage-)tables with **layout-option columns** `O(t)` (each option = a
  concrete `LayoutOption` with a demand vector).
- `A` actions with written-container-set proxies; action-data fields.
- dependency edges `DEP ⊆ T×T` with min-stage-gap `g(a,b)∈{0,1}`.

---

## 3. Model M1 — PHV allocation (Binary ILP)

### 3.1 Sets & parameters

- `S` = field slices to place; `C` = physical containers.
- `kindOK(s,c) ∈ {0,1}` : container `c`'s kind/size legal for slice `s`
  (encodes P2, P7, P10). Param from `phv.cpp` + pragmas.
- `w(s)` slice width; `cap(c)` container width ∈ {8,16,32}.
- `MUTEX(s,s')`, `CONF(s,s')` (P4, P5).
- `align(s) ∈ {⊥} ∪ {0..cap-1}` required start offset (P6); `byteAlign(s)∈{0,1}`.
- `grp(c)` MAU group of `c`; `Bgrp` the per-group container count.
- For action reachability (P11): `srcReach(s,c) ∈ {0,1}` = can the ALU of
  container `c` source all operands needed to produce `s` (precomputed from the
  action-source graph). If 0, `c` is forbidden for `s`.

### 3.2 Variables

```
x[s,c]     ∈ {0,1}   slice s assigned to container c
p[s,c,o]   ∈ {0,1}   slice s at bit-offset o within container c   (o = 0..cap(c)-w(s))
u[c]       ∈ {0,1}   container c is used (any slice)
```
`p` is only instantiated for offsets allowed by `align(s)` and byte-alignment,
which keeps it small.

### 3.3 Objective (default O2 + tie-breaks)

```
min  Σ_c u[c]                              (minimize containers used)
     + λ1 Σ_{s,c} costGroupSpread(s,c)·x[s,c]   (keep a table's key in few groups → helps C1)
     + λ2 Σ_{s,c} tphvPref(s,c)·x[s,c]          (prefer T-PHV for deparse-only fields)
```
with `0 < λ2 ≪ λ1 ≪ 1`.

### 3.4 Constraints

**(P1) assignment** — every referenced slice placed once:
```
Σ_c x[s,c] = 1                                   ∀ s ∈ S            (1)
```
**(link x,p)**:
```
Σ_o p[s,c,o] = x[s,c]                             ∀ s, c             (2)
```
**(P2/P7/P10) legality**:
```
x[s,c] ≤ kindOK(s,c)·srcReach(s,c)               ∀ s, c             (3)
```
**(P3 + P4) no bit overlap unless overlay-legal** — for every container `c`,
bit `b`, and time-overlapping non-mutex slice pair, at most one occupies bit `b`:
```
Σ_{s: b∈covered(s,o)}  p[s,c,o]  ≤ 1
                 ∀ c, ∀ b∈[0,cap(c)), restricted to a clique of pairwise
                 NON-overlay-compatible slices                         (4)
```
Practically: enumerate, per container, the conflict graph among candidate slices
(edges = not MUTEX and not physical-disjoint), and add a clique/edge cover. Edge
form:
```
p[s,c,o] + p[s',c,o'] ≤ 1   ∀ (s,s')∉MUTEX with bit-overlap at (o,o'), ∀c   (4')
```
**(P5) pack conflict** (cannot co-reside in a container at all):
```
x[s,c] + x[s',c] ≤ 1            ∀ (s,s')∈CONF, ∀ c                    (5)
```
**(P6) alignment** — only offsets in `align(s)` instantiated; for byte-aligned:
```
p[s,c,o] = 0   for all o with (o mod 8) ≠ 0   (when byteAlign(s)=1)   (6)
```
**(u link)**:
```
u[c] ≥ x[s,c]                  ∀ s, c                                 (7)
```
**(P8/C1) crossbar-group locality (soft via objective, hard option)** — if a set
`K(t)` of slices forms a table key that must fit `≤ Γ` crossbar groups, introduce
`g[t,grp]∈{0,1}` (group used by table t):
```
x[s,c] ≤ g[t, grp(c)]          ∀ t, s∈K(t), c
Σ_grp g[t,grp] ≤ Γ(t)                                                 (8)
```
**(P12) parser-extractor balance** — per parser state `ps`, per extractor class
`e`, the number of containers extracted ≤ budget `Ext(e)`:
```
Σ_{s∈extract(ps), c∈class(e)} x[s,c] ≤ Ext(e)·something … (see Doc 04 §2)  (9)
```

### 3.5 Outputs of M1 (parameters into M2/M3)

- `containerOf(s)` → AllocSlice (write-back, Doc 06).
- `xbarBytes(t)` = the (group,byte) ordinates reachable for each table key →
  feeds M2 constraint set T8/T9 (coupling C1).
- per-action written-container set → feeds M3 (coupling C2).

---

## 4. Model M2 — MAU placement + memory (MILP)

This is the most important sub-model. It decides **stage**, **logical id**, and
**which layout option** per table, subject to all per-stage budgets.

### 4.1 Sets & parameters

- `T` stage-tables; `G = {0..NSTAGE-1}` stages; `R` gresses; `gress(t)∈R`.
- `O(t)` = layout options of table `t` (from `LayoutChoices`, Doc 04 §3). Each
  option `o` carries a **demand vector**
  `d[t,o] = (srams, tcams, maprams, xbar_bytes, tern_groups, stats_alus,
  meter_alus, logical_ids, hash_bits, hash_groups, gateways)` taken from
  `StageUseEstimate` (`resource_estimate.h`).
- `split(t)` = max stage-tables table may be split into (`stages_required()`).
- `DEP ⊆ T×T` dependency edges with gap `g(a,b)∈{0,1}` (match-dep ⇒ 1,
  action-dep handled by imem, control-dep ⇒ 0 but same-or-later).
- `mutexTbl(t,t')` tables mutually exclusive ⇒ may share a logical id slot region.

### 4.2 Variables

```
s[t,o,k]   ∈ {0,1}   table t uses layout option o and is placed in stage k
y[t,k]     ∈ {0,1}   table t (any option) occupies stage k          (= Σ_o s[t,o,k])
useStage[k]∈ {0,1}   stage k used by any table
lid[t,k]   ∈ {0,1}   (optional, for exact id assignment / symmetry off)
```
For a split table, `y[t,k]` may be 1 for several consecutive `k`; a "primary
stage" `first[t]` variable orders them.

### 4.3 Objective

```
min  W_stage · Σ_k useStage[k]            (O1 minimize stages = latency)
   + W_pow   · Σ_{t,o,k} pow(t,o)·s[t,o,k]   (O3 power)
   + W_bal   · (max-stage-pressure slack)     (O4 spread)
```
`W_stage ≫ W_pow ≫ W_bal` for lexicographic behavior, or use staged lexicographic re-solves (Doc 05 §5).

### 4.4 Constraints

**(T1) one option, placed) — non-split tables:**
```
Σ_{o∈O(t)} Σ_{k∈G} s[t,o,k] = 1            ∀ t (non-split)           (10)
```
For split-capable tables, replace with: select one option, then place its
`parts(t,o)` stage-tables in distinct consecutive stages:
```
Σ_o z[t,o] = 1                                                          (10a)
Σ_k y[t,k] = Σ_o parts(t,o)·z[t,o]                                      (10b)
y consecutive in k  (ordering constraints, §8.3)                       (10c)
```
**(define y, useStage):**
```
y[t,k] = Σ_o s[t,o,k]                       ∀ t,k                      (11)
useStage[k] ≥ y[t,k]                         ∀ t,k                      (12)
```
**(T2) logical-id capacity:**
```
Σ_t y[t,k] ≤ NLID                            ∀ k                       (13)
```
**(T5) SRAM capacity:**
```
Σ_{t,o} srams(t,o)·s[t,o,k] ≤ NSRAM          ∀ k                       (14)
```
**(T6) TCAM capacity:**
```
Σ_{t,o} tcams(t,o)·s[t,o,k] ≤ NTCAM          ∀ k                       (15)
```
**(T7) map-RAM capacity:**
```
Σ_{t,o} maprams(t,o)·s[t,o,k] ≤ NMAP         ∀ k                       (16)
```
**(T8) exact ixbar bytes** — uses C1 parameter (bytes can be shared by tables
reading the same PHV byte; introduce `xb[k,β]∈{0,1}` = crossbar byte β used in
stage k):
```
s[t,o,k] ≤ xb[k,β]     ∀ k,t,o, β∈keyBytes(t,o)                        (17a)
Σ_β xb[k,β] ≤ NXB                            ∀ k                       (17b)
```
(If byte-sharing is not modeled, use the simpler sum form like (14) with
`xbar_bytes(t,o)`.)
**(T9) ternary ixbar groups:**
```
Σ_{t,o} tern_groups(t,o)·s[t,o,k] ≤ NTXB     ∀ k                       (18)
```
**(T10) stats / meter ALUs:**
```
Σ_{t,o} stats_alus(t,o)·s[t,o,k] ≤ NSTATS    ∀ k                       (19)
Σ_{t,o} meter_alus(t,o)·s[t,o,k] ≤ NMETER    ∀ k                       (20)
```
**(T11) hash:**
```
Σ_{t,o} hash_bits(t,o)·s[t,o,k] ≤ NHASHB     ∀ k                       (21)
Σ_{t,o} hash_groups(t,o)·s[t,o,k] ≤ NHASHG   ∀ k                       (22)
```
**(T12) gateways:**
```
Σ_{t,o} gateways(t,o)·s[t,o,k] ≤ NGW         ∀ k                       (23)
```
**(T3) dependencies** — table `a` depends on `b` with gap `g`:
```
Σ_k k·firstStage(a) ≥ Σ_k k·lastStage(b) + g(b,a)     ∀ (b,a)∈DEP     (24)
```
where `firstStage(a)=Σ_k k·y'[a,k]` with `y'` the indicator of the *first* stage
of `a` (and `lastStage` the last); for non-split tables both equal the unique
placed stage `Σ_k k·y[a,k]`.
**(T13) split sizing** is encoded by option `parts(t,o)` (10a–10c).
**(T14) attached co-residence:** the attached unit's demand is *already folded
into* the match table's option demand vector (Doc 04 §3), so no extra variable —
except for *shared/indirect* attached tables, modeled as their own `t` with a
same-stage equality `Σ_k k·y[att,k] = Σ_k k·y[host,k]`.

### 4.5 Optional fine memory model (M2-fine)

When exact cell placement is wanted in-model (else delegate to
`Memories::allocate_all`): per stage introduce `r[t,row,col]∈{0,1}` over the
8×10 SRAM grid with:
```
Σ_{row,col} r[t,row,col] = srams(t,chosen o)            (per placed table)
Σ_t r[t,row,col] ≤ 1                                     (one owner per cell)
side / bus / swbox-row constraints from M5b–M5e (Doc 02 §3)
```
This is a 2-D packing extension; default OFF (Doc 05 §3).

---

## 5. Model M3 — VLIW / action allocation (Binary ILP, per stage×gress)

Solved **independently for each (stage k, gress r)** after M2 fixes which
actions are active there ⇒ tiny models (≤ a few hundred binaries each).

### 5.1 Sets & parameters

- `A_kr` = actions active in (k,r). `Wr(a) ⊆ ALUs` = set of PHV containers (ALUs)
  written by action `a` (from M1/instruction selection).
- `share(a,a') = 1` iff identical opcodes (V4) ⇒ can co-map to the *same* row+color.
- action-data fields with slot size `slot(f)∈{1,2,4}` bytes and bus class.

### 5.2 Variables

```
rrow[a,ρ]   ∈ {0,1}   action a placed on imem row ρ (ρ=0..IMROW-1)
rcol[a,ρ,γ] ∈ {0,1}   action a on row ρ color γ (γ=0..IMCOL-1)
slot[f,β]   ∈ {0,1}   action-data field f on bus byte β
```

### 5.3 Objective: feasibility (constant) or minimize rows used.

### 5.4 Constraints

**(V1) one placement:**
```
Σ_{ρ,γ} rcol[a,ρ,γ] = 1                        ∀ a∈A_kr               (25)
```
**(V2)+(V3) color disjointness & capacity** — two actions on the same (row,color)
forbidden; on the same row different colors only if ALU-disjoint:
```
Σ_a rcol[a,ρ,γ] ≤ 1                            ∀ ρ,γ                  (26)
rcol[a,ρ,γ] + rcol[a',ρ,γ'] ≤ 1
        ∀ ρ, ∀ (a,a') with Wr(a)∩Wr(a')≠∅ and ¬share(a,a'), ∀ γ,γ'   (27)
```
(27) reduces to "two ALU-overlapping actions cannot share a row at all" — exactly
the imem coloring rule (`instruction_memory.h:70`).
**Row count** is automatically ≤ IMROW because `ρ∈{0..31}`.
**(V4) sharing:** identical actions may be forced equal `rcol[a,·]=rcol[a',·]`.
**(V5) action-data bus:**
```
Σ_β slot[f,β] = slot(f)            (field occupies slot(f) consecutive bytes) (28)
Σ_f [β∈span(f)]·slot[f,β] ≤ 1      ∀ β   (no byte double-booked)             (29)
β ≤ BUSWIDTH                                                                  (30)
```
**(V6) action format** alignment: `slot[f,β]=0` for offsets β incompatible with
the consuming ALU input (parameter from `action_format.cpp`).
**(V7) stateful caps** enforced as `≤ StatefulAluSpec.MaxInstructions` etc. on the
counts of stateful actions in (k,r).

If M3 for some (k,r) is infeasible → emit a **no-good cut** on the offending
action set back to M2 (coupling C5, Doc 05 §5).

---

## 6. Worked micro-example (sanity check of the formulas)

2 tables `t1`(exact, 1 option: 3 srams, 6 xbar B, 0 tcam), `t2`(ternary, 1
option: 2 tcam, 1 tern grp), dependency `t2` matches on `t1`'s action ⇒ gap 1,
NSTAGE=2. Variables `s[t1,o,k], s[t2,o,k]` for k∈{0,1}.
- (10): `s[t1,o,0]+s[t1,o,1]=1`, same for t2.
- (24): `1·s[t2,o,1] (=stage of t2) ≥ stage(t1)+1` ⇒ forces t1→stage0, t2→stage1.
- (14) per stage trivially satisfied (3≤80, 0≤80).
- Objective Σ useStage = 2. Optimal, matches hand placement. ✓

---

## 7. Why BILP / MILP (not LP, not CP-only)

- Assignment, packing, coloring, and "uses a stage" are inherently **0/1** ⇒
  Binary ILP. Every variable is binary and every coefficient integral, so the
  model is a **pure integer program** — exactly the shape OR-Tools CP-SAT solves
  natively (no LP relaxation or rounding needed).
- Capacities and dependencies are **linear** in those binaries ⇒ a linear integer
  program. CP-SAT combines CP propagation with LP relaxation and cutting planes
  internally, which is strong on these knapsack/assignment structures.
- The few genuinely combinatorial sub-structures (imem coloring, 2-D RAM
  packing) are kept **small** (per-stage) so even their integer cores solve fast.

---

## 8. Linearization & symmetry-breaking toolbox

- **Indicator `𝟙[Σ a_i x_i ≥ b] = z`**: big-M `Σ a_i x_i ≥ b·z`,
  `Σ a_i x_i ≤ b-1+M·z`. MiniZinc expresses this directly as a reified
  implication `(z = 1) -> (Σ a_i x_i ≥ b)`, which CP-SAT enforces natively —
  preferred (no big-M tuning).
- **`firstStage`/`lastStage`** (24): introduce `fk[t,k]` with
  `Σ_k fk[t,k]=1`, `fk[t,k] ≤ Σ_{k'≤k} y[t,k']`, `Σ_k k·fk = firstStage`.
- **Stage symmetry:** stages are *not* interchangeable (dependencies + earlier =
  better), so little symmetry. **Logical-id symmetry within a stage** is broken
  by *not* modeling explicit ids (use only counts, T2) — exact ids are assigned
  trivially post-solve.
- **Container symmetry within a MAU group:** containers of the same size in the
  same group are interchangeable ⇒ add lexicographic `u[c] ≥ u[c']` for c<c' in a
  group, or model "k-th used container of group" counts (Doc 05 §3.2).

---

## 9. Optional extensions (research / future)

1. **Global fused model** M1∪M2∪M3 with all couplings as real constraints —
   solvable for small programs, gives provably optimal joint allocation; used as
   ground truth to validate the decomposition's optimality gap.
2. **Parser/CLOT** allocation as an additional knapsack sub-model.
3. **Power as hard constraint** using `MauPowerSpec` per-stage RAM-access budget.
4. **Robust/parametric** allocation: leave PHV headroom to survive program edits.

All formulas above are implemented by the builders in `model-minizinc/src/model/*`
against the parameter API of Doc 04 and emitted to MiniZinc/CP-SAT via Doc 05.
