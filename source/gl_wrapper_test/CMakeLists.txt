
cmake_minimum_required(VERSION 3.8 FATAL_ERROR)

project(gl_wrapper_test)

add_catalog_recursive(${PROJECT_SOURCE_DIR} / SOURCE)
add_executable(${PROJECT_NAME} ${SOURCE})

link_project_at_path(cpp_utils  ${cpp_utils_path} )
link_project_at_path(gl_wrapper ${gl_wrapper_path})

if(${NEEDS_CONAN})
conan_target_link_libraries(${PROJECT_NAME})
endif()
