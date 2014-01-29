/* This file is part of Tank.
 *
 * Tank is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Tank is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License and
 * the GNU Lesser General Public Licence along with Tank. If not, see
 * <http://www.gnu.org/licenses/>.
 *
 * Copyright 2013 (©) Jamie Bayne, David Truby, David Watson.
 */

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
