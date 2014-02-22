// Copyright (©) Jamie Bayne, David Truby, David Watson 2013-2014.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
#ifndef TANK_MUSIC_HPP
#define TANK_MUSIC_HPP

#include <string>
#include "../Utility/Pimpl.hpp"

namespace tank
{

class Music
{
    struct Impl;
    Pimpl<Impl> data;

public:
    Music(std::string fileName);

    bool load(std::string fileName);

    void play();
    void pause();
    void stop();
};

}

#endif //TANK_MUSIC_HPP
