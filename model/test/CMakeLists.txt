# Unit tests for the ralloc model core (Doc 07 §4). No bf-p4c and no solver
# required: tests build a LinearModel and assert .lp text / structure against
# goldens.
add_executable(ralloc_unit
  test_mau_model.cpp
)
target_link_libraries(ralloc_unit PRIVATE ralloc)
add_test(NAME ralloc_unit COMMAND ralloc_unit)

# Solver behaviour: solves the MAU model, indicator rows and a small LP through
# the OR-Tools backend. Degrades to checking the .lp-export fallback when
# OR-Tools is not linked (RALLOC_HAVE_ORTOOLS=0).
add_executable(ralloc_solver_test
  test_ortools_solver.cpp
)
target_link_libraries(ralloc_solver_test PRIVATE ralloc)
add_test(NAME ralloc_solver_test COMMAND ralloc_solver_test)

# JSON seam round-trip (model_input.json / model_out.json contract).
add_executable(ralloc_json_test
  test_model_json.cpp
)
target_link_libraries(ralloc_json_test PRIVATE ralloc)
add_test(NAME ralloc_json_test COMMAND ralloc_json_test)

# The test executables are EXCLUDE_FROM_ALL (see ../CMakeLists.txt), so give
# `ctest` users one target that builds all of them:
#   cmake --build <builddir> --target ralloc_tests && ctest --test-dir <builddir>
add_custom_target(ralloc_tests DEPENDS ralloc_unit ralloc_solver_test ralloc_json_test)
