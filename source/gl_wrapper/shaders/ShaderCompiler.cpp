//
//  ShaderCompiler.cpp
//  test_engine
//
//  Created by Vladas Zakrevskis on 8/17/17.
//  Copyright © 2017 VladasZ. All rights reserved.
//

#include <cstdio>
#include <vector>
#include <fstream>
#include <stdlib.h>
#include <algorithm>

#include "GLDebug.hpp"
#include "OpenGLHeaders.hpp"
#include "ShaderCompiler.hpp"

using namespace std;

#ifdef IOS_BUILD
static const string version = "#version 300 core";
#else
static const string version = "#version 330 core";
#endif

unsigned int ShaderCompiler::compile(const string& vertex_path, const string& fragment_path)
{
	GLuint vertex = GL(glCreateShader(GL_VERTEX_SHADER));
	GLuint fragment = GL(glCreateShader(GL_FRAGMENT_SHADER));

	string vertex_code = version;
	ifstream vertex_stream(vertex_path.c_str(), ios::in);

#if SHADER_COMPILER_OUTPUT

	Log(vertex_path);
	Log(fragment_path);

#endif

	if (vertex_stream.is_open()) {
		string line = "";
		while (getline(vertex_stream, line))
			vertex_code += "\n" + line;
		vertex_stream.close();
	}
	else {
		Fatal("Impossible to open " << vertex_path.c_str());
	}

	string fragment_code = version;
	ifstream fragment_stream(fragment_path.c_str(), ios::in);

	if (fragment_stream.is_open()) {
		string line = "";
		while (getline(fragment_stream, line))
			fragment_code += "\n" + line;
		fragment_stream.close();
	}

	GLint result = GL_FALSE;
	int info_length;

#if SHADER_COMPILER_OUTPUT
	Log("Compiling shader :" << vertex_path.c_str());
#endif

	char const* vertex_code_pointer = vertex_code.c_str();
	GL(glShaderSource(vertex, 1, &vertex_code_pointer, NULL));
	GL(glCompileShader(vertex));

	GL(glGetShaderiv(vertex, GL_COMPILE_STATUS, &result));
	GL(glGetShaderiv(vertex, GL_INFO_LOG_LENGTH, &info_length));

	if (info_length > 0) {
		vector<char> vertex_error_message(info_length + 1);
		GL(glGetShaderInfoLog(vertex, info_length, NULL, &vertex_error_message[0]));
		Error(&vertex_error_message[0]);
	}

#if SHADER_COMPILER_OUTPUT
	Log("Compiling shader :" << fragment_path.c_str());
#endif

	char const* fragment_code_pointer = fragment_code.c_str();
	GL(glShaderSource(fragment, 1, &fragment_code_pointer, NULL));
	GL(glCompileShader(fragment));

	GL(glGetShaderiv(fragment, GL_COMPILE_STATUS, &result));
	GL(glGetShaderiv(fragment, GL_INFO_LOG_LENGTH, &info_length));

	if (info_length > 0) {
		vector<char> fragment_error(info_length + 1);
		GL(glGetShaderInfoLog(fragment, info_length, NULL, &fragment_error[0]));
		Error(&fragment_error[0]);
	}

#if SHADER_COMPILER_OUTPUT
	Log("Linking program");
#endif

	GLuint program = glCreateProgram();
	GL(glAttachShader(program, vertex));
	GL(glAttachShader(program, fragment));
	GL(glLinkProgram(program));

	GL(glGetProgramiv(program, GL_LINK_STATUS, &result));
	GL(glGetProgramiv(program, GL_INFO_LOG_LENGTH, &info_length));

	if (info_length > 0) {
		vector<char> program_error(info_length + 1);
		GL(glGetProgramInfoLog(program, info_length, NULL, &program_error[0]));
		Error(&program_error[0]);

		if (program_error[0] == 'E')
			std::terminate();
	}

	GL(glDetachShader(program, vertex));
	GL(glDetachShader(program, fragment));

	GL(glDeleteShader(vertex));
	GL(glDeleteShader(fragment));

	return program;
}
