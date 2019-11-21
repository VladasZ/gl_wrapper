cmake_minimum_required(VERSION 3.8 FATAL_ERROR)

setup_lib(gl_wrapper)

if(IOS_BUILD)

include_directories(/Applications/Xcode.app/Contents/Developer/Platforms/iPhoneOS.platform/Developer/SDKs/iPhoneOS12.1.sdk/System/Library/Frameworks/Foundation.framework/Headers/)
include_directories(/Applications/Xcode.app/Contents/Developer/Platforms/iPhoneOS.platform/Developer/SDKs/iPhoneOS12.1.sdk/System/Library/Frameworks/OpenGLES.framework/Headers/)

set(CMAKE_C_FLAGS   "-x objective-c")
set(CMAKE_CXX_FLAGS "-x objective-c++")

endif()
