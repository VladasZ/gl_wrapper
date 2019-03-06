cmake_minimum_required(VERSION 3.8 FATAL_ERROR)

project(gl_wrapper)

add_catalog_recursive(${PROJECT_SOURCE_DIR} /Source SOURCE)

include_directories(/Applications/Xcode.app/Contents/Developer/Platforms/iPhoneOS.platform/Developer/SDKs/iPhoneOS12.1.sdk/System/Library/Frameworks/Foundation.framework/Headers/)
include_directories(/Applications/Xcode.app/Contents/Developer/Platforms/iPhoneOS.platform/Developer/SDKs/iPhoneOS12.1.sdk/System/Library/Frameworks/OpenGLES.framework/Headers/)

set(CMAKE_C_FLAGS   "-x objective-c")
set(CMAKE_CXX_FLAGS "-x objective-c++")
#set(CMAKE_EXE_LINKER_FLAGS "-framework Foundation")

add_library(${PROJECT_NAME} ${SOURCE})

if(IOS_BUILD)

endif()

link_project_at_path(geometry  ${geometry_path} )
link_project_at_path(cpp_utils ${cpp_utils_path})
