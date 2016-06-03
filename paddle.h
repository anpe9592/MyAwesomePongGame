#ifndef paddle_h
#define paddle_h

#include <iostream>
#include <vector>


#include <SDL2/SDL.h>

class Paddle {
public:
    Paddle(int posx, int posy);

    void handleEvent(SDL_Event& event);         // Takes key input and adept the Paddle's velocity
    void move(int width, int height, std::vector<SDL_Rect>& otherColliders);    // Moves the Paddle
    void render(SDL_Renderer* renderer);        // Draw the Paddle on to the screen

    static const int PADDLE_WIDTH  = 10;        // Paddle's width
    static const int PADDLE_HEIGHT = 90;        // Paddle's height
    static const int PADDLE_VEL    = 10;        // Max velocity of the Paddle

    std::vector<SDL_Rect>& getColliders();      // Gets the collision boxes

private:
    int mPosX, mPosY;                           // The X and Y offsets of the Paddle
    int mVelX, mVelY;                           // The velocity of the Paddle

    std::vector<SDL_Rect> mColliders;           // Paddle's collision boxes
    void shiftColliders();                      // Moves the collision boxes relative to the paddle's offset

};

#endif
