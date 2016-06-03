#include "dot.h"

// checks collision
bool Dot::collisionChecker(std::vector<SDL_Rect>& a, std::vector<SDL_Rect>& b) {
    // The rectangles sides
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    // Go through A boxes
    for (int Abox = 0; Abox < a.size(); Abox++) {
        // Calculate ract A sides
        leftA = a[Abox].x;
        rightA = a[Abox].x + a[Abox].w;
        topA = a[Abox].y;
        bottomA = a[Abox].y + a[Abox].h;

        // Go through A boxes
        for (int Bbox = 0; Bbox < b.size(); Bbox++) {
            // Calculate ract B sides
            leftB = b[Bbox].x;
            rightB = b[Bbox].x + b[Bbox].w;
            topB = b[Bbox].y;
            bottomB = b[Bbox].y + b[Bbox].h;

            // Check if no sides from A are outside of B
            if (((bottomA <= topB) || (topA >= bottomB) || (rightA <= leftB) || (leftA >= rightB)) == false) {
                if (Bbox == 0) {
                    mVelY = -8;
                }
                if (Bbox == 1) {
                    mVelY = -4;
                }
                if (Bbox == 2) {
                    mVelY = -2;
                }
                if (Bbox == 3) {
                    mVelY = 2;
                }
                if (Bbox == 4) {
                    mVelY = 4;
                }
                if (Bbox == 5) {
                    mVelY = 8;
                }

                // Collision is detected
                return true;
            }
        }
    }

    // No collision detected
    return false;
}

Dot::Dot(int posx, int posy):
mPosX(posx), mPosY(posy), mVelX(0), mVelY(0), hit(false), playerOneScore(0), playerTwoScore(0) {
    // Create the necessary SDL_Rects
    mColliders.resize(1);

    // Initialize the collision boxes' width and height
    mColliders[0].w = 20;
    mColliders[0].h = 20;

    // Initialize colliders relative to position
    shiftColliders();
}

void Dot::move(int width, int height, std::vector<SDL_Rect>& otherCollidersOne, std::vector<SDL_Rect>& otherCollidersTwo) {
    if (hit == false) {
        mPosX += DOT_VEL;
        shiftColliders();
    } else {
        mPosX -= DOT_VEL;
        shiftColliders();
    }

    // Check if the dot moved to far left or right
    if (collisionChecker(mColliders, otherCollidersOne) || collisionChecker(mColliders, otherCollidersTwo)) {
        //Move back
        if (hit == false) {
            mPosX -= DOT_VEL;
            shiftColliders();
            hit = true;
        } else {
            mPosX += DOT_VEL;
            shiftColliders();
            hit = false;
        }
    }

    // Up or down
    mPosY += mVelY;
    shiftColliders();

    // Check if the dot moved to far up or down
    if ((mPosY < 0) || (mPosY + DOT_HEIGHT > height)) {
        mPosY -= mVelY;
        shiftColliders();

        // Dot bounce off the wall at the same ange as it came in
        if (mVelY == -8) {
            mVelY = 8;
        } else if (mVelY == -4) {
            mVelY = 4;
        } else if (mVelY == -2) {
            mVelY = 2;
        } else if (mVelY == 2) {
            mVelY = -2;
        } else if (mVelY == 4) {
            mVelY = -4;
        } else if (mVelY == 8) {
            mVelY = -8;
        }
    }

    // Restart the dot in the middle of the window if dot leaves the window
    if (mPosX >= width) {
        mPosX = width / 2;
        mPosY = height / 2;

        playerOneScore++;
    }
    if (mPosX <= 0) {
        mPosX = width / 2;
        mPosY = height / 2;

        playerTwoScore++;
    }
}

void Dot::render(SDL_Renderer* renderer) {
    // Draw the dot
    SDL_Rect bottomLine = {mPosX, mPosY, DOT_WIDTH, DOT_HEIGHT};
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderFillRect(renderer, &bottomLine);
}

std::vector<SDL_Rect>& Dot::getCollider() {
    return mColliders;
}

void Dot::shiftColliders() {
    // Row offset
    int r = 0;

    // Moving through the dots collision boxes
    for (int set = 0; set < mColliders.size(); ++set) {
        // Center the collision box
        mColliders[set].x = mPosX + (DOT_WIDTH - mColliders[set].w) / 2;

        // Set the collision box at its row offset
        mColliders[set].y = mPosY + r;

        // Move the row offset down the height of the collision box
        r += mColliders[set].h;
    }
}
