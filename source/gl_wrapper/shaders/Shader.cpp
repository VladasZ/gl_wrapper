//
//  Shader.cpp
//  gl_wrapper
//
//  Created by Vladas Zakrevskis on 8/30/17.
//  Copyright © 2017 VladasZ. All rights reserved.
//

#include "Shader.hpp"
#include "GLDebug.hpp"
#include "OpenGLHeaders.hpp"
#include "ShaderCompiler.hpp"

using namespace gl;


#define GET_UNIFORM(uni) uni = glGetUniformLocation(program, #uni)

Shader::Shader(const std::string& path) : path(path) {

    program = ShaderCompiler::compile(path);

    GET_UNIFORM(color);
    GET_UNIFORM(mvp_matrix);
    GET_UNIFORM(model_matrix);
    GET_UNIFORM(light_position);
    GET_UNIFORM(size);
    GET_UNIFORM(selected);
    GET_UNIFORM(resolution);
    GET_UNIFORM(position);
    GET_UNIFORM(rotation);
    GET_UNIFORM(camera_position);
    GET_UNIFORM(flip);

}

void Shader::use() const {
    GL(glUseProgram(program));
}

Shader::ID Shader::get_program_id() const {
    return program;
}

void Shader::set_color(const gm::Color& c) const {
    GL(glUniform4fv(color, 1, &c.r));
}

void Shader::set_mvp_matrix(const gm::Matrix4& mvp) const {
    GL(glUniformMatrix4fv(mvp_matrix, 1, false, &mvp.data[0][0]));
}

void Shader::set_model_matrix(const gm::Matrix4& mat) const {
    GL(glUniformMatrix4fv(model_matrix, 1, false, &mat.data[0][0]));
}

void Shader::set_light_position(const gm::Vector3& pos) const {
    GL(glUniform3fv(light_position, 1, &pos.x));
}

void Shader::set_size(const gm::Size& s) const {
    GL(glUniform2fv(size, 1, &s.width));
}

void Shader::set_selected(bool s) const {
    GL(glUniform1i(selected, s));
}

void Shader::set_resolution(const gm::Size& res) const {
    GL(glUniform2fv(resolution, 1, &res.width));
}

void Shader::set_position(const gm::Point& point) const {
    GL(glUniform2fv(position, 1, &point.x));
}

void Shader::set_rotation(float angle) const {
    GL(glUniform1f(rotation, angle));
}

void Shader::set_camera_position(const gm::Point& pos) const {
    GL(glUniform2fv(camera_position, 1, &pos.x));
}

void Shader::set_flip(bool f) const {
    GL(glUniform1i(flip, f));
}
