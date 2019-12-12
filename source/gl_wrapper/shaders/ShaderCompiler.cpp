//
//  ShaderCompiler.cpp
//  test_engine
//
//  Created by Vladas Zakrevskis on 8/17/17.
//  Copyright � 2017 VladasZ. All rights reserved.
//

#include <regex>
#include <string>
#include <vector>
#include <unordered_map>

#include "File.hpp"
#include "GLDebug.hpp"
#include "StringUtils.hpp"
#include "OpenGLHeaders.hpp"
#include "ShaderCompiler.hpp"
#include "ExceptionCatch.hpp"

using namespace cu;
using namespace std;

#if defined(IOS_BUILD) || defined(ANDROID_BUILD)
static const string version = "#version 300 es\n";
#else
static const string version = "#version 330 core\n";
#endif

const static string quotes_query = R"(("[^ "]+"))";
const static string include_query = "#include " + quotes_query;

static char errror_message_buffer[1024];

static void check_programm_error(GLuint program) {
#ifdef ANDROID_BUILD
    return;
#else
	static GLint log_length;
	GL(glGetShaderiv(program, GL_INFO_LOG_LENGTH, &log_length));
	if (log_length > 2) {
	    char* message = errror_message_buffer;
		GL(glGetShaderInfoLog(program, log_length, nullptr, message));
		Fatal(message);
	}
#endif
}

static GLuint compile_shader(const string& code, unsigned type) {
	auto shader = GL(glCreateShader(type));
	auto code_pointer = code.c_str();
	GL(glShaderSource(shader, 1, &code_pointer, nullptr));
	GL(glCompileShader(shader));
	check_programm_error(shader);
	return shader;
}

static void unfold_includes(std::string& code) {

	auto includes = String::find_regexpr_matches(code, include_query);

	unordered_map<string, string> files;

	for (auto include : includes) {
		auto file_name = String::find_regexpr_match(include, quotes_query);
		String::trim(file_name);
		auto file_path = ShaderCompiler::includes_path + "/" + file_name;
		auto include_code = File::read_to_string(file_path);
		files[include] = include_code;
	}

	for (auto [include, include_code] : files) {
		String::replace(include, include_code, code);
	}

	code = version + code;
}

unsigned ShaderCompiler::compile(const std::string& path) {

	unsigned program;

	auto vertex_code   = File::read_to_string(path + ".vert");
	auto fragment_code = File::read_to_string(path + ".frag");

	unfold_includes(vertex_code);
	unfold_includes(fragment_code);

	auto vertex   = compile_shader(vertex_code, GL_VERTEX_SHADER);
	auto fragment = compile_shader(fragment_code, GL_FRAGMENT_SHADER);

	program = glCreateProgram();
	Logvar(program);
	GL(glAttachShader(program, vertex));
	GL(glAttachShader(program, fragment));
	GL(glLinkProgram(program));

	check_programm_error(program);

	GL(glDetachShader(program, vertex));
	GL(glDetachShader(program, fragment));

	GL(glDeleteShader(vertex));
	GL(glDeleteShader(fragment));

	Log("Shader compiled:");
	Logvar(path);
	Logvar(program);

	return program;
}
