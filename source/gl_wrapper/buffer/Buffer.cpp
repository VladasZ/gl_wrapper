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
#include "GLWrapper.hpp"
#include "BufferData.hpp"
#include "OpenGLHeaders.hpp"
#include "BufferConfiguration.hpp"

using namespace gl;

void Buffer::_initialize(BufferData* data, const BufferConfiguration& configuration) {

    this->data = data;
    draw_mode = GL_TRIANGLES;

    GL(glGenVertexArrays(1, &vertex_array_object));
    GL(glBindVertexArray(vertex_array_object));

    GL(glGenBuffers(1, &vertex_buffer_object));
    GL(glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_object));
    GL(glBufferData(GL_ARRAY_BUFFER,
                    static_cast<uint16_t>(data->vertices_data.size() * sizeof(GLfloat)),
                    data->vertices_data.data(),
                    GL_STATIC_DRAW));

    if (!data->indices.empty()) {
        GL(glGenBuffers(1, &index_buffer_object));
        GL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer_object));
        GL(glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                        static_cast<uint16_t>(data->indices.size() * sizeof(GLushort)),
                        data->indices.data(),
                        GL_STATIC_DRAW));
    }

    configuration.set_pointers();
    GL(glEnableVertexAttribArray(0));
    GL(glBindVertexArray(0));
}

Buffer::Buffer(BufferData* data, const BufferConfiguration& configuration) {
    _initialize(data, configuration);
}

Buffer::Buffer(const std::vector<float>& vertices,
               const gm::Vertex::Indices& indices,
               const BufferConfiguration& configuration)
    : Buffer(new BufferData(vertices, indices), configuration) { }

Buffer::Buffer(gm::Path* path)
    : Buffer(new BufferData(path->floats_vector(), path->points().size()), BufferConfiguration::_2) {

    draw_mode = GL::DrawMode::LineStrip;

    if (path->draw_mode == gm::Path::DrawMode::Lines)
        draw_mode = GL::DrawMode::Lines;
}

Buffer::~Buffer() {
    GL(glDeleteBuffers(1, &vertex_buffer_object));
    if (index_buffer_object != 0) {
        GL(glDeleteBuffers(1, &index_buffer_object));
    }
    GL(glDeleteVertexArrays(1, &vertex_array_object));
    delete data;
}

void Buffer::draw() const {
	GL(glBindVertexArray(vertex_array_object));
    if (data->indices.empty()) {
        GL(glDrawArrays(draw_mode, 0, static_cast<GLsizei>(data->vertices_count)));
    } else {
        GL(glDrawElements(draw_mode, static_cast<GLsizei>(data->vertices_count), GL_UNSIGNED_SHORT, nullptr));
    }
    GL(glBindVertexArray(0));
}

BufferData* Buffer::buffer_data() const {
    return data;
}

std::string Buffer::to_string(unsigned new_line) const {
    return data->to_string(new_line);
}
