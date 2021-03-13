//
//  GL.cpp
//  gl_wrapper
//
//  Created by Vladas Zakrevskis on 12/28/18.
//  Copyright © 2018 VladasZ. All rights reserved.
//

#include "Log.hpp"
#include "GLDebug.hpp"
#include "Dispatch.hpp"
#include "GLWrapper.hpp"
#include "StringUtils.hpp"
#include "OpenGLHeaders.hpp"
#include "GLWFCallbacks.hpp"
#include "ExceptionCatch.hpp"


using namespace cu;
using namespace std;

const static string glsl_version_query = R"((\d\.)(\d\d))";
const static string gl_version_query   = R"((\d\.)(\d))";

const unsigned GL::DrawMode::Points        = 0;//GL_POINT;
const unsigned GL::DrawMode::Lines         = GL_LINES;
const unsigned GL::DrawMode::LineStrip     = GL_LINE_STRIP;
const unsigned GL::DrawMode::LineLoop      = GL_LINE_LOOP;
const unsigned GL::DrawMode::Triangles     = GL_TRIANGLES;
const unsigned GL::DrawMode::TriangleFan   = GL_TRIANGLE_FAN;
const unsigned GL::DrawMode::TriangleStrip = GL_TRIANGLE_STRIP;
const unsigned GL::DrawMode::Polygon       = 0;//GL_POLYGON;

#ifdef DESKTOP_BUILD

static GLFWwindow* window = nullptr;

namespace cursor {
    static GLFWcursor* arrow;
    static GLFWcursor* text;
    static GLFWcursor* drag;
    static GLFWcursor* h_resize;
    static GLFWcursor* v_resize;
}
#endif

void GL::initialize(const gm::Size& size) {

#ifdef DESKTOP_BUILD
    glfwInit();

    glfwWindowHint(GLFW_SAMPLES, 16); // 4x antialiasing
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // We want OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //We don't want the old OpenGL
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
#endif

    window = GL(glfwCreateWindow(static_cast<int>(size.width),
                                 static_cast<int>(size.height),
                                 "Test Engine",
                                 nullptr,
                                 nullptr));

    if (window == nullptr) {
        Fatal("GLFW window creation failed");
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Limit fps to 60
    glewExperimental = GL_TRUE;

    if (glewInit()) {
        Fatal("Glew initialization failed");
    }

#endif

    _get_gl_info();

    GL(glEnable(GL_DEPTH_TEST));
    GL(glEnable(GL_BLEND));
    GL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));


#ifdef DESKTOP_BUILD
    glfwSetKeyCallback        (window, key_callback            );
    glfwSetScrollCallback     (window, scroll_callback         );
    glfwSetCursorPosCallback  (window, cursor_position_callback);
    glfwSetWindowSizeCallback (window, size_changed            );
    glfwSetMouseButtonCallback(window, mouse_button_callback   );
#endif

#ifdef DESKTOP_BUILD
    cursor::arrow    = glfwCreateStandardCursor(GLFW_ARROW_CURSOR);
    cursor::text     = glfwCreateStandardCursor(GLFW_IBEAM_CURSOR);
#ifdef WIN32
    cursor::drag     = glfwCreateStandardCursor(GLFW_HAND_CURSOR);
#else
    cursor::drag     = glfwCreateStandardCursor(GLFW_CROSSHAIR_CURSOR);
#endif
    cursor::h_resize = glfwCreateStandardCursor(GLFW_HRESIZE_CURSOR);
    cursor::v_resize = glfwCreateStandardCursor(GLFW_VRESIZE_CURSOR);
#endif


#ifdef DESKTOP_BUILD
    
    int monitors_count;
    auto glfw_monitors = glfwGetMonitors(&monitors_count);

    for (int i = 0; i < monitors_count; i++) {
        monitors.emplace_back(glfw_monitors[i]);
    }
    
#elif IOS_BUILD
    monitors.push_back(gl::Monitor());
#elif ANDROID_BUILD
    monitors.push_back(gl::Monitor(3, 60, { 1920, 1080 }, { 1, 1 }, "Xiaoumi"));
#endif

    for (const auto& monitor : monitors) {
        Log << monitor;
    }

    render_scale = monitors.front().scale();

