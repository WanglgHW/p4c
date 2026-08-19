/**
 * Copyright (C) 2026
 * SPDX-License-Identifier: Apache-2.0
 *
 * DeviceSpec factories (Doc 01). Numbers mirror bf-p4c specs; the compile-time
 * bridge spec_check.cpp static_asserts them against the live backend symbols.
 */
#include "ralloc/device_spec.h"

#include <algorithm>

namespace ralloc {

DeviceSpec DeviceSpec::tofino1() {
    DeviceSpec d;  // defaults in the header are Tofino-1.
    d.kind = DeviceKind::Tofino1;
    return d;
}

DeviceSpec DeviceSpec::tofino2u() {
    DeviceSpec d = tofino1();
    d.kind = DeviceKind::Tofino2U;
    d.num_stages = 20;            // JBayUDevice::getNumStages()
    // Tofino-2 adds mocha/dark kinds and different PHV group counts; populate
    // d.normal_phv accordingly in a full port. Budgets per stage are unchanged
    // for the resources modeled here (StageUse constants are shared).
    return d;
}

DeviceSpec DeviceSpec::tofino2m() {
    DeviceSpec d = tofino2u();
    d.kind = DeviceKind::Tofino2M;
    d.num_stages = 12;            // JBayMDevice::getNumStages()
    return d;
}

DeviceSpec DeviceSpec::fromName(const std::string &name, float phv_scale_factor) {
    DeviceSpec d;
    if (name == "Tofino" || name == "tofino")
        d = tofino1();
    else if (name == "Tofino2" || name == "Tofino2U" || name == "JBay")
        d = tofino2u();
    else if (name == "Tofino2M")
        d = tofino2m();
    else
        d = tofino1();
    // Honor --phv-scale-factor (Doc 01 §2.1): scales MAU group counts.
    if (phv_scale_factor != 1.0f)
        for (auto &c : d.normal_phv)
            c.num_groups = std::max(1u, static_cast<unsigned>(c.num_groups * phv_scale_factor));
    return d;
}

}  // namespace ralloc
