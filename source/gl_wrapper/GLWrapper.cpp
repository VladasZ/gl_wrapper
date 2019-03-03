//
//  GL.cpp
//  gl_wrapper
//
//  Created by Vladas Zakrevskis on 12/28/18.
//  Copyright © 2018 VladasZ. All rights reserved.
//

#include       "GLDebug.hpp"
#include     "GLWrapper.hpp"
#include "OpenGLHeaders.hpp"

static GLFWwindow* window = nullptr;

#if DESKTOP_BUILD
namespace cursor {
static GLFWcursor* arrow;
static GLFWcursor* text;
static GLFWcursor* drag;
static GLFWcursor* h_resize;
static GLFWcursor* v_resize;
}
#endif

#if DESKTOP_BUILD

static void size_changed(GLFWwindow* window, int width, int height);
static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
static void cursor_position_callback(GLFWwindow* window, double x, double y);
static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

#endif

void GL::initialize(const Size& size) {

#if DESKTOP_BUILD
    glfwInit();
    glfwWindowHint(GLFW_SAMPLES, 16); // 4x antialiasing
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // We want OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //We don't want the old OpenGL
#ifdef MAC_OS
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
#endif

    window = glfwCreateWindow(static_cast<int>(size.width),
                              static_cast<int>(size.height),
                              "Test Engine",
                              nullptr,
                              nullptr);

    if (window == nullptr)
        Fatal("GLFW window creation failed");

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Limit fps to 60
    glewExperimental = GL_TRUE;

    if (glewInit())
        Fatal("Glew initialization failed");

    auto mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    display_resolution = { static_cast<float>(mode->width), static_cast<float>(mode->height) };
#endif

    GL(glEnable(GL_DEPTH_TEST));
    GL(glEnable(GL_BLEND));
    GL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));


#if DESKTOP_BUILD
    glfwSetKeyCallback        (window, key_callback            );
    glfwSetScrollCallback     (window, scroll_callback         );
    glfwSetCursorPosCallback  (window, cursor_position_callback);
    glfwSetWindowSizeCallback (window, size_changed            );
    glfwSetMouseButtonCallback(window, mouse_button_callback   );
#endif

#if DESKTOP_BUILD
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
}

void GL::start_main_loop(std::function<void()> on_frame_drawn) {
    do {
        GL(glfwPollEvents());
        on_frame_drawn();
        GL(glfwSwapBuffers(window));
    } while (
        glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
        glfwWindowShouldClose(window) == 0
    );
}

void GL::set_viewport(const Rect& rect) {
    static const GLint scale = 2;
    glViewport(static_cast<GLint>  (rect.origin.x) * scale,
               static_cast<GLint>  (screen_size.height - rect.origin.y - rect.size.height) * scale,
               static_cast<GLsizei>(rect.size.width) * scale,
               static_cast<GLsizei>(rect.size.height) * scale);
}

void GL::set_clear_color(const Color& color) {
    glClearColor(color.r, color.g, color.b, color.a);
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

#if DESKTOP_BUILD
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

static void size_changed(GLFWwindow* window, int width, int height) {
    GL::on_window_size_change({ static_cast<float>(width), static_cast<float>(height) });
    GL(glfwSwapBuffers(window));
}

static void mouse_button_callback([[maybe_unused]] GLFWwindow* window,
int glfw_button,
int action,
[[maybe_unused]] int mods) {

}

static void cursor_position_callback([[maybe_unused]] GLFWwindow* window, double x, double y) {

}

static void scroll_callback([[maybe_unused]] GLFWwindow* window, double xoffset, double yoffset) {

}

static void key_callback([[maybe_unused]] GLFWwindow* window,
int key,
int scancode,
int action,
int mods) {

}
