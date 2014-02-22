// Copyright (©) Jamie Bayne, David Truby, David Watson 2013-2014.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#include "Text.hpp"
#include <SFML/Graphics/Text.hpp>
#include "../Utility/Pimpl_impl.hpp"
#include "../System/Game.hpp"

#include "../System/Game.hpp"

namespace tank
{

struct Text::Impl {
        sf::Text text;
};

template class Pimpl<Text::Impl>;

Text::Text(Font& f, unsigned size, std::string text)
    : data{sf::Text{text,f,size}}
{
}

void Text::setFont(Font& f)
{
    data->text.setFont(f);
}

void Text::setFontSize(unsigned s)
{
    data->text.setCharacterSize(s);
}
unsigned Text::getFontSize() const
{
    return data->text.getCharacterSize();
}

void Text::setText(std::string s)
{
    data->text.setString(s);
}

std::string Text::getText() const
{
    return data->text.getString();
}

void Text::setOrigin(Vectorf o)
{
    data->text.setOrigin(o.x,o.y);
}
Vectorf Text::getOrigin() const
{
    return {data->text.getOrigin().x, data->text.getOrigin().y};
}

Vectorf Text::getSize() const
{
    return {data->text.getLocalBounds().width, data->text.getLocalBounds().height};
}

void Text::setColor(const Color& color) {
    data->text.setColor(color);
}

void Text::draw(Vectorf parentPos, float parentRot, Camera const& cam)
{
    Graphic::transform(this, parentPos, parentRot, cam, data->text);
    Game::window()->SFMLWindow().draw(data->text);
}
}
