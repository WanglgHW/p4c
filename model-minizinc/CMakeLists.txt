# ralloc — Tofino resource allocator (Doc 07 §3), MiniZinc + OR-Tools edition
#
# Builds two libraries:
#   libralloc         — solver-agnostic model core + MiniZinc backend (NO bf-p4c deps)
#   libralloc_bridge  — IR <-> model translation (links bf-p4c IR), built only
#                       when configured inside the p4c tree.
#
# The solver is MiniZinc driving Google OR-Tools CP-SAT. MiniZinc is invoked as
# an external process at runtime, so there is NO build- or link-time solver
# dependency: just build, then ensure a `minizinc` binary with a CP-SAT backend
# is on $PATH (override with $RALLOC_MINIZINC / $RALLOC_MINIZINC_SOLVER).
#
# Standalone use:
#   cmake -S model-minizinc -B model-minizinc/build
#   cmake --build model-minizinc/build
#
# In-tree use: add `add_subdirectory(model-minizinc)` to the top-level
# CMakeLists and link `ralloc_bridge` into the `tofinobackend` target.

cmake_minimum_required(VERSION 3.16)
project(ralloc LANGUAGES CXX)

if(NOT DEFINED CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 17)
  set(CMAKE_CXX_STANDARD_REQUIRED ON)
endif()

# ---- MiniZinc (runtime dependency only) -----------------------------------
# The backend shells out to `minizinc`; nothing to find or link at build time.
# This lookup is purely informational (a friendly configure-time warning).
find_program(MINIZINC_EXECUTABLE minizinc)
if(MINIZINC_EXECUTABLE)
  message(STATUS "ralloc: found minizinc at ${MINIZINC_EXECUTABLE} — CP-SAT solving enabled")
else()
  message(STATUS "ralloc: minizinc not found on PATH — .mzn export only until installed")
endif()

# ---- core library (no compiler dependency) --------------------------------
add_library(ralloc
  src/model/device_spec.cpp
  src/model/phv_model.cpp
  src/model/mau_model.cpp
  src/model/vliw_model.cpp
  src/model/resource_model.cpp
  src/model/model_json.cpp
  src/solver/linear_model.cpp
  src/solver/minizinc_solver.cpp
)
target_include_directories(ralloc PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

# ---- standalone solver executable -----------------------------------------
# `ralloc-solve` is the process that drives MiniZinc: it reads model_input.json,
# solves M2 (MAU) + M3 (VLIW), and writes model_out.json. It links ONLY the
# model core (no bf-p4c), so the solver never runs inside p4c-barefoot's GC arena.
add_executable(ralloc-solve src/tool/ralloc_solve_main.cpp)
target_link_libraries(ralloc-solve PRIVATE ralloc)

# ---- bridge library (links bf-p4c IR) -------------------------------------
# NOTE: The in-tree integration (backends/tofino/bf-p4c/CMakeLists.txt) builds
# the bridge + RallocModelPass directly against tofinobackend's include
# environment and links it into the backend. This block only builds a bridge
# here for an explicit standalone consumer that sets P4C_SOURCE_DIR and provides
# the generated IR headers itself; it is skipped if the in-tree target already
# exists (avoids a double definition of `ralloc_bridge`).
if(DEFINED P4C_SOURCE_DIR AND NOT TARGET ralloc_bridge)
  add_library(ralloc_bridge
    src/bridge/compiler_bridge.cpp
    src/bridge/spec_check.cpp
    src/bridge/ralloc_model_pass.cpp
  )
  target_link_libraries(ralloc_bridge PUBLIC ralloc)
  target_compile_definitions(ralloc_bridge PUBLIC RALLOC_WITH_BFP4C=1)
  target_include_directories(ralloc_bridge PUBLIC ${P4C_SOURCE_DIR})
endif()

# ---- tests ----------------------------------------------------------------
enable_testing()
add_subdirectory(test EXCLUDE_FROM_ALL)
