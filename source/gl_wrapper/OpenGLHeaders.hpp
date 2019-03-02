//
//  OpenglHeaders.hpp
//  gl_wrapper
//
//  Created by Vladas Zakrevskis on 3/3/19
//  Copyright © 2019 VladasZ. All rights reserved.
//

#pragma once

#if IOS_BUILD
    #include <OpenGL/gl.h>
#else
    #include <GL/glew.h>
    #include <GLFW/glfw3.h>
#endif