//
//  Buffer.hpp
//  gl_wrapper
//
//  Created by Vladas Zakrevskis on 8/28/17.
//  Copyright © 2017 VladasZ. All rights reserved.
//

#pragma once

#include <vector>

#include "Shader.hpp"
#include "Vertex.hpp"
#include "ArrayView.hpp"
#include "PointsPath.hpp"
#include "BufferConfiguration.hpp"


namespace gl {

    class Buffer {

        template <class T>
        using Array = cu::ArrayView<T>;

        const Array<gm::Float> vertices_data;
        const Array<gm::Vertex::Index> indices;

        const size_t vertices_count;

        const BufferConfiguration& configuration;

        unsigned vertex_array_object  = 0;
        unsigned vertex_buffer_object = 0;
        unsigned index_buffer_object  = 0;


    public:

        unsigned draw_mode;


        Buffer(const Array<gm::Float>& vertices_data, const Array<gm::Vertex::Index>& indices, const BufferConfiguration& configuration);
        Buffer(const Array<gm::Float>& vertices_data, size_t vertices_count,                   const BufferConfiguration& configuration);

        ~Buffer();

        void draw() const;

        std::string to_string(unsigned new_line = 3) const;

    private:

        void _init();

    };

}
