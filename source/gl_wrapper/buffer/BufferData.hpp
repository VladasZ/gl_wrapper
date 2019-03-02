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

class Buffer;

class BufferData {
    
    std::vector<float>    vertices_data;
    std::vector<unsigned short> indices;
    
    friend Buffer;
    
public:
        
    BufferData(const std::vector<float>& vertices_data, const std::vector<unsigned short>& indices = { });

    std::string to_string(unsigned int new_line = 3) const;
    
    static BufferData* from_size               (const Size&);
    static BufferData* from_rect               (const Rect&);
    static BufferData* from_rect_to_image      (const Rect&);
    static BufferData* from_rect_to_framebuffer(const Rect&);
};
