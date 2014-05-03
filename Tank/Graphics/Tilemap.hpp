// Copyright (©) Jamie Bayne, David Truby, David Watson 2013-2014.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#ifndef TANK_TILEMAP_HPP
#define TANK_TILEMAP_HPP

#include <string>
#include <functional>
#include "Graphic.hpp"
#include "Image.hpp"
#include "../Utility/Vector.hpp"
#include "../Utility/Rect.hpp"
#include "../Utility/Grid.hpp"

namespace tank
{

/*!
 * \brief Represents an image with multiple frames and stores animations for
 * that image.
 */
class Tilemap final : public Image
{
    Vectoru frameDimensions_ {0, 0};
    Rectu clipRect_ {0,0,0,0};
    Grid<unsigned> tiles_;

public:
    Tilemap() = default;
    /*!
     * \brief Construct an Animation with a Texture.
     * \param file the file to load the texture from.
     * \param gridDims size of the grid.
     * \param frameDims size of each image in the Texture.
     */
    Tilemap(std::string file, Vector<unsigned> gridDims,
            Vector<unsigned int> frameDims);

    /*!
     * \brief Draw the animation.
     *
     * Trying to draw an animation without a texture will crash the game!
     *
     * \param pos Position at which to draw the texture.
     */
    virtual void draw(Vectorf parentPos = {},
                      float parentRot = 0,
                      Vectorf parentOri = {},
                      Camera const& = Camera()) override;
    /*!
     * \brief Set the dimensions of the image in the texture.
     *
     * \param frameDims the dimensions of each image in the texture.
     */
    void setFrameDimensions(Vectoru frameDims)
    {
        frameDimensions_ = frameDims;
    }

    Vectoru getFrameDimensions() const { return frameDimensions_; }

    /*!
     * \brief This sets the clip rectangle by tiling the region and selecting
     * the tile designated by index. It has an option of setting an additional
     * clip within that area.
     *
     * \param dimensions The dimensions of the tile.
     * \param index The index of the tile to select.
     * \param clip An optional parameter for additional clipping within the
     * designated area.
     */
    virtual void setClip(Vectoru dimensions, unsigned int index, Rectu clip = {0,0,0,0}) override;

    /*!
     * \brief Sets the clip rectangle of the image
     *
     * \param clip The rectangle to clip the image to
     */
    virtual void setClip(Rectu clip) override
    {
        clipRect_ = clip;
    }
    virtual Rectu getClip() const
    {
        return clipRect_;
    }


};

} // tank

#endif /* TANK_TILEMAP_HPP */
