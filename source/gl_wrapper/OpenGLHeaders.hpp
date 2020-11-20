//
//  OpenglHeaders.hpp
//  gl_wrapper
//
//  Created by Vladas Zakrevskis on 3/3/19
//  Copyright © 2019 VladasZ. All rights reserved.
//

#pragma once

#include "Target.hpp"

#ifndef GL_SILENCE_DEPRECATION
#define GL_SILENCE_DEPRECATION
#endif

#ifdef IOS_BUILD

#include <OpenGLES/ES1/gl.h>
#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES3/gl.h>

#elif __ANDROID__

#include <GLES/gl.h>
#include <GLES2/gl2.h>
#include <GLES3/gl3.h>

#elif DESKTOP_BUILD

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#else
    INVALID_PLATFORM
#endif
