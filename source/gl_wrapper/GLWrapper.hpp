//
//  GL.hpp
//  TestEngine
//
//  Created by Vladas Zakrevskis on 8/17/17.
//  Copyright © 2017 VladasZ. All rights reserved.
//

#pragma once

#include <functional>

#include "Rect.hpp"
#include "Color.hpp"
#include "Event.hpp"

#include "Shader.hpp"

struct GL {

    enum CursorMode {
        Arrow  ,
        Text   ,
        Drag   ,
        HResize,
        VResize,
    };

    static inline Size screen_size;
    static inline Size display_resolution;

    static void initialize(const Size& size);

    static void start_main_loop(std::function<void()> on_frame_drawn);

    static inline Event<Size> on_window_size_change;

    static void set_viewport(const Rect& rect);
    static void set_clear_color(const Color& color);
    static void clear();
    static void enable_depth_test();
    static void disable_depth_test();

#if DESKTOP_BUILD
    static void set_cursor_mode(CursorMode);
#endif
};
