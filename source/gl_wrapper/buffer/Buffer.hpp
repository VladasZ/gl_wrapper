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
#include "Vertex.hpp"
#include "PointsPath.hpp"

namespace gl {

class BufferData;
class BufferConfiguration;

class Buffer {
    
    BufferData* data;
    
    unsigned vertex_array_object  = 0;
    unsigned vertex_buffer_object = 0;
    unsigned index_buffer_object  = 0;

private:

    void _initialize(BufferData* data, const BufferConfiguration& configuration);

public:
    
    unsigned draw_mode;

    Buffer(BufferData* data, const BufferConfiguration& configuration);
    
    Buffer(const std::vector<float>& vertices_data,
           const gm::Vertex::Indices& indices,
           const BufferConfiguration& configuration);

    Buffer(gm::PointsPath*);

    ~Buffer();

    void draw() const;

    BufferData* buffer_data() const;

    std::string to_string(unsigned new_line = 3) const;

};

}
