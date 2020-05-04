//
//  BufferConfiguration.cpp
//  gl_wrapper
//
//  Created by Vladas Zakrevskis on 9/23/17.
//  Copyright © 2017 VladasZ. All rights reserved.
//

#include "Log.hpp"
#include "GLDebug.hpp"
#include "OpenGLHeaders.hpp"
#include "BufferConfiguration.hpp"

using namespace gl;


BufferConfiguration::BufferConfiguration(uint8_t first, uint8_t second, uint8_t third) {

    if (first == 0) Fatal("Zero BufferConfiguration");

    configuration[0] = first;
    configuration[1] = second;
    configuration[2] = third;

    size = 1;
    if (second > 0) size++;
    if (third  > 0) size++;

    vertex_size = first + second + third;

}

uint8_t BufferConfiguration::stride_for_index(uint8_t index) const {
    if (index == 0) return 0;
    if (index == 1) return vertex_size - configuration[1] - configuration[2];
                    return vertex_size                    - configuration[2];
}

void BufferConfiguration::set_pointers() const {
    for (uint8_t i = 0; i < size; i++) {
        GL(glEnableVertexAttribArray(i));
        GL(glVertexAttribPointer(i,
                                 configuration[i],
                                 GL_FLOAT,
                                 GL_FALSE,
                                 vertex_size * sizeof(GLfloat),
                                 reinterpret_cast<GLvoid*>(stride_for_index(i) * sizeof(GLfloat))));
    }
}

const BufferConfiguration BufferConfiguration::_2     { 2, 0, 0 };
const BufferConfiguration BufferConfiguration::_2_2   { 2, 2, 0 };
const BufferConfiguration BufferConfiguration::_3_3   { 3, 3, 0 };
const BufferConfiguration BufferConfiguration::_3_3_2 { 3, 3, 2 };
const BufferConfiguration BufferConfiguration::_3_3_3 { 3, 3, 3 };
const BufferConfiguration BufferConfiguration::_3_3_4 { 3, 3, 4 };
