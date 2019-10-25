//
//  Monitor.hpp
//  gl_wrapper
//
//  Created by Vladas Zakrevskis on 10/25/19.
//  Copyright © 2019 VladasZ. All rights reserved.
//

#pragma once

#include "Size.hpp"

namespace gl {

    class Monitor {

        std::string _name;

        unsigned _refresh_rate;

        gm::Size _scale;
        gm::Size _resolution;
        gm::Size _physical_size;

    public:

        Monitor(void*);

        std::string name() const;

        unsigned refresh_rate() const;

        gm::Size scale() const;
        gm::Size resolution() const;
        gm::Size physical_size() const;

        std::string to_string() const;

    };

}
