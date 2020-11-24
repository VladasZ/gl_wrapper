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


Shader::Shader(const std::string& path) : path(path) {

    _program = ShaderCompiler::compile(path);

    _color          = glGetUniformLocation(_program, "color"         );
    _mvp_matrix     = glGetUniformLocation(_program, "mvp_matrix"    );
    _model_matrix   = glGetUniformLocation(_program, "model_matrix"  );
    _light_position = glGetUniformLocation(_program, "light_position");
    _size           = glGetUniformLocation(_program, "size"          );
    _selected       = glGetUniformLocation(_program, "selected"      );
    _resolution     = glGetUniformLocation(_program, "resolution"    );
    _position       = glGetUniformLocation(_program, "position"      );
    _rotation       = glGetUniformLocation(_program, "rotation"      );
}

void Shader::use() const {
    GL(glUseProgram(_program));
}

Shader::ID Shader::get_program_id() const {
    return _program;
}

void Shader::set_color(const gm::Color& color) const {
    GL(glUniform4fv(_color, 1, &color.r));
}

void Shader::set_mvp_matrix(const gm::Matrix4& mvp) const {
    GL(glUniformMatrix4fv(_mvp_matrix, 1, false, &mvp.data[0][0]));
}

void Shader::set_model_matrix(const gm::Matrix4& model_matrix) const {
    GL(glUniformMatrix4fv(_model_matrix, 1, false, &model_matrix.data[0][0]));
}

void Shader::set_light_position(const gm::Vector3& light_position) const {
    GL(glUniform3fv(_light_position, 1, &light_position.x));
}

void Shader::set_size(const gm::Size& size) const {
    GL(glUniform2fv(_size, 1, &size.width));
}

void Shader::set_selected(bool selected) const {
    GL(glUniform1i(_selected, selected));
}

void Shader::set_resolution(const gm::Size& resolution) const {
    GL(glUniform2fv(_resolution, 1, &resolution.width));
}

void Shader::set_position(const gm::Point& point) const {
    GL(glUniform2fv(_position, 1, &point.x));
}

void Shader::set_rotation(float angle) const {
    GL(glUniform1f(_rotation, angle));
}

void Shader::set_camera_position(const gm::Point& pos) const {
    GL(glUniform2fv(_camera_position, 1, &pos.x));
}
