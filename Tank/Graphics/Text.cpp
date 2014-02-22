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
