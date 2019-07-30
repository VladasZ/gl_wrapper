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

#include "Path.hpp"
#include "Shader.hpp"
#include "Vertex.hpp"

namespace gl {

class BufferData;
class BufferConfiguration;

class Buffer {
    
    BufferData* data;
    
    unsigned int vertex_array_object  = 0;
    unsigned int vertex_buffer_object = 0;
    unsigned int index_buffer_object  = 0;

private:

    void _initialize(BufferData* data, const BufferConfiguration& configuration);

public:
    
    unsigned int draw_mode;

    Buffer(BufferData* data, const BufferConfiguration& configuration);
    
    Buffer(const std::vector<float>& vertices_data,
           const gm::Vertex::Indices& indices,
           const BufferConfiguration& configuration);

    Buffer(gm::Path*);

    ~Buffer();

    void bind() const;
    void draw() const;

    BufferData* buffer_data() const;

    std::string to_string(unsigned int new_line = 3) const;

};

}
