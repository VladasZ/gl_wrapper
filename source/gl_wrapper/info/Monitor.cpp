//
//  Monitor.cpp
//  gl_wrapper
//
//  Created by Vladas Zakrevskis on 10/25/19.
//  Copyright © 2019 VladasZ. All rights reserved.
//

#include "Monitor.hpp"
#include "OpenGLHeaders.hpp"

using namespace gm;
using namespace gl;

Monitor::Monitor(void* pointer) {

    auto monitor = static_cast<GLFWmonitor*>(pointer);

    _name = glfwGetMonitorName(monitor);

    int x, y;
    glfwGetMonitorPhysicalSize(glfwGetPrimaryMonitor(), &x, &y);
    _physical_size = { x, y };

    auto mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    _resolution = { mode->width, mode->height };
    _refresh_rate = mode->refreshRate;

    float xscale, yscale;
    glfwGetMonitorContentScale(monitor, &xscale, &yscale);
    _scale = { xscale, yscale };
}

std::string Monitor::name() const {
    return _name;
}

unsigned Monitor::refresh_rate() const {
    return _refresh_rate;
}

gm::Size Monitor::scale() const {
    return _scale;
}

Size Monitor::resolution() const {
    return _resolution;
}

Size Monitor::physical_size() const {
    return _physical_size;
}

std::string Monitor::to_string() const {
    return std::string() +
        "Monitor: " + _name + "\n" +
        "Scale: " + _scale.to_string() + "\n" +
        "Resolution: " + _resolution.to_string() + "\n" +
        "Physical size: " + _physical_size.to_string() + " mm\n" +
        "Refresh rate: " + std::to_string(_refresh_rate) + "Hz\n";
}
