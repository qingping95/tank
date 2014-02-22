// Copyright (©) Jamie Bayne, David Truby, David Watson 2013-2014.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#include "BitmapText.hpp"
#include "Image.hpp"

#include  <cmath>
#include  <iostream>
#include "../Utility/Pimpl_impl.hpp"

namespace tank
{

struct BitmapText::Impl
{
    Image font;
    Vectoru glyphDims;
    char asciiOffset;
    unsigned int rowWidth;
    Rectu clip;

    std::string text;
    Vectorf origin;
};


template class Pimpl<BitmapText::Impl>;

BitmapText::BitmapText(Image const& font, Vectoru glyphDimensions,
                       char asciiOffset, unsigned int rowWidth)
    : data{font, glyphDimensions, asciiOffset, rowWidth,
                    Rectu{0,0,data->glyphDims.x, data->glyphDims.y}} // clip
{
    data->font.setClip(data->clip);
}

void BitmapText::setText(std::string text)
{
    data->text = text;
}

std::string BitmapText::getText()
{
    return data->text;
}

void BitmapText::setScale(float scale)
{
    data->font.setScale(scale);
}

void BitmapText::setScale(Vectorf scale)
{
    data->font.setScale(scale);
}

Vectorf BitmapText::getScale() const
{
    return data->font.getScale();
}

void BitmapText::setOrigin(Vectorf origin)
{
    data->origin = origin;
}

Vectorf BitmapText::getOrigin() const
{
    return data->origin;
}

Vector<unsigned int> BitmapText::getTextureSize() const
{
    return data->font.getTextureSize();
}

void BitmapText::setGlyphSize(Vectorf size)
{
    data->font.setSize(size);
}
Vectorf BitmapText::getGlyphSize() const
{
    return data->font.getSize();
}

Vectorf BitmapText::getSize() const
{
    int nChars = data->text.size();

    auto size = getGlyphSize();
    size.x *= nChars;

    return size;
}

void BitmapText::draw(Vectorf parentPos, float parentRot, Camera const& cam)
{
    Vectorf pos = getPos();
    float rot = getRotation();
    if(isRelativeToParent())
    {
        pos += parentPos;
        rot += parentRot;
    }

    for (unsigned int stringIndex = 0; data->text[stringIndex] != '\0'; ++stringIndex)
    {
        unsigned int clipIndex = static_cast<unsigned int>(data->text[stringIndex]
                                                           - data->asciiOffset);
        data->clip.x = (clipIndex % data->rowWidth) * data->glyphDims.x;
        data->clip.y = (clipIndex / data->rowWidth) * data->glyphDims.y;

        const float rads = 3.14159265 * rot / 180.f;
        const float distance = stringIndex * data->glyphDims.x;
        Vectorf displacement;
        displacement.x = distance * std::cos(rads);
        displacement.y = distance * std::sin(rads);

        data->font.setClip(data->clip);
        data->font.setPos(displacement);

        data->font.draw(pos, rot, cam);
    }
}

}
