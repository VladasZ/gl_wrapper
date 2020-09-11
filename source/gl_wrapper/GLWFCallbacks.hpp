//
//  GLWFCallbacks.hpp
//  gl_wrapper
//
//  Created by Vladas Zakrevskis on 15/12/19.
//  Copyright © 2019 VladasZ. All rights reserved.
//

#pragma once

void size_changed(GLFWwindow* window, int width, int height);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void cursor_position_callback(GLFWwindow* window, double x, double y);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mod);
