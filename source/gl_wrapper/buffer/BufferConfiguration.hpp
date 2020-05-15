//
//  BufferConfiguration.hpp
//  gl_wrapper
//
//  Created by Vladas Zakrevskis on 9/23/17.
//  Copyright © 2017 VladasZ. All rights reserved.
//

#pragma once

#include <cstdint>

#include "NonCopyable.hpp"


namespace gl {

    class BufferConfiguration : cu::NonCopyable {

    private:

        uint8_t _size;
        uint8_t _configuration[3];
        uint8_t _vertex_size = 0;

        uint8_t stride_for_index(uint8_t index) const;

        explicit BufferConfiguration(uint8_t, uint8_t, uint8_t);

    public:

        uint8_t size() const;
        void set_pointers() const;

    public:

        static const BufferConfiguration _2;
        static const BufferConfiguration _2_2;
        static const BufferConfiguration _3_3;
        static const BufferConfiguration _3_3_2;
        static const BufferConfiguration _3_3_3;
        static const BufferConfiguration _3_3_4;

    };

}
