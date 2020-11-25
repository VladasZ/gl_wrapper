//
//  Shader.hpp
//  gl_wrapper
//
//  Created by Vladas Zakrevskis on 8/30/17.
//  Copyright © 2017 VladasZ. All rights reserved.
//

#pragma once

#include <string>

#include "Size.hpp"
#include "Point.hpp"
#include "Color.hpp"
#include "Matrix4.hpp"


namespace gl {

class Shader {

    using ID = int;

    ID program = -1;

    int color;
    int mvp_matrix;
    int model_matrix;
    int light_position;
    int size;
	int selected;
	int resolution;
	int position;
	int rotation;
    int camera_position;
    int flip;

public:

    explicit Shader(const std::string& path);

    const std::string path;

    void use() const;

    ID get_program_id() const;

    void set_color(const gm::Color&) const;
    void set_mvp_matrix(const gm::Matrix4&) const;
    void set_model_matrix(const gm::Matrix4&) const;
    void set_light_position(const gm::Vector3&) const;
    void set_size(const gm::Size&) const;
	void set_selected(bool) const;
	void set_resolution(const gm::Size&) const;
	void set_position(const gm::Point&) const;
	void set_rotation(float) const;
    void set_camera_position(const gm::Point&) const;
    void set_flip(bool) const;
};

}
