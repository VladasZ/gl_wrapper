
cmake_minimum_required(VERSION 3.8 FATAL_ERROR)

setup_exe(gl_wrapper_test)

link_project_at_path(cpp_utils  ${cpp_utils_path} )
link_project_at_path(gl_wrapper ${gl_wrapper_path})
