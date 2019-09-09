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
    
#ifdef DESKTOP_BUILD

    enum CursorMode {
        Arrow,
        Text,
        Drag,
        HResize,
        VResize
    };

    enum MouseButton {
        Left,
        Right,
        Middle
    };

    enum ButtonState {
        Up,
        Down
    };
    
#endif

    struct DrawMode {
        static const unsigned Points;
        static const unsigned Lines;
        static const unsigned LineStrip;
        static const unsigned LineLoop;
        static const unsigned Triangles;
        static const unsigned TriangleFan;
        static const unsigned TriangleStrip;
        static const unsigned Polygon;
    };

    static inline gm::Size screen_size;
    static inline gm::Size display_resolution;

    static void initialize(const gm::Size& size);

#ifdef DESKTOP_BUILD
    static void start_main_loop(std::function<void()> on_frame_drawn);
#endif
  
    static inline Event<gm::Size> on_window_size_change;
    static inline Event<gm::Point> on_cursor_moved;
    static inline Event<gm::Point> on_scroll_moved;

#ifdef DESKTOP_BUILD
    static inline Event<MouseButton, ButtonState> on_mouse_key_pressed;
#endif
    
    static inline Event<char, unsigned int> on_key_pressed;

    static void set_viewport(const gm::Rect& rect);
    static void set_clear_color(const gm::Color& color);

    static void clear();

    static void enable_depth_test();
    static void disable_depth_test();

#ifdef DESKTOP_BUILD
    static void set_cursor_mode(CursorMode);
#endif
};
