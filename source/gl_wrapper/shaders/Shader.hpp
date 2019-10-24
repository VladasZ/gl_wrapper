//
//  Shader.hpp
//  gl_wrapper
//
//  Created by Vladas Zakrevskis on 8/30/17.
//  Copyright © 2017 VladasZ. All rights reserved.
//

#pragma once

#include <string>

#include "Rect.hpp"
#include "Color.hpp"
#include "Matrix4.hpp"

namespace gl {

class Shader {

    using ID = unsigned int;

    ID _program = 0;

    int _uniform_color;
    int _mvp_matrix;
    int _model_matrix;
    int _light_position;
    int _size;
	int _selected;
	int _resolution;
	int _position;
	int _rotation;

public:
    
    Shader() = default;
    Shader(const std::string& path);

    const std::string path;

    void use() const;

    ID get_program_id() const;

    void set_uniform_color(const gm::Color &);
    void set_mvp_matrix(const gm::Matrix4&);
    void set_model_matrix(const gm::Matrix4&);
    void set_light_position(const gm::Vector3&);
    void set_size(const gm::Size&);
	void set_selected(bool);
	void set_resolution(const gm::Size&);
	void set_position(const gm::Point&);
	void set_rotation(float);
};

}
