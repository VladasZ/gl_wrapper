//
//  OpenglHeaders.hpp
//  gl_wrapper
//
//  Created by Vladas Zakrevskis on 3/3/19
//  Copyright © 2019 VladasZ. All rights reserved.
//

#pragma once

#define GL_SILENCE_DEPRECATION

//#define OPENGL2_BUILD

#ifdef IOS_BUILD
    #include <OpenGLES/ES3/gl.h>
#elif ANDROID_BUILD

#ifdef OPENGL2_BUILD
#include <GLES/gl.h>
#include <GLES2/gl2.h>
#else
#include <GLES3/gl3.h>
#endif

#elif DESKTOP_BUILD
    #include <GL/glew.h>
    #include <GLFW/glfw3.h>
#else
    INVALID_PLATFORM
#endif
