//
//  GLDebug.hpp
//  gl_wrapper
//
//  Created by Vladas Zakrevskis on 3/3/19..
//  Copyright © 2019 VladasZ. All rights reserved.
//

#pragma once

#pragma once

#include "Log.hpp"

#ifdef DEBUG

#define RENDERING_ERRORS_OUTPUT true
#define SHADER_COMPILER_OUTPUT true

#if RENDERING_ERRORS_OUTPUT
#define GL(x) (x); check_gl_error(LOCATION_INFO)
#else
#define GL(x) x
#endif

#define CHECK_FRAMEBUFFER check_framebuffer_status(GL_FRAMEBUFFER, LOCATION_INFO)

void check_gl_error(LOCATION_PARAMETERS);
void check_framebuffer_status(unsigned int target, LOCATION_PARAMETERS);

#else

#define GL(x) x

#endif
