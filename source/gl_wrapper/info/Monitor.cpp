//
//  Monitor.cpp
//  gl_wrapper
//
//  Created by Vladas Zakrevskis on 10/25/19.
//  Copyright © 2019 VladasZ. All rights reserved.
//

#include "Log.hpp"
#include "GmMath.hpp"
#include "Monitor.hpp"
#include "OpenGLHeaders.hpp"

#ifdef IOS_BUILD
#include "CallObj.hpp"
#endif

using namespace gm;
using namespace gl;


Monitor::Monitor(unsigned scale,
        unsigned refresh_rate,
        const gm::Size& resolution,
        const gm::Size& physical_size,
        const std::string& name) :
    _scale(scale),
    _refresh_rate(refresh_rate),
    _resolution(resolution),
    _physical_size(physical_size),
    _name(name)
{
    
}

#ifdef IOS_BUILD
Monitor::Monitor() {
    obj_c::ScreenInfo info = obj_c::screen_info();

    _ppi = info.ppi;
    _scale = info.scale;
    _refresh_rate = info.refresh_rate;
    _resolution.width = info.res_x;
    _resolution.height = info.res_y;

    Size inch_size = _resolution / _ppi;

    Log << inch_size;

    _physical_size = { gm::math::inch_to_mm(inch_size.width), gm::math::inch_to_mm(inch_size.height) };

}
#endif

#ifdef DESKTOP_BUILD
Monitor::Monitor(void* glfw_monitor) {
    
    auto monitor = static_cast<GLFWmonitor*>(glfw_monitor);

    _name = glfwGetMonitorName(monitor);

    int x, y;
    glfwGetMonitorPhysicalSize(glfwGetPrimaryMonitor(), &x, &y);
    _physical_size = { x, y };

    auto mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    _resolution = { mode->width, mode->height };
    _refresh_rate = mode->refreshRate;

    float xscale, yscale;
    glfwGetMonitorContentScale(monitor, &xscale, &yscale);
    _scale = xscale;

    _ppi = _resolution.height / gm::math::mm_to_inch(_physical_size.height);

}
#endif

unsigned Monitor::ppi() const {
    return _ppi;
}

unsigned Monitor::scale() const {
    return _scale;
}

unsigned Monitor::refresh_rate() const {
    return _refresh_rate;
}

Size Monitor::resolution() const {
    return _resolution;
}

Size Monitor::physical_size() const {
    return _physical_size;
}

std::string Monitor::name() const {
    return _name;
}

float Monitor::diagonal() const {
    return gm::math::mm_to_inch(_physical_size.diagonal());
}

std::string Monitor::to_string() const {
    return std::string() +
        "Monitor: " + _name + "\n" +
        "Scale: " + std::to_string(_scale) + "\n" +
        "Resolution: " + _resolution.to_string() + "\n" +
        "Physical size: " + _physical_size.to_string() + " mm\n" +
        "Diagonal: " + std::to_string(diagonal()) + " inch\n" +
        "Ppi: " + std::to_string(ppi()) + "\n" +
        "Refresh rate: " + std::to_string(_refresh_rate) + "Hz\n";
}
