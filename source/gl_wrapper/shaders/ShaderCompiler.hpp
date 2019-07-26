//
//  ShaderCompiler.cpp
//  test_engine
//
//  Created by Vladas Zakrevskis on 8/17/17.
//  Copyright © 2017 VladasZ. All rights reserved.
//

#pragma once

#include <string>

struct ShaderCompiler final {    
    static unsigned int compile(const std::string& vertex_path, const std::string& fragment_path);
};
