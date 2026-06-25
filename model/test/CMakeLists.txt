# Unit tests for the ralloc model core (Doc 07 §4). No bf-p4c, no SCIP required:
# tests build a LinearModel and assert .lp text / structure against goldens.
add_executable(ralloc_unit
  test_mau_model.cpp
)
target_link_libraries(ralloc_unit PRIVATE ralloc)
add_test(NAME ralloc_unit COMMAND ralloc_unit)

# JSON seam round-trip (model_input.json / model_out.json contract).
add_executable(ralloc_json_test
  test_model_json.cpp
)
target_link_libraries(ralloc_json_test PRIVATE ralloc)
add_test(NAME ralloc_json_test COMMAND ralloc_json_test)
