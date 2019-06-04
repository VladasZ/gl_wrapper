//
//  OpenglHeaders.hpp
//  gl_wrapper
//
//  Created by Vladas Zakrevskis on 3/3/19
//  Copyright © 2019 VladasZ. All rights reserved.
//

#pragma once

#ifdef IOS_BUILD
// #include <Foundation.h>
    #include <OpenGLES/ES3/gl.h>
#else
    #include <GL/glew.h>
    #include <GLFW/glfw3.h>
#endif
