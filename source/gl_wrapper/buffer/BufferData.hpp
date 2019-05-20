//
//  BufferData.hpp
//  gl_wrapper
//
//  Created by Vladas Zakrevskis on 9/17/17.
//  Copyright © 2017 VladasZ. All rights reserved.
//

#pragma once

#include <vector>
#include <string>

#include "Size.hpp"
#include "Rect.hpp"

namespace gl {

class Buffer;

class BufferData {
    
    const std::vector<float> vertices_data;
    const std::vector<unsigned short> indices;

    const size_t vertices_count;
    
    friend Buffer;
    
public:
        
    BufferData(const std::vector<float>& vertices_data, const std::vector<unsigned short>& indices);
    BufferData(const std::vector<float>& vertices_data, size_t vertices_count);

    std::string to_string(unsigned int new_line = 3) const;
    
    static BufferData* from_size               (const gm::Size&);
    static BufferData* from_rect               (const gm::Rect&);
    static BufferData* from_rect_to_image      (const gm::Rect&);
    static BufferData* from_rect_to_rectangle  (const gm::Rect&);
    static BufferData* from_rect_to_framebuffer(const gm::Rect&);
};

}
