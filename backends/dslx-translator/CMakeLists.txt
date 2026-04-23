# Makefile for the DSLX translator backend.
# Emits P4 -> DSLX (.x) files via the p4c-dslx driver, modeled after the
# bmv2 / p4test backend layout.

message(STATUS "Start configuring the DSLX translator backend")

configure_file("${CMAKE_CURRENT_SOURCE_DIR}/version.h.cmake"
  "${CMAKE_CURRENT_BINARY_DIR}/version.h" @ONLY)

set(DSLX_IR_SRCS
  dslx_ir/ast.cc
  dslx_ir/module.cc
)
set(DSLX_IR_HDRS
  dslx_ir/ast.h
  dslx_ir/build.h
  dslx_ir/formatter.h
  dslx_ir/module.h
  dslx_ir/pos.h
)

set(P4_ADAPTER_SRCS
  p4_adapter/binding_helpers.cc
  p4_adapter/intrinsic_metadata.cc
  p4_adapter/p4_action_lower.cc
  p4_adapter/p4_control_lower.cc
  p4_adapter/p4_deparser_lower.cc
  p4_adapter/p4_expr_lower.cc
  p4_adapter/p4_parser_lower.cc
  p4_adapter/p4_stmt_lower.cc
  p4_adapter/p4_table_lower.cc
  p4_adapter/p4_to_dslx.cc
  p4_adapter/p4_type_lower.cc
)
set(P4_ADAPTER_HDRS
  p4_adapter/binding_helpers.h
  p4_adapter/intrinsic_metadata.h
  p4_adapter/lower_context.h
  p4_adapter/p4_action_lower.h
  p4_adapter/p4_control_lower.h
  p4_adapter/p4_deparser_lower.h
  p4_adapter/p4_expr_lower.h
  p4_adapter/p4_parser_lower.h
  p4_adapter/p4_stmt_lower.h
  p4_adapter/p4_table_lower.h
  p4_adapter/p4_to_dslx.h
  p4_adapter/p4_type_lower.h
)

set(DSLX_BACKEND_LIB_SRCS
  dslxBackend.cpp
  dslxOptions.cpp
  midend.cpp
  ${DSLX_IR_SRCS}
  ${P4_ADAPTER_SRCS}
)

set(DSLX_BACKEND_LIB_HDRS
  dslxBackend.h
  dslxOptions.h
  midend.h
  ${DSLX_IR_HDRS}
  ${P4_ADAPTER_HDRS}
)

add_library(dslx-translator STATIC ${DSLX_BACKEND_LIB_SRCS})
target_link_libraries(dslx-translator ${P4C_LIBRARIES} ${P4C_LIB_DEPS})
target_include_directories(dslx-translator
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/..
  PRIVATE ${CMAKE_CURRENT_BINARY_DIR}
  PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/..
)
add_dependencies(dslx-translator ir-generated frontend)

add_executable(p4c-dslx p4c-dslx.cpp)
target_link_libraries(p4c-dslx dslx-translator ${P4C_LIBRARIES} ${P4C_LIB_DEPS})
target_include_directories(p4c-dslx
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/..
  PRIVATE ${CMAKE_CURRENT_BINARY_DIR}
  PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/..
)
add_dependencies(p4c-dslx ir-generated frontend)

install(TARGETS p4c-dslx RUNTIME DESTINATION ${P4C_RUNTIME_OUTPUT_DIRECTORY})

file(RELATIVE_PATH
  CURRENT_BINARY_DIR_PATH_REL
  ${P4C_BINARY_DIR}
  ${CMAKE_CURRENT_BINARY_DIR}
)

file(RELATIVE_PATH
  P4C_BINARY_DIR_PATH_REL
  ${CMAKE_CURRENT_BINARY_DIR}
  ${P4C_BINARY_DIR}
)

# Mirror the bmv2/p4test convention: expose the backend binary at the top of
# the build directory and share the generated p4include tree.
add_custom_target(linkp4c-dslx
  COMMAND ${CMAKE_COMMAND} -E create_symlink ${CURRENT_BINARY_DIR_PATH_REL}/p4c-dslx ${P4C_BINARY_DIR}/p4c-dslx
  COMMAND ${CMAKE_COMMAND} -E create_symlink ${P4C_BINARY_DIR_PATH_REL}/p4include ${CMAKE_CURRENT_BINARY_DIR}/p4include
  COMMAND ${CMAKE_COMMAND} -E create_symlink ${P4C_BINARY_DIR_PATH_REL}/p4_14include ${CMAKE_CURRENT_BINARY_DIR}/p4_14include
  DEPENDS update_includes
)
add_dependencies(p4c_driver linkp4c-dslx)

message(STATUS "Done with configuring DSLX translator backend")
