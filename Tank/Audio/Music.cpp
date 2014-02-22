// Copyright (©) Jamie Bayne, David Truby, David Watson 2013-2014.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#include "Music.hpp"
#include "../System/Game.hpp"
#include <SFML/Audio/Music.hpp>
#include "../Utility/Pimpl_impl.hpp"

namespace tank
{

struct Music::Impl {
    sf::Music music;
    bool loaded = false;
};

template class Pimpl<Music::Impl>;

Music::Music (std::string fileName)
{
    load(fileName);
}

bool Music::load (std::string fileName)
{
    if (data->loaded)
    {
        Game::log << "Music already loaded!" << std::endl;
        return data->loaded;
    }
    data->loaded = data->music.openFromFile(fileName);
    return data->loaded;
}

void Music::play()
{
    data->music.play();
}

void Music::pause()
{
    data->music.pause();
}

void Music::stop()
{
    data->music.stop();
}

}
