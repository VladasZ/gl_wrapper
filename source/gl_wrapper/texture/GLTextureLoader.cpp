//
//  GLTextureLoader.cpp
//  gl_wrapper
//
//  Created by Vladas Zakrevskis on 3/4/19.
//  Copyright © 2019 VladasZ. All rights reserved.
//

#include "GLDebug.hpp"
#include "OpenGLHeaders.hpp"
#include "GLTextureLoader.hpp"

using namespace gl;

static unsigned int mode_for_channels(unsigned int channels) {
    switch (channels) {
#if IOS_BUILD
    case 1: return GL_LUMINANCE;
#else
    case 1: return GL_RED;
#endif
    default: return GL_RGBA;
    }
}

TextureID TextureLoader::load(const void* data, const gm::Size& size, unsigned int channels) {

    TextureID id;

    GL(glGenTextures(1, &id));

    GL(glBindTexture(GL_TEXTURE_2D, id));

    if (channels == 1)
        GL(glPixelStorei(GL_UNPACK_ALIGNMENT, 1));

    GL(glTexImage2D(GL_TEXTURE_2D,
                    0,
                    static_cast<GLint>(mode_for_channels(channels)),
                    static_cast<GLsizei>(size.width),
                    static_cast<GLsizei>(size.height),
                    0,
                    mode_for_channels(channels),
                    GL_UNSIGNED_BYTE,
                    data));

    GL(glGenerateMipmap(GL_TEXTURE_2D));

    GL(glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    GL(glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

    return id;
}

void TextureLoader::bind(TextureID id) {
    GL(glBindTexture(GL_TEXTURE_2D, id));
}

void TextureLoader::free(TextureID id) {
    GL(glDeleteTextures(1, &id));
}
