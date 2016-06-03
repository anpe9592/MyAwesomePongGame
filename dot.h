#ifndef dot_h
#define dot_h

#include <iostream>
#include <vector>

#include <SDL2/SDL.h>

class Dot {
public:
    Dot(int posx, int posy);

    void move(int width, int height, std::vector<SDL_Rect>& otherCollidersOne, std::vector<SDL_Rect>& otherCollidersTwo);       // Moves the dot
    void render(SDL_Renderer* renderer);    // Draw the dot on to the screen

    static const int DOT_WIDTH  = 20;       // Dot's width
    static const int DOT_HEIGHT = 20;       // Dot's height
    static const int DOT_VEL    = 5;        // Max velocity of the dot

    std::vector<SDL_Rect>& getCollider();   // Gets the collision boxes

    bool collisionChecker(std::vector<SDL_Rect>& a, std::vector<SDL_Rect>& b);  // checks collision

    int getPlayerOneScore() const { return playerOneScore; }
    int getPlayerTwoScore() const { return playerTwoScore; }

private:
    int mPosX, mPosY;                       // The X and Y offsets of the dot
    int mVelX, mVelY;                       // The velocity of the dot

    std::vector<SDL_Rect> mColliders;       // Paddle's collision boxes
    void shiftColliders();                  // Moves the collision boxes relative to the paddle's offset

    bool hit;                               // Check if Dot hit Paddle

    int playerOneScore, playerTwoScore;     // The players score
};

#endif
