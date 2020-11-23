//
//  GL.cpp
//  gl_wrapper
//
//  Created by Vladas Zakrevskis on 12/28/18.
//  Copyright © 2018 VladasZ. All rights reserved.
//

#include <iostream>

#include "Log.hpp"
#include "GLDebug.hpp"
#include "GLWrapper.hpp"
#include "StringUtils.hpp"
#include "OpenGLHeaders.hpp"

#include "GLWFCallbacks.hpp"


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

    window = glfwCreateWindow(static_cast<int>(size.width),
                              static_cast<int>(size.height),
                              "Test Engine",
                              nullptr,
                              nullptr);

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

    for (auto monitor : monitors) {
        Log << monitor;
    }
    
#endif

#ifdef IOS_BUILD
    render_scale = 3.0f;
#elif ANDROID_BUILD
    render_scale = 1.0f;
#else
    render_scale = 1.5f;
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
    GL(glViewport(static_cast<GLint>(rect.origin.x * render_scale),
                  static_cast<GLint>((window_size.height - rect.origin.y - rect.size.height) * render_scale),
                  static_cast<GLsizei>(rect.size.width * render_scale),
                  static_cast<GLsizei>(rect.size.height * render_scale)));
}

void GL::set_clear_color(const gm::Color& color) {
    GL(glClearColor(color.r, color.g, color.b, color.a));
}

void GL::scissor_begin(const gm::Rect& rect) {
    GL(glEnable(GL_SCISSOR_TEST));
    GL(glScissor(static_cast<GLint>(rect.origin.x * render_scale),
                 static_cast<GLint>((window_size.height - rect.origin.y - rect.size.height) * render_scale),
                 static_cast<GLsizei>(rect.size.width * render_scale),
                 static_cast<GLsizei>(rect.size.height * render_scale)));
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

    if (gl_major_version < 3) {
        Fatal("OpenGL version is too low.");
    }

    //Logvar(gl_major_version);
    //Logvar(gl_version);
    //Logvar(glsl_version);
    //Logvar(glsl_version_number);
    //Logvar(is_gles);
    //Logvar(is_gl2);
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
