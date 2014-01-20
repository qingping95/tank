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
