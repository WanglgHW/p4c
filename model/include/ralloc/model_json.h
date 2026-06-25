/**
 * Copyright (C) 2026
 * SPDX-License-Identifier: Apache-2.0
 *
 * ralloc/model_json.h
 *
 * Round-trippable JSON serialization for the model seam PODs (ModelInputs and
 * ModelResults, model_types.h). This is the on-disk contract between the three
 * decoupled phases:
 *
 *   compiler emit   -> model_input.json   (ModelInputs)
 *   ralloc-solve    -> model_out.json     (ModelResults)
 *   compiler resume <-  both
 *
 * It links NO bf-p4c headers and NO external JSON dependency (a tiny self
 * contained DOM lives in model_json.cpp), so it builds in both the standalone
 * `ralloc` core library and the in-tree `ralloc_bridge`.
 */
#ifndef RALLOC_MODEL_JSON_H_
#define RALLOC_MODEL_JSON_H_

#include <iosfwd>
#include <string>

#include "ralloc/model_types.h"

namespace ralloc {

// ---- ModelInputs (compiler -> solver) -------------------------------------
void writeModelInputs(const ModelInputs &in, std::ostream &os);
ModelInputs readModelInputs(std::istream &is);

// ---- ModelResults (solver -> compiler) ------------------------------------
void writeModelResults(const ModelResults &res, std::ostream &os);
ModelResults readModelResults(std::istream &is);

// ---- ResumeBundle (ir_middle.json) ----------------------------------------
void writeResumeBundle(const ResumeBundle &b, std::ostream &os);
ResumeBundle readResumeBundle(std::istream &is);

// ---- path convenience wrappers (throw std::runtime_error on I/O failure) ---
void writeModelInputsFile(const ModelInputs &in, const std::string &path);
ModelInputs readModelInputsFile(const std::string &path);
void writeModelResultsFile(const ModelResults &res, const std::string &path);
ModelResults readModelResultsFile(const std::string &path);
void writeResumeBundleFile(const ResumeBundle &b, const std::string &path);
ResumeBundle readResumeBundleFile(const std::string &path);

}  // namespace ralloc

#endif  // RALLOC_MODEL_JSON_H_
