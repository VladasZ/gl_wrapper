//
//  Buffer.hpp
//  gl_wrapper
//
//  Created by Vladas Zakrevskis on 8/28/17.
//  Copyright © 2017 VladasZ. All rights reserved.
//

#pragma once

#include <string>
#include <vector>

#include "Shader.hpp"

namespace gl {

class BufferData;
class BufferConfiguration;

class Buffer {
    
    BufferData* data;
    
    unsigned int vertex_array_object  = 0;
    unsigned int vertex_buffer_object = 0;
    unsigned int index_buffer_object  = 0;

    Shader* _shader;

private:

    void _initialize(BufferData* data, const BufferConfiguration& configuration, Shader* shader);

public:
    
    unsigned int draw_mode;

    Buffer(BufferData* data, const BufferConfiguration& configuration, Shader* shader);
    
    Buffer(const std::vector<float>& vertices,
           const std::vector<unsigned short>& indices,
           const BufferConfiguration& configuration,
           Shader* shader);

    ~Buffer();

    void bind() const;
    void draw() const;

    Shader* shader() const;

    std::string to_string(unsigned int new_line = 3) const;

};

}
