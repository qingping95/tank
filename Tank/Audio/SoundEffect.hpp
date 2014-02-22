// Copyright (©) Jamie Bayne, David Truby, David Watson 2013-2014.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#ifndef TANK_SOUNDEFFECT_HPP
#define TANK_SOUNDEFFECT_HPP

#include <string>
#include "../Utility/Pimpl.hpp"

namespace tank
{

class SoundEffect
{
    struct Impl;
    Pimpl<Impl> data;

public:
    enum Status {
        Stopped, Paused, Playing
    };

    SoundEffect(std::string fileName);

    bool load(std::string fileName);

    void play();

    Status getStatus();

};

}

#endif //TANK_SOUNDEFFECT_HPP
