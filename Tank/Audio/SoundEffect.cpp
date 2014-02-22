// Copyright (©) Jamie Bayne, David Truby, David Watson 2013-2014.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include "SoundEffect.hpp"
#include "../System/Game.hpp"
#include "../Utility/Pimpl_impl.hpp"

namespace tank
{

struct SoundEffect::Impl {
    sf::SoundBuffer buffer;
    sf::Sound sound;
    bool loaded = false;
};

template class Pimpl<SoundEffect::Impl>;

SoundEffect::SoundEffect(std::string fileName)
{
    load(fileName);
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