#ifdef DESKTOP_BUILD

    using GamepadID = decltype(GLFW_JOYSTICK_LAST);

    static GamepadID gamepad_id = -1;

    Dispatch::each(1, [&] {
        for (auto i = GLFW_JOYSTICK_1; i <= GLFW_JOYSTICK_LAST; i++) {
            if (glfwJoystickPresent(i)) {
                Log << "Gamepad: " << glfwGetGamepadName(i);
                gamepad_id = i;
            }
        }
        if (gamepad_id == -1) {
            //Log << "No gamepad";
        }
    });

    Dispatch::each(0.01, [&] {

        if (gamepad_id == -1) return;

        GLFWgamepadstate state;

        if (glfwGetGamepadState(gamepad_id, &state))
        {
            gamepad.a = state.buttons[GLFW_GAMEPAD_BUTTON_A];
            gamepad.b = state.buttons[GLFW_GAMEPAD_BUTTON_B];
            gamepad.x = state.buttons[GLFW_GAMEPAD_BUTTON_X];
            gamepad.y = state.buttons[GLFW_GAMEPAD_BUTTON_Y];

            gamepad.lb = state.buttons[GLFW_GAMEPAD_BUTTON_LEFT_THUMB];
            gamepad.rb = state.buttons[GLFW_GAMEPAD_BUTTON_RIGHT_THUMB];

            gamepad.back  = state.buttons[GLFW_GAMEPAD_BUTTON_BACK];
            gamepad.start = state.buttons[GLFW_GAMEPAD_BUTTON_START];

            gamepad.lt = state.axes[GLFW_GAMEPAD_AXIS_LEFT_TRIGGER];
            gamepad.rt = state.axes[GLFW_GAMEPAD_AXIS_RIGHT_TRIGGER];

            gamepad.up    = state.buttons[GLFW_GAMEPAD_BUTTON_DPAD_UP];
            gamepad.right = state.buttons[GLFW_GAMEPAD_BUTTON_DPAD_RIGHT];
            gamepad.down  = state.buttons[GLFW_GAMEPAD_BUTTON_DPAD_DOWN];
            gamepad.left  = state.buttons[GLFW_GAMEPAD_BUTTON_DPAD_LEFT];

            gamepad.left_stick.x = state.axes[GLFW_GAMEPAD_AXIS_LEFT_X];
            gamepad.left_stick.y = state.axes[GLFW_GAMEPAD_AXIS_LEFT_Y];

            gamepad.right_stick.x = state.axes[GLFW_GAMEPAD_AXIS_RIGHT_X];
            gamepad.right_stick.y = state.axes[GLFW_GAMEPAD_AXIS_RIGHT_Y];

            on_gamepad_update(gamepad);
        }
        else {
            Log << "Izmena";
        }

    });
    
#endif

}

#ifdef DESKTOP_BUILD
void GL::start_main_loop(function<void()> draw_frame) {
    while (true) {
        GL(glfwPollEvents());
        draw_frame();
        GL(glfwSwapBuffers(window));
    }
}
#endif

void GL::set_viewport(const gm::Rect& rect) {
#ifdef DEBUG
    if (rect.size.is_negative()) {
        Log << "Invalid size";
        return;
    }
#endif
    GL(glViewport(static_cast<GLint>(rect.origin.x),
                  static_cast<GLint>((window_size.height - rect.origin.y - rect.size.height)),
                  static_cast<GLsizei>(rect.size.width),
                  static_cast<GLsizei>(rect.size.height)));
}

void GL::set_clear_color(const gm::Color& color) {
    GL(glClearColor(color.r, color.g, color.b, color.a));
}

void GL::scissor_begin(const gm::Rect& rect) {
    GL(glEnable(GL_SCISSOR_TEST));
    GL(glScissor(static_cast<GLint>(rect.origin.x),
                 static_cast<GLint>((window_size.height - rect.origin.y - rect.size.height)),
                 static_cast<GLsizei>(rect.size.width),
                 static_cast<GLsizei>(rect.size.height)));
}

void GL::scissor_end() {
    GL(glDisable(GL_SCISSOR_TEST));
}

void GL::clear() {
    GL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}

void GL::enable_depth_test() {
    GL(glEnable(GL_DEPTH_TEST));
}

void GL::disable_depth_test() {
    GL(glDisable(GL_DEPTH_TEST));
}

void GL::_get_gl_info() {

    try {
        string full_gl_version = cu::log::to_string(glGetString(GL_VERSION));

        is_gles = String::contains(full_gl_version, "ES");

        gl_version =
            String::find_regexpr_match(full_gl_version,
                                       gl_version_query);

        glsl_version =
            String::find_regexpr_match(cu::log::to_string(glGetString(GL_SHADING_LANGUAGE_VERSION)),
                                       glsl_version_query);

        glsl_version_number = stoi(String::remove(glsl_version, '.'));

        gl_major_version = gl_version.front() - '0';

        Logvar(full_gl_version);
        Logvar(gl_major_version);
        Logvar(gl_version);
        Logvar(glsl_version);
        Logvar(glsl_version_number);
        Logvar(is_gles);

        if (gl_major_version < 3) {
            Fatal("OpenGL version is too low.");
        }
    }
    catch(...) {
        Fatal("Failed to get OpenGL info. " + what());
    }

}

#ifdef DESKTOP_BUILD

void GL::set_cursor_mode(CursorMode cursor_mode) {
    switch (cursor_mode) {
        case CursorMode::Arrow:
            glfwSetCursor(window, cursor::arrow);
            break;
        case CursorMode::Text:
            glfwSetCursor(window, cursor::text);
            break;
        case CursorMode::Drag:
            glfwSetCursor(window, cursor::drag);
            break;
        case CursorMode::HResize:
            glfwSetCursor(window, cursor::h_resize);
            break;
        case CursorMode::VResize:
            glfwSetCursor(window, cursor::v_resize);
            break;
    }
}

#endif
