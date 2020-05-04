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
    :
    vertices_data(vertices),
    indices(indices),
    vertices_count(indices.size()) { }

BufferData::BufferData(const Array<Float>& vertices_data, size_t vertices_count)
    :
    vertices_data(vertices_data),
    vertices_count(vertices_count) { }

std::string BufferData::to_string(unsigned int new_line) const {
    std::string string;
    string = "\n";

    for (size_t i = 0; i < vertices_data.size(); i++) {
        string += std::to_string(vertices_data[i]) + " ";
        if ((i + 1) % (new_line) == 0) {
            string += "\n";
        }
    }

    string += "\n";

    for (unsigned i = 0; i < indices.size(); i++) {
        string += std::to_string(indices[i]) + " ";
        if ((i + 1) % (new_line) == 0) {
            string += "\n";
        }
    }

    string += "\n";
    string += std::to_string(vertices_count);

    return string;
}
