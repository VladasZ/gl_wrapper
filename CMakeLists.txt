cmake_minimum_required(VERSION 3.9.2 FATAL_ERROR)

if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_CURRENT_SOURCE_DIR})
	include(build/build_tools_generated.cmake)
	include(${CMAKE_UTILS_PATH})
	if(${NEEDS_CONAN})
	include(${CONAN_BUILD_INFO})
	endif()
endif()

set(CMAKE_CXX_STANDARD 17)

project(gl_wrapper)

if(${NEEDS_CONAN})
conan_basic_setup()
endif()

add_subdirectory(source/gl_wrapper)
if(${DESKTOP_BUILD})
  add_subdirectory(source/gl_wrapper_test)
endif()

if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_CURRENT_SOURCE_DIR})
  foreach(var ${GIT_DEPENDENCIES})
	add_subdirectory(${var} "${var}/dep_build")
  endforeach()
endif()
