//
//  ShaderCompiler.cpp
//  test_engine
//
//  Created by Vladas Zakrevskis on 8/17/17.
//  Copyright © 2017 VladasZ. All rights reserved.
//

#pragma once

#include <string>

struct ShaderCompiler {    
	static inline std::string includes_path;
    static unsigned compile(const std::string& path);
};
