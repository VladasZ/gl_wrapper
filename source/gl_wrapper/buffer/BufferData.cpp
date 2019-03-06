//
//  BufferData.cpp
//  gl_wrapper
//
//  Created by Vladas Zakrevskis on 9/17/17.
//  Copyright © 2017 VladasZ. All rights reserved.
//

#include <cstring>

#include "BufferData.hpp"

using namespace gl;
using namespace gm;

static const std::vector<unsigned short> rect_indices = { 0, 1, 3, 2 };

BufferData::BufferData(const std::vector<float>& vertices, const std::vector<unsigned short>& indices)
    : vertices_data(vertices), indices(indices) { }

std::string BufferData::to_string(unsigned int new_line) const {
    std::string string;
    string = "\n";

    for (size_t i = 0; i < vertices_data.size(); i++) {
        string += std::to_string(vertices_data[i]) + " ";
        if ((i + 1) % (new_line) == 0)
            string += "\n";
    }

    string += "\n";

    for (unsigned int i = 0; i < indices.size(); i++) {
        string += std::to_string(indices[i]) + " ";
        if ((i + 1) % (new_line) == 0)
            string += "\n";
    }

    return string;
}

BufferData* BufferData::from_size(const Size& size) {
    const std::vector<float> vertices = {
        0,          0,
        0,          size.height,
        size.width, size.height,
        size.width, 0
    };
    return new BufferData(vertices, rect_indices);
}

BufferData* BufferData::from_rect(const Rect& rect) {
    const std::vector<float> vertices = {
        rect.origin.x,                   rect.origin.y,
        rect.origin.x,                   rect.size.height + rect.origin.y,
        rect.size.width + rect.origin.x, rect.size.height + rect.origin.y,
        rect.size.width + rect.origin.x, rect.origin.y
    };
    return new BufferData(vertices, rect_indices);
}

BufferData* BufferData::from_rect_to_image(const Rect& rect) {
    const std::vector<float> vertices = {
        rect.origin.x,                   rect.origin.y,                    0.0f,  1.0f, //|- |
        rect.origin.x,                   rect.size.height + rect.origin.y, 0.0f,  0.0f, //|_ |
        rect.size.width + rect.origin.x, rect.size.height + rect.origin.y, 1.0f,  0.0f, //| _|
        rect.size.width + rect.origin.x, rect.origin.y,                    1.0f,  1.0f  //| -|
    };
    return new BufferData(vertices, rect_indices);
}

BufferData* BufferData::from_rect_to_framebuffer(const Rect& rect) {
    const std::vector<float> vertices = {
        rect.origin.x,                   rect.origin.y,                    0.0f,  1.0f, //|- |
        rect.origin.x,                   rect.size.height + rect.origin.y, 0.0f,  0.0f, //| _|
        rect.size.width + rect.origin.x, rect.size.height + rect.origin.y, 1.0f,  0.0f, //| -|
        rect.size.width + rect.origin.x, rect.origin.y,                    1.0f,  1.0f  //| _|
    };
    return new BufferData(vertices, rect_indices);
}


