//
//  Buffer.cpp
//  gl_wrapper
//
//  Created by Vladas Zakrevskis on 8/28/17.
//  Copyright © 2017 VladasZ. All rights reserved.
//

#include <string>

#include "Buffer.hpp"
#include "GLDebug.hpp"
#include "OpenGLHeaders.hpp"
#include "BufferConfiguration.hpp"

using namespace gl;
using namespace gm;


Buffer::Buffer(const BufferConfiguration& configuration, const Buffer::Array<Float>& vertices_data,
               const Buffer::Array<Vertex::Index>& indices)
    :
    vertices_data(vertices_data),
    indices(indices),
    vertices_count(indices.size() == 0 ? vertices_data.size() / configuration.size() : -1) ,
    configuration(configuration)
    {
        draw_mode = GL_TRIANGLES;

        GL(glGenVertexArrays(1, &vertex_array_object));
        GL(glBindVertexArray(vertex_array_object));

        GL(glGenBuffers(1, &vertex_buffer_object));
        GL(glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_object));
        GL(glBufferData(GL_ARRAY_BUFFER,
                        static_cast<uint16_t>(vertices_data.size() * sizeof(GLfloat)),
                        vertices_data.data(),
                        GL_STATIC_DRAW));

        if (!indices.empty()) {
            GL(glGenBuffers(1, &index_buffer_object));
            GL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer_object));
            GL(glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                            static_cast<uint16_t>(indices.size() * sizeof(GLushort)),
                            indices.data(),
                            GL_STATIC_DRAW));
        }

        configuration.set_pointers();
        GL(glBindVertexArray(0));
}

Buffer::~Buffer() {
    GL(glDeleteBuffers(1, &vertex_buffer_object));
    if (index_buffer_object != 0) {
        GL(glDeleteBuffers(1, &index_buffer_object));
    }
    GL(glDeleteVertexArrays(1, &vertex_array_object));
}

void Buffer::draw() const {
    GL(glBindVertexArray(vertex_array_object));
    if (indices.empty()) {
        GL(glDrawArrays(draw_mode, 0, static_cast<GLsizei>(vertices_count)));
    } else {
        GL(glDrawElements(draw_mode, static_cast<GLsizei>(indices.size()), GL_UNSIGNED_SHORT, nullptr));
    }
    GL(glBindVertexArray(0));
}

std::string Buffer::to_string(unsigned new_line) const {
    std::string string;
    string = "\n";

    for (int i = 0; i < vertices_data.size(); i++) {
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
