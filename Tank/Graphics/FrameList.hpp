// Copyright (©) Jamie Bayne, David Truby, David Watson 2013-2014.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#ifndef TANK_FRAMELIST_HPP
#define TANK_FRAMELIST_HPP

#include <string>
#include <vector>
#include <functional>
#include <memory>
#include <chrono>
#include "Graphic.hpp"
#include "../Utility/Vector.hpp"
#include "../Utility/Rect.hpp"
#include "../Utility/Pimpl.hpp"

namespace tank
{

class Image;
class Timer;

/*!
 * \brief Represents an image with multiple frames and stores animations for
 * that image.
 */
class FrameList final : public Graphic
{
    struct Animation
    {
        std::string name;
        std::vector<unsigned int> frameList;
        std::chrono::milliseconds time;
    };

    struct Impl;
    Pimpl<Impl> data;

public:
    FrameList() = default;
    /*!
     * \brief Construct an Animation with a Texture.
     * \param i Image to give the animation.
     * \param frameDims size of each image in the Texture.
     */
    FrameList(const Image& i, Vector<unsigned int> frameDimensions);

    /*!
     * \brief Add an animation
     *
     * Create a named list of frames to play in sequence, to be displayed  at a
     * fixed rate
     *
     * \param name String to identify the animation with later.
     * \param frames std::initializer_list of frames.
     * \param frameTime Time between each frame in milliseconds (ms)
     */
    void add(std::string name, const std::vector<unsigned int>& frames,
             std::chrono::milliseconds frameTime);

    void remove(std::string name);

    void select(std::string name, bool loop = true,
                std::function<void()> callback = []{});

    /*!
     * \brief Update the animation to the current frame. Called by draw
     */
    void refresh();

    /*!
     * \brief Draw the animation.
     *
     * Trying to draw an animation without a texture will crash the game!
     *
     * \param pos Position at which to draw the texture.
     */
    void draw(Vectorf parentPos = {},
              float parentRot = 0, 
              Camera const& = Camera()) override;

    /*!
     * \brief Start the animation
     */
    void start();

    /*!
     * \brief Pause the animation.
     */
    void pause();

    /*!
     * \brief Resume the animation.
     */
    void resume();

    /*!
     * \brief Stop the animation.
     * Sets the state of the animation to the first frame.
     */
    void stop();

    /*!
     * \return If the animation is playing.
     */
    bool playing() const;
    std::string currentAnimation();

    /*!
     * \brief Set the texture of the FrameList.
     * \param texture the Texture to set.
     * \param frameDims the dimensions of each image in the texture.
     */
    void setImage(Image const&, Vectoru frameDims);

    virtual void setPos(Vectorf pos);
    virtual Vectorf getPos() const;
    virtual bool isRelativeToParent() const;

    virtual void setRotation(float angle);
    virtual float getRotation() const;

    void setClip(Rectu clip);
    Rectu getClip() const;

    void setOrigin(Vectorf origin) override;
    Vectorf getOrigin() const override;

    void setSize(Vectorf size);
    Vectorf getSize() const override;


    Vectoru getFrameDimensions() const;
    virtual void setScale(float scale) override;
    virtual void setScale(Vectorf scale) override;
    virtual Vectorf getScale() const override;
    virtual void drawRelativeToParent(bool relative);
    virtual Vectoru getTextureSize() const;
};

// TODO: Use enum to specify image format
/*!
 * \brief Generate a walking animations for Animation
 *
 * Generates four animations: walk_up, walk_right, walk_down, walk_left.
 * Currently, they are generated from image rows going down in that order.
 */
void addWalkingAnimation(FrameList& frames, std::chrono::milliseconds time);

} // tank

#endif /* TANK_FRAMELIST_HPP */
