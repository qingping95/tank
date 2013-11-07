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

#include "Game.hpp"

#include <SFML/Window/Event.hpp>
#include "Keyboard.hpp"
#include "Window.hpp"

namespace tank {

Logger Game::log {"log.txt"};
unsigned int Game::fps {60};
bool Game::initialized_ {false};
bool Game::run_ {false};
bool Game::popWorld_ {false};
observing_ptr<World> Game::currentWorld_ {nullptr};
std::unique_ptr<Window> Game::window_ {nullptr};
std::stack<std::unique_ptr<World>> Game::worlds_;
//Timer Game::frameTimer_;

/* ---------------------------- *
 * Initialization
 * ---------------------------- */

//TODO Handle errors with exceptions
bool Game::initialize(Vector<unsigned int> const& wSize, int fps)
{
    if (not initialized_)
    {
        initialized_ = true;

        //Create window
		window_.reset(new Window(tank::Vectoru{wSize.x, wSize.y}));

        // TODO: Make this reflect actual FPS
        Game::fps = fps;
    }

    return initialized_;
}

/* ----------------------------------- *
 * Main Game Loop
 * ----------------------------------- */

void Game::run()
{
    if (run_) { return; }

    run_ = true;
    log << "Entering main loop" << std::endl;
    while (run_)
    {
        if (worlds_.empty())
        {
            log << "No game world" << std::endl;
            run_ = false;
            break;
        }

        currentWorld_ = worlds_.top();
        handleEvents();
        currentWorld_->update();
        draw();

        if (popWorld_)
        {
            worlds_.pop();
            popWorld_ = false;
        }
    }
}

void Game::handleEvents()
{
    sf::Event event;

    while (window_->pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::KeyPressed:
            Keyboard::setKeyPressed(event.key.code);
            break;
        case sf::Event::KeyReleased:
            if(event.key.code == sf::Keyboard::Key::F4 && event.key.alt)
            {
                run_ = false;
                break;
            }
            Keyboard::setKeyReleased(event.key.code);
            break;
        case sf::Event::GainedFocus:
            draw();
            break;
        case sf::Event::Closed:
            run_ = false;
            break;
        default:
            break;
        }
    }

    currentWorld_->eventHandler.propagate();
    Keyboard::reset();
}

/* ----------------------------------- *
 * World management
 * ----------------------------------- */

void Game::popWorld()
{
    popWorld_ = true;
}

/* --------------------------- *
 * Update and draw functions
 * --------------------------- */

void Game::update()
{
}

void Game::draw()
{
    //Draw current world
    currentWorld_->draw();

    //Update the screen
    window_->flipDisplay();
}

}
