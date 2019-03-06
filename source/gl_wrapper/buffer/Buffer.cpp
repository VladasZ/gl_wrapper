//
//  Buffer.cpp
//  gl_wrapper
//
//  Created by Vladas Zakrevskis on 8/28/17.
//  Copyright © 2017 VladasZ. All rights reserved.
//

#include <string>

#include              "Buffer.hpp"
#include             "GLDebug.hpp"
#include          "BufferData.hpp"
#include       "OpenGLHeaders.hpp"
#include "BufferConfiguration.hpp"

using namespace gl;

void Buffer::_initialize(BufferData* data, const BufferConfiguration& configuration, Shader* shader) {

    _shader = shader;

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

Buffer::Buffer(BufferData* data, const BufferConfiguration& configuration, Shader* shader) {
    _initialize(data, configuration, shader);
}

Buffer::Buffer(const std::vector<float>& vertices,
               const std::vector<unsigned short>& indices,
               const BufferConfiguration& configuration,
               Shader* shader)
    : Buffer(new BufferData(vertices, indices), configuration, shader) { }

Buffer::~Buffer() {
    GL(glDeleteBuffers(1, &vertex_buffer_object));
    if (index_buffer_object != 0)
        GL(glDeleteBuffers(1, &index_buffer_object));
    GL(glDeleteVertexArrays(1, &vertex_array_object));
    delete data;
}

void Buffer::bind() const {
    _shader->use();
    GL(glBindVertexArray(vertex_array_object));
}

void Buffer::draw() const {
    if (data->indices.empty()) {
        GL(glDrawArrays(draw_mode, 0, static_cast<GLsizei>(data->vertices_data.size())));
    } else {
        GL(glDrawElements(draw_mode, static_cast<GLsizei>(data->indices.size()), GL_UNSIGNED_SHORT, nullptr));
    }
    GL(glBindVertexArray(0));
}

Shader* Buffer::shader() const {
    return _shader;
}

std::string Buffer::to_string(unsigned int new_line) const {
    return data->to_string(new_line);
}
