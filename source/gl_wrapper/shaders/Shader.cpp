//
//  Shader.cpp
//  gl_wrapper
//
//  Created by Vladas Zakrevskis on 8/30/17.
//  Copyright © 2017 VladasZ. All rights reserved.
//

#include            "Log.hpp"
#include         "Shader.hpp"
#include        "GLDebug.hpp"
#include  "OpenGLHeaders.hpp"
#include "ShaderCompiler.hpp"

using namespace gl;

Shader::Shader(const std::string& directory, const std::string& name) : name(name), path(directory) {
    _program = ShaderCompiler::compile(directory + name + ".vert",
                                       directory + name + ".frag");

    _uniform_color  = glGetUniformLocation(_program, "uniform_color" );
    _mvp_matrix     = glGetUniformLocation(_program, "mvp_matrix"    );
    _model_matrix   = glGetUniformLocation(_program, "model_matrix"  );
    _light_position = glGetUniformLocation(_program, "light_position");
}

void Shader::use() const {
    GL(glUseProgram(_program));
}

unsigned int Shader::get_program_id() const {
    return _program;
}

void Shader::set_uniform_color(const Color& color) {
    if (_uniform_color != -1)
        GL(glUniform4fv(_uniform_color, 1, &color.r));
}

void Shader::set_mvp_matrix(const Matrix4& mvp) {
    if (_mvp_matrix != -1)
        GL(glUniformMatrix4fv(_mvp_matrix, 1, false, &mvp.data[0][0]));
}

void Shader::set_model_matrix(const Matrix4& model_matrix) {
    if (_model_matrix != -1)
        GL(glUniformMatrix4fv(_model_matrix, 1, false, &model_matrix.data[0][0]));
}

void Shader::set_light_position(const Vector3& light_position) {
    if (_light_position != -1)
        GL(glUniform3fv(_light_position, 1, &light_position.x));
}
