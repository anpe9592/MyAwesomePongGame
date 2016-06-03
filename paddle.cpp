#include "paddle.h"

Paddle::Paddle(int posx, int posy):
mPosX(posx), mPosY(posy), mVelX(0), mVelY(0) {
    // Create the necessary SDL_Rects
    mColliders.resize(6);

    // Initialize the collision boxes' width and height
    mColliders[0].w = 10;
    mColliders[0].h = 15;

    mColliders[1].w = 10;
    mColliders[1].h = 15;

    mColliders[2].w = 10;
    mColliders[2].h = 15;

    mColliders[3].w = 10;
    mColliders[3].h = 15;

    mColliders[4].w = 10;
    mColliders[4].h = 15;

    mColliders[5].w = 10;
    mColliders[5].h = 15;

    // Initialize colliders relative to position
    shiftColliders();
}

void Paddle::handleEvent(SDL_Event& event) {
    // Key pressed down
    if (event.type == SDL_KEYDOWN && event.key.repeat == 0) {
        switch(event.key.keysym.sym) {
            case SDLK_UP:    mVelY -= PADDLE_VEL; break;
            case SDLK_DOWN:  mVelY += PADDLE_VEL; break;
        }
    }
    // Key is released
    else if (event.type == SDL_KEYUP && event.key.repeat == 0) {
        switch (event.key.keysym.sym) {
            case SDLK_UP:    mVelY += PADDLE_VEL; break;
            case SDLK_DOWN:  mVelY -= PADDLE_VEL; break;
        }
    }
}

void Paddle::move(int width, int height, std::vector<SDL_Rect>& otherColliders) {
    // Up or down
    mPosY += mVelY;
    shiftColliders();

    // Check if the Paddle moved to far up or down
    if ((mPosY < 0) || (mPosY + PADDLE_HEIGHT > height)) {
        mPosY -= mVelY;     // Move back
        shiftColliders();
    }
}

void Paddle::render(SDL_Renderer* renderer) {
    // Draw the Paddle
    SDL_Rect bottomLine = {mPosX, mPosY, PADDLE_WIDTH, PADDLE_HEIGHT};
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderFillRect(renderer, &bottomLine);
}

void Paddle::shiftColliders() {
    // Row offset
    int r = 0;

    // Moving through the paddles collision boxes
    for (int set = 0; set < mColliders.size(); ++set) {
        // Center the collision box
        mColliders[set].x = mPosX + (PADDLE_WIDTH - mColliders[set].w) / 2;

        // Set the collision box at its row offset
        mColliders[set].y = mPosY + r;

        // Move the row offset down the height of the collision box
        r += mColliders[set].h;
    }
}

std::vector<SDL_Rect>& Paddle::getColliders() {
    return mColliders;
}
