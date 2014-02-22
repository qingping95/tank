// Copyright (©) Jamie Bayne, David Truby, David Watson 2013-2014.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#ifndef TANK_TEXT_HPP
#define TANK_TEXT_HPP

#include "../Utility/Pimpl.hpp"
#include "../Graphics/Graphic.hpp"
#include "../Utility/Vector.hpp"
#include "Font.hpp"
#include "Color.hpp"

#include <string>

namespace tank
{

class Camera;

class Text : public Graphic
{
    struct Impl;
    Pimpl<Impl> data;
public:
    Text() = default;
    Text(const Text&) = default;
    Text(Font& f, unsigned size = 30, std::string text = "");

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
