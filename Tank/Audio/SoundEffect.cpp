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

#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include "SoundEffect.hpp"
#include "../System/Game.hpp"

namespace tank
{

struct SoundEffect::Impl {
    sf::SoundBuffer buffer;
    sf::Sound sound;
    bool loaded = false;
};

SoundEffect::SoundEffect(std::string fileName) : data{new Impl}
{
    load(fileName);
}

SoundEffect::~SoundEffect() = default;

SoundEffect::SoundEffect(const SoundEffect& other) : data{new Impl(*other.data)}
{
}

SoundEffect& SoundEffect::operator=(const SoundEffect& other)
{
    // Copy and swap
    SoundEffect copy {other};
    std::swap(*this, copy);
    return *this;
}

bool SoundEffect::load(std::string fileName)
{
    if (data->loaded)
    {
        Game::log << "SoundEffect already loaded!" << std::endl;
        return data->loaded;
    }
    data->loaded = data->buffer.loadFromFile(fileName);
    data->sound.setBuffer(data->buffer);
    return data->loaded;
}

void SoundEffect::play()
{
    data->sound.play();
}

SoundEffect::Status SoundEffect::getStatus()
{
    return static_cast<SoundEffect::Status>(data->sound.getStatus());
}

}
