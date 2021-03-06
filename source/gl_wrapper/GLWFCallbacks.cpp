//
//  GLWFCallbacks.cpp
//  gl_wrapper
//
//  Created by Vladas Zakrevskis on 15/12/19.
//  Copyright © 2019 VladasZ. All rights reserved.
//

#include "GLWFCallbacks.hpp"

#ifdef DESKTOP_BUILD

#include "GLDebug.hpp"
#include "GLWrapper.hpp"
#include "OpenGLHeaders.hpp"


void size_changed(GLFWwindow* window, int width, int height) {
    GL::on_window_size_change({ static_cast<float>(width * GL::render_scale), static_cast<float>(height * GL::render_scale) });
    GL(glfwSwapBuffers(window));
}

void mouse_button_callback(GLFWwindow*,
                           int glfw_button,
                           int action,
                           int) {
    auto button  = GL::MouseButton::Left;
    if      (glfw_button == GLFW_MOUSE_BUTTON_RIGHT ) button = GL::MouseButton::Right ;
    else if (glfw_button == GLFW_MOUSE_BUTTON_MIDDLE) button = GL::MouseButton::Middle;
    GL::on_mouse_key_pressed(button, action == GLFW_PRESS ? GL::ButtonState::Down : GL::ButtonState::Up);
}

void cursor_position_callback([[maybe_unused]] GLFWwindow* window, double x, double y) {
    GL::on_cursor_moved({ x / GL::render_scale, y / GL::render_scale });
}

void scroll_callback([[maybe_unused]] GLFWwindow* window, double xoffset, double yoffset) {
    GL::on_scroll_moved({ xoffset, yoffset });
}

void key_callback([[maybe_unused]] GLFWwindow* window,
                  int key,
                  [[maybe_unused]] int scancode,
                  int action,
                  int mod) {
    GL::on_key_pressed(key, mod, action);
}

#endif
