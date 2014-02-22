// Copyright (©) Jamie Bayne, David Truby, David Watson 2013-2014.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#ifndef TANK_BITMAPTEXT_HPP
#define TANK_BITMAPTEXT_HPP

#include <limits>
#include <string>
#include <memory>
#include "Graphic.hpp"
#include "../Utility/Pimpl.hpp"

namespace tank
{

class Image;

class BitmapText final : public Graphic
{
    struct Impl;
    Pimpl<Impl> data;

public:
    BitmapText(Image const& font, Vectoru glyphDimensions,
               char asciiOffset = 32, unsigned rowWidth = std::numeric_limits<unsigned>::max());

    void setText(std::string text);

    std::string getText();

    virtual void setScale(float scale) override;
    virtual void setScale(Vectorf scale) override;
    virtual Vectorf getScale() const override;

    /*!
     * \brief Set the size of each rendered glyph
     *
     * \param size The size for each glyph
     */
    virtual void setGlyphSize(Vectorf size);
    /*!
     * \brief Return the rendered glyph size
     *
     * \return The glyph size
     */
    virtual Vectorf getGlyphSize() const;

    /*!
     * \brief Return the size of the current string
     */
    virtual Vectorf getSize() const override;

    virtual void setOrigin(Vectorf origin) override;
    virtual Vectorf getOrigin() const override;

    virtual Vector<unsigned int> getTextureSize() const;

    virtual void draw(Vectorf parentPos = {},
                      float parentRot = 0,
                      Camera const& = Camera());
};

}

#endif /* TANK_BITMAPTEXT_HPP */
