#pragma once
#ifndef GAME_H
#define GAME_H

#include <stack>
#include <memory>
#include "../Graphics/IRender.hpp"
#include "../System/IWindow.hpp"
#include "../Utility/Timer.hpp"
#include "State.hpp"
#include <SDL/SDL_events.h>
#include "../Utility/Logger.hpp"

class Game
{
public:
    static Game* Instance();
    ~Game();

    bool initialize();
    void run();

    bool addState(State*);
    void popState();

	/**
	 * @brief Log a message in the game logfile.
	 *
	 * @param logStr The first part of the message to be logged.
	 * @param args The rest of the message.
	 */
    Logger& log() {
        return log_;
    }

    State& state();
private:
    bool initialized_;
    bool run_;

    //Hacky hacky hacky
    bool popState_;

    Logger log_ {"log.txt"};
    IWindow* window_;
    IRender* render_;

    std::stack<std::unique_ptr<State>> states_;
    Timer frameTimer_;

    void handleEvents();
    void update();
    void draw();

    static Game* instance_;
    Game();
};

/*
template<typename... Args>
void Game::log(const std::string& logStr, Args&&... args)
{
<<<<<<< Updated upstream
    log_.log(logStr, std::forward<Args>(args)...);
=======
	log_.log(logStr, std::forward<Args>(args)...);
>>>>>>> Stashed changes
}
*/
#endif
