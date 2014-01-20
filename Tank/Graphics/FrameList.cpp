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

#include "FrameList.hpp"

#include <algorithm>
#include <boost/range/algorithm.hpp>

#include "Image.hpp"
#include "../Utility/Timer.hpp"
#include "../Utility/Pimpl_impl.hpp"

namespace tank
{

struct FrameList::Impl {
    Impl() = default;
    Impl(const Image& image, Vector<unsigned> frameDims) :
        image(image), frameDimensions(frameDims) {}
    Image image;
    Vectoru frameDimensions {0, 0};
    FrameList::Animation* currentAnimation {nullptr};
    unsigned int currentFrame {0};
    Timer animTimer;
    bool loop {false};
    std::function<void()> callback = []{};
    std::vector<Animation>  animations;
};

template class Pimpl<FrameList::Impl>;

FrameList::FrameList(const Image& image, Vector<unsigned int> frameDims)
    : data{image, frameDims}
{
    data->image.setClip({0,0,frameDims.x, frameDims.y});
    //image_.setSize(frameDims);
}

bool FrameList::playing() const
{
    return data->currentAnimation;
}

std::string FrameList::currentAnimation()
{
    if (not playing())
    {
        return "";
    }
    return data->currentAnimation->name;
}

void FrameList::setPos(Vectorf pos)
{
    data->image.setPos(pos);
}
Vectorf FrameList::getPos() const
{
    return data->image.getPos();
}
bool FrameList::isRelativeToParent() const
{
    return data->image.isRelativeToParent();
}

void FrameList::setRotation(float angle)
{
    data->image.setRotation(angle);
}
float FrameList::getRotation() const
{
    return data->image.getRotation();
}

void FrameList::setClip(Rectu clip)
{
    data->image.setClip(clip);
}

Rectu FrameList::getClip() const
{
    return data->image.getClip();
}

void FrameList::setOrigin(Vectorf origin)
{
    data->image.setOrigin(origin);
}

Vectorf FrameList::getOrigin() const
{
    return data->image.getOrigin();
}

void FrameList::setSize(Vectorf size)
{
    data->image.setSize(size);
}
Vectorf FrameList::getSize() const
{
    return data->image.getSize();
}


Vectoru FrameList::getFrameDimensions() const
{
    return data->frameDimensions;
}

void FrameList::setScale(float scale)
{
    data->image.setScale(scale);
}
void FrameList::setScale(Vectorf scale)
{
    data->image.setScale(scale);
}
Vectorf FrameList::getScale() const
{
    return data->image.getScale();
}
void FrameList::drawRelativeToParent(bool relative)
{
    data->image.drawRelativeToParent(relative);
}
Vectoru FrameList::getTextureSize() const
{
    return data->image.getTextureSize();
}

void FrameList::add(std::string name,
                    std::vector<unsigned int> const& frames,
                    unsigned int time)
{
    // TODO: validate arguments
    // Create new Animation
    data->animations.push_back({name, frames, time});
}

void FrameList::remove(std::string name)
{
    // Find the animation by name
    auto iter = boost::find_if(data->animations, [&name](Animation& anim)
    {
        return anim.name != (name);
    });

    //Remove the animation from the animations list
    if (iter != data->animations.end())
    {
        data->animations.erase(iter);
    }
}

void FrameList::select(std::string name, bool loop,
                       std::function<void()> callback)
{
    //Check that the requested animation is not already playing
    if (not data->currentAnimation || data->currentAnimation->name != name)
    {
        //search for the name requested
        for (auto& anim : data->animations)
        {
            if (anim.name == name)
            {
                data->currentAnimation = &anim;
                data->currentFrame = 0;
                data->loop = loop;
                data->callback = callback;
            }
        }
    }
}

void FrameList::refresh()
{
    //Only play if there is a selected animation
    if (data->currentAnimation)
    {
        //Check if we need to change animation frame
        bool playNextFrame = data->animTimer.getTicks() > data->currentAnimation->time;


        if (playNextFrame)
        {
            ++data->currentFrame;

            data->animTimer.start(); //Reset timer

            //Check if we've finished the animation
            unsigned const int lastFrame = data->currentAnimation->frameList.size();

            if (data->currentFrame >= lastFrame)
            {
                data->currentFrame = 0;

                data->callback();

                //If the animation doesn't loop, stop it
                if (not data->loop)
                {
                    //Reset all properties (callback, timer, currentFrame, etc)
                    stop();
                }
            }
        }
    }

    //Animation may have ended now. If not, need to set clipping mask for image
    if (data->currentAnimation)
    {
        //Start at first frame
        unsigned int frame = data->currentAnimation->frameList[data->currentFrame];

        //Set clipping rectangle according to current frame
        data->image.setClip(data->frameDimensions, frame);
    }
}

void FrameList::start()
{
    if (not data->animTimer.isStarted())
    {
        data->animTimer.start();
    }
}

void FrameList::pause()
{
    data->animTimer.pause();
}

void FrameList::resume()
{
    if (data->animTimer.isPaused() and data->currentAnimation != nullptr)
    {
        data->animTimer.resume();
    }
}

void FrameList::stop()
{
    //Change appearance to first frame
    data->currentFrame = 0;
    refresh();

    //Unset member variables
    data->animTimer.stop();
    data->callback = []{};
    data->currentAnimation = nullptr;
}

void FrameList::draw(Vectorf parentPos, float parentRot, Camera const& cam)
{
    refresh();
    data->image.draw(parentPos, parentRot, cam);
}

void FrameList::setImage(Image const& image, Vector<unsigned int> frameDims)
{
    data->frameDimensions = frameDims;
    data->image = image;
}

void addWalkingFrameList(FrameList& anim, unsigned int time)
{
    unsigned int xFrames = anim.getTextureSize().x / anim.getFrameDimensions().x;

    std::vector<unsigned int> up;
    std::vector<unsigned int> right;
    std::vector<unsigned int> down;
    std::vector<unsigned int> left;

    for (unsigned int i = 0; i < xFrames; ++i)
    {
        up.push_back(i);
        right.push_back(i + xFrames);
        down.push_back(i + xFrames * 2);
        left.push_back(i + xFrames * 3);
    }
    anim.add("walk_up", up, time);
    anim.add("walk_right", right, time);
    anim.add("walk_down", down, time);
    anim.add("walk_left", left, time);
}

}
