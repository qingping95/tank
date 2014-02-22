// Copyright (©) Jamie Bayne, David Truby, David Watson 2013-2014.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#include "CircleShape.hpp"
#include "../System/Game.hpp"
#include "../Utility/Pimpl_impl.hpp"

namespace tank {

struct CircleShape::Impl {
    sf::CircleShape circleShape;
};

template class Pimpl<CircleShape::Impl>;

CircleShape::CircleShape(float radius):Shape(), data{sf::CircleShape{radius}}
{
}

void CircleShape::setFillColor(Color c)
{
    data->circleShape.setFillColor(c);
}
void CircleShape::setOutlineColor(Color c)
{
    data->circleShape.setOutlineColor(c);
}
void CircleShape::setOutlineThickness(float thickness)
{
    data->circleShape.setOutlineThickness(thickness);
}
Color const& CircleShape::getFillColor() const
{
    return data->circleShape.getFillColor();
}
Color const& CircleShape::getOutlineColor() const
{
    return data->circleShape.getOutlineColor();
}
float CircleShape::getOutlineThickness() const
{
    return data->circleShape.getOutlineThickness();
}

Vectorf CircleShape::getSize() const
{
    auto rect = data->circleShape.getGlobalBounds();
    return {rect.width, rect.height};
}

void CircleShape::draw(tank::Vectorf parentPos,
                       float parentRot,
                       tank::Camera const& cam)
{
    Graphic::transform(this, parentPos, parentRot, cam, data->circleShape);
    Game::window()->SFMLWindow().draw(data->circleShape);
}

void CircleShape::setRadius(float radius) { data->circleShape.setRadius(radius); }
float CircleShape::getRadius() const { return data->circleShape.getRadius(); }

void CircleShape::setOrigin(Vectorf o)
{
    data->circleShape.setOrigin({o.x, o.y});
}

Vectorf CircleShape::getOrigin() const
{
    auto origin = data->circleShape.getOrigin();
    return { origin.x, origin.y };
}


}
