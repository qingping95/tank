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

#ifndef TANK_TEXT_HPP
#define TANK_TEXT_HPP

#include <SFML/Graphics/Text.hpp>
#include "../System/Entity.hpp"
#include "../Utility/Timer.hpp"
#include "../Utility/Vector.hpp"
#include "Font.hpp"
#include "Color.hpp"

#include <string>

namespace tank
{

class Text : public Graphic
{
    struct Impl;
    std::unique_ptr<Impl> data;
public:
    Text() = default;
    Text(const Text&) = default;
    Text(Font& f, unsigned size = 30, std::string text = "");

    ~Text();

    void setFont(Font& f);

    void setFontSize(unsigned s);
    unsigned getFontSize() const;

    void setText(std::string s);
    std::string getText() const;

    virtual void setOrigin(Vectorf o);
    virtual Vectorf getOrigin() const;

    virtual Vectorf getSize() const;

    virtual void setColor(const Color& color);

    virtual void draw(Vectorf parentPos,
                      float parentRot,
                      Camera const& = Camera()) override;
};

}
#endif
