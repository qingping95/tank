// Copyright (©) Jamie Bayne, David Truby, David Watson 2013-2014.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#ifndef TANK_CIRCLESHAPE_HPP
#define TANK_CIRCLESHAPE_HPP

#include <SFML/Graphics/CircleShape.hpp>
#include "../Utility/Pimpl.hpp"
#include "Shape.hpp"

namespace tank {

class CircleShape : public Shape
{
    struct Impl;
    Pimpl<Impl> data;

public:
    CircleShape(float radius = 0);

    void setRadius(float radius);
    float getRadius() const;

    virtual void setFillColor(Color colour) override;
    virtual void setOutlineColor(Color colour) override;
    virtual void setOutlineThickness(float) override;
    virtual Color const& getFillColor() const override;
    virtual Color const& getOutlineColor() const override;
    virtual float getOutlineThickness() const override;

    virtual Vectorf getSize() const override;

    virtual void setOrigin(Vectorf o) override;

    virtual Vectorf getOrigin() const override;

    virtual void draw(Vectorf parentPos = {},
                      float parentRot = 0,
                      Camera const& = Camera()) override;
};

}

#endif /* TANK_CICLESHAPE_HPP */
