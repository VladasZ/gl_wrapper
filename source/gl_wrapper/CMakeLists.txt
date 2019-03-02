cmake_minimum_required(VERSION 3.8 FATAL_ERROR)

project(gl_wrapper)

add_catalog_recursive(${PROJECT_SOURCE_DIR} /Source SOURCE)

add_library(${PROJECT_NAME} ${SOURCE})

if(IOS_BUILD)

endif()

link_project_at_path(geometry  ${geometry_path} )
link_project_at_path(cpp_utils ${cpp_utils_path})
