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

        unsigned _ppi;
        unsigned _scale;
        unsigned _refresh_rate;
        
        gm::Size _resolution;
        gm::Size _physical_size;

        std::string _name;
        
    public:

        Monitor(unsigned scale,
                unsigned refresh_rate,
                const gm::Size& resolution,
                const gm::Size& physical_size,
                const std::string& name);

#ifdef IOS_BUILD
        Monitor();
#endif
        
#ifdef DESKTOP_BUILD
        Monitor(void* glfw_info);
#endif

        unsigned ppi() const;
        unsigned scale() const;
        unsigned refresh_rate() const;

        gm::Size resolution() const;
        gm::Size physical_size() const;

        std::string name() const;

        float diagonal() const;


        std::string to_string() const;

    };

}
