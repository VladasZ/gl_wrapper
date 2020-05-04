//
//  BufferData.hpp
//  gl_wrapper
//
//  Created by Vladas Zakrevskis on 9/17/17.
//  Copyright © 2017 VladasZ. All rights reserved.
//

#pragma once

#include <string>
#include <vector>

#include "Vertex.hpp"
#include "Geometry.hpp"
#include "ArrayView.hpp"


namespace gl {

    class BufferData {

    public:

        template <class T>
        using Array = cu::ArrayView<T>;

        const Array<gm::Float> vertices_data;
        const Array<gm::Vertex::Index> indices;

        const size_t vertices_count;

        BufferData(const Array<gm::Float>& vertices_data, const Array<gm::Vertex::Index>& indices);
        BufferData(const Array<gm::Float>& vertices_data, size_t vertices_count);

        std::string to_string(unsigned int new_line = 3) const;

    };

}
