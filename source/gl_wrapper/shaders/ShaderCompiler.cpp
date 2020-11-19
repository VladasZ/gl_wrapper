//
//  ShaderCompiler.cpp
//  test_engine
//
//  Created by Vladas Zakrevskis on 8/17/17.
//  Copyright © 2017 VladasZ. All rights reserved.
//

#include <regex>
#include <string>
#include <unordered_map>

#include "Log.hpp"
#include "File.hpp"
#include "GLDebug.hpp"
#include "GLWrapper.hpp"
#include "StringUtils.hpp"
#include "OpenGLHeaders.hpp"
#include "ShaderCompiler.hpp"

using namespace cu;
using namespace std;


static string version() {

    string result = "#version ";
    result += to_string(GL::glsl_version_number);

    if (GL::is_gles) {
        if (GL::gl_major_version > 2) {
            result += " es";
        }
    }
    else {
        result += " core";
    }

    result += "\n";

    return result;
}

static string defines(unsigned type) {

    if (!GL::is_gl2) {
        return
        "#define IN in\n"
        "#define OUT out\n";
    }

    if (type == GL_VERTEX_SHADER) {
        return
        "#define IN attribute\n"
        "#define OUT varying\n";
    }

    return
    "#define IN varying\n"
    "#define OUT\n";

}

const static string quotes_query = R"(("[^ "]+"))";
const static string include_query = "#include " + quotes_query;

static char errror_message_buffer[1024];

static void check_programm_error(const std::string& file_name, GLuint program) {
#ifdef ANDROID_BUILD
    return;
#else
	static GLint log_length;
    glGetShaderiv(program, GL_INFO_LOG_LENGTH, &log_length);
 //   GL(glGetShaderiv(program, GL_INFO_LOG_LENGTH, &log_length));
    glGetError();
	if (log_length > 2) {
	    char* message = errror_message_buffer;
		GL(glGetShaderInfoLog(program, log_length, nullptr, message));
        Log << file_name;
		Fatal(message);
	}
#endif
}

static void unfold_includes(std::string& code) {

	auto includes = String::find_regexpr_matches(code, include_query);

	unordered_map<string, string> files;

	for (auto& include : includes) {
		auto file_name = String::find_regexpr_match(include, quotes_query);
		String::trim(file_name);
		auto file_path = ShaderCompiler::includes_path + "/" + file_name;
		auto include_code = File::read(file_path);
		files[include] = include_code;
	}

	for (auto& [include, include_code] : files) {
		String::replace(include, include_code, code);
	}

}

static GLuint compile_shader(const std::string& file_name, string& code, unsigned type) {
    
    unfold_includes(code);
    
    code = version() + "\n" + defines(type) + "\n" + code;

    auto shader = GL(glCreateShader(type));
    auto code_pointer = code.c_str();
    GL(glShaderSource(shader, 1, &code_pointer, nullptr));
    GL(glCompileShader(shader));
    check_programm_error(file_name, shader);
    return shader;
}

unsigned ShaderCompiler::compile(const std::string& path) {

#ifdef SHADER_COMPILER_OUTPUT
    Log << "Compiling: " + path;
#endif
    
	unsigned program;

	auto vertex_code   = File::read(path + ".vert");
	auto fragment_code = File::read(path + ".frag");

	auto vertex   = compile_shader(path + ".vert", vertex_code,   GL_VERTEX_SHADER);
	auto fragment = compile_shader(path + ".frag", fragment_code, GL_FRAGMENT_SHADER);

	program = glCreateProgram();
	GL(glAttachShader(program, vertex));
	GL(glAttachShader(program, fragment));
	GL(glLinkProgram(program));

	check_programm_error(path, program);

    GL(glDetachShader(program, vertex));
	GL(glDetachShader(program, fragment));

	GL(glDeleteShader(vertex));
	GL(glDeleteShader(fragment));

	return program;
}
