//
//  GLTextureLoader.hpp
//  gl_wrapper
//
//  Created by Vladas Zakrevskis on 3/4/19.
//  Copyright © 2019 VladasZ. All rights reserved.
//

#include "Size.hpp"

namespace gl {

using TextureID = unsigned int;

struct TextureLoader {
    static TextureID load(const void* data, const gm::Size& size, unsigned int channels);
    static void bind(TextureID);
    static void free(TextureID);
};

}
