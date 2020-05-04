//
//  GLDebug.hpp
//  gl_wrapper
//
//  Created by Vladas Zakrevskis on 3/3/19..
//  Copyright © 2019 VladasZ. All rights reserved.
//

#pragma once

#include <string>


#ifdef DEBUG

#define RENDERING_ERRORS_OUTPUT true
//#define SHADER_COMPILER_OUTPUT

#if RENDERING_ERRORS_OUTPUT
#define GL(command) command; check_gl_error(__FILE__, __func__, __LINE__)
#else
#define GL(x) x
#endif

#define CHECK_FRAMEBUFFER check_framebuffer_status(GL_FRAMEBUFFER, __FILE__, __func__, __LINE__)

void check_gl_error(const std::string& fileName, const char* function, int line);
void check_framebuffer_status(unsigned int target, const std::string& fileName, const char* function, int line);

#else

#define GL(x) x

#endif
