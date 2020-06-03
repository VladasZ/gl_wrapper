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
#include "Monitor.hpp"


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
    
    using DrawBlock = std::function<void()>;

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

    static inline unsigned gl_major_version;
    static inline std::string gl_version;
    static inline std::string glsl_version;
    static inline unsigned glsl_version_number;

    static inline bool is_gles;
    static inline bool is_gl2;

    static inline std::vector<gl::Monitor> monitors;
    
#ifdef IOS_BUILD
    static inline float screen_scale = 2.0f;
#else
    static inline float screen_scale = 1.0f;
#endif
    
    static inline gm::Size window_size;

    static void initialize(const gm::Size& size);

#ifdef DESKTOP_BUILD
    static void start_main_loop(std::function<void()> draw_frame);
#endif
  
    static inline cu::Event<gm::Size> on_window_size_change;
    static inline cu::Event<gm::Point> on_cursor_moved;
    static inline cu::Event<gm::Point> on_scroll_moved;

#ifdef DESKTOP_BUILD
    static inline cu::Event<MouseButton, ButtonState> on_mouse_key_pressed;
#endif
    
    static inline cu::Event<int, int, int> on_key_pressed;

    static void set_viewport(const gm::Rect& rect);
    static void set_clear_color(const gm::Color& color);

    static void scissor_begin(const gm::Rect& rect);
    static void scissor_end();

    static void clear();

    static void enable_depth_test();
    static void disable_depth_test();

#ifdef DESKTOP_BUILD
    static void set_cursor_mode(CursorMode);
#endif

#ifdef ANDROID_BUILD
    static void create_context();
#endif

private:

    static void _get_gl_info();

};
