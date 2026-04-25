#ifndef IR_GENERATED_H_
#define IR_GENERATED_H_

// Umbrella header for the (formerly auto-generated) IR class hierarchy.
// The IR was split into per-category headers so each translation unit
// can include only what it needs. New code should prefer the specific
// headers below; this file exists for backwards compatibility.
//
//   ir-generated-base.h         interfaces + root abstract classes
//   ir-generated-types.h        Type_*, Parameter, StructField, Method, ...
//   ir-generated-expressions.h  Operation_* and all expression nodes
//   ir-generated-statements.h   Statement family + compound assignment ops
//   ir-generated-declarations.h P4Parser/P4Control/P4Action/P4Table/Block/...
//   ir-generated-v1.h           legacy P4-14 / V1 model classes

#include "ir/ir-generated-base.h"
#include "ir/ir-generated-types.h"
#include "ir/ir-generated-expressions.h"
#include "ir/ir-generated-statements.h"
#include "ir/ir-generated-declarations.h"
#include "ir/ir-generated-v1.h"

#endif  /* IR_GENERATED_H_ */
