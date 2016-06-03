#ifndef game_h
#define game_h

#include <iostream>
#include <string>
#include <sstream>

#include <SDL2/SDL.h>
#include <SDL2_ttf/SDL_ttf.h>

#include "dot.h"
#include "paddle.h"
#include "texture.h"

class Game {
public:
    Game(const char* title, int xpos, int ypos, int screenWidth, int screenHight, int flags):
    mRunning(true), mWindow(NULL), mRenderer(NULL), mFont(NULL), mTitle(title), mXpos(xpos), mYpos(ypos),
    mScreenWidth(screenWidth), mScreenHight(screenHight), mFlags(flags),
    paddleOne(10, screenHight / 2), paddleTwo(screenWidth - 20, screenHight / 2), dot(screenWidth / 2, screenHight / 2) { }

    ~Game() {}

    bool loadMedia();       // load media files

    bool init();            // Init SDL
    void render();          // Render objects
    void update();          // Updates the screen
    void handleEvents();    // Handles user input
    void clean();           // Clean SDL at exit

    bool running() { return mRunning; }
    SDL_Renderer* gRenderer() const { return mRenderer; }

private:
    bool mRunning;

    SDL_Window* mWindow;
    SDL_Renderer* mRenderer;
    TTF_Font* mFont;

    std::stringstream scoreText;        // in memory text stream

    const char* mTitle;                 // Window title
    int mXpos, mYpos;                   // The X and Y offsets of the window
    int mScreenWidth, mScreenHight;     // The windows width and height
    int mFlags;                         // Window Flag

    Dot dot;
    Paddle paddleOne;
    Paddle paddleTwo;
    Texture mText;

};

#endif
