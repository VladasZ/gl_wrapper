//
//  BufferData.cpp
//  gl_wrapper
//
//  Created by Vladas Zakrevskis on 9/17/17.
//  Copyright © 2017 VladasZ. All rights reserved.
//

#include <cstring>

#include "BufferData.hpp"

using namespace cu;
using namespace gm;
using namespace gl;


BufferData::BufferData(const Array<Float>& vertices, const Array<Vertex::Index>& indices)
    : _vertices_data(vertices), _indices(indices), _vertices_count(indices.size()) { }

BufferData::BufferData(const Array<Float>& vertices_data, size_t vertices_count)
    : _vertices_data(vertices_data),
    _vertices_count(vertices_count) { }

std::string BufferData::to_string(unsigned int new_line) const {
    std::string string;
    string = "\n";

    for (size_t i = 0; i < _vertices_data.size(); i++) {
        string += std::to_string(_vertices_data[i]) + " ";
        if ((i + 1) % (new_line) == 0) {
            string += "\n";
        }
    }

    string += "\n";

    for (unsigned i = 0; i < _indices.size(); i++) {
        string += std::to_string(_indices[i]) + " ";
        if ((i + 1) % (new_line) == 0) {
            string += "\n";
        }
    }

    string += "\n";
    string += std::to_string(_vertices_count);

    return string;
}

const BufferData::Array<gm::Float>& BufferData::vertices_data() const {
    return _vertices_data;
}

const BufferData::Array<Vertex::Index>& BufferData::indices() const {
    return _indices;
}

size_t BufferData::vertices_count() const {
    return _vertices_count;
}
