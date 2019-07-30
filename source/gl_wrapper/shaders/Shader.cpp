//
//  Shader.cpp
//  gl_wrapper
//
//  Created by Vladas Zakrevskis on 8/30/17.
//  Copyright © 2017 VladasZ. All rights reserved.
//

#include "Log.hpp"
#include "Shader.hpp"
#include "GLDebug.hpp"
#include "OpenGLHeaders.hpp"
#include "ShaderCompiler.hpp"

using namespace gl;

Shader::Shader(const std::string& directory, const std::string& name) : name(name), path(directory) {
    _program = ShaderCompiler::compile(directory + "/" + name + ".vert",
                                       directory + "/" + name + ".frag");

    _uniform_color  = glGetUniformLocation(_program, "uniform_color" );
    _mvp_matrix     = glGetUniformLocation(_program, "mvp_matrix"    );
    _model_matrix   = glGetUniformLocation(_program, "model_matrix"  );
    _light_position = glGetUniformLocation(_program, "light_position");
    _size           = glGetUniformLocation(_program, "size"          );
	_selected       = glGetUniformLocation(_program, "selected"      );
	_resolution     = glGetUniformLocation(_program, "resolution"    );
	_position       = glGetUniformLocation(_program, "position"      );
}

void Shader::use() const {
    GL(glUseProgram(_program));
}

Shader::ID Shader::get_program_id() const {
    return _program;
}

void Shader::set_uniform_color(const gm::Color& color) {
    GL(glUniform4fv(_uniform_color, 1, &color.r));
}

void Shader::set_mvp_matrix(const gm::Matrix4& mvp) {
    GL(glUniformMatrix4fv(_mvp_matrix, 1, false, &mvp.data[0][0]));
}

void Shader::set_model_matrix(const gm::Matrix4& model_matrix) {
    GL(glUniformMatrix4fv(_model_matrix, 1, false, &model_matrix.data[0][0]));
}

void Shader::set_light_position(const gm::Vector3& light_position) {
    GL(glUniform3fv(_light_position, 1, &light_position.x));
}

void Shader::set_size(const gm::Size& size) {
    GL(glUniform2fv(_size, 1, &size.width));
}

void Shader::set_selected(bool selected) {
    GL(glUniform1i(_selected, selected));
}

void Shader::set_resolution(const gm::Size& resolution) {
	GL(glUniform2fv(_resolution, 1, &resolution.width));
}

void Shader::set_position(const gm::Point& point) {
	GL(glUniform2fv(_position, 1, &point.x));
}
