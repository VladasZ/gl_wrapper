//
//  GL.hpp
//  TestEngine
//
//  Created by Vladas Zakrevskis on 8/17/17.
//  Copyright © 2017 VladasZ. All rights reserved.
//

#pragma once

#include "Rect.hpp"
#include "Color.hpp"

#include "Shader.hpp"

struct GL {

    static inline Size screen_size;

    static void set_viewport(const Rect& rect);
    static void set_clear_color(const Color& color);
};
