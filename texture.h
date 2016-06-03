#ifndef texture_h
#define texture_h

#include <iostream>
#include <string>

#include <SDL2/SDL.h>
#include <SDL2_ttf/SDL_ttf.h>

class Texture {
public:
    // Initializes variables
    Texture();

    // Deallocates memory
    ~Texture();

    // Creates image from font string
    bool loadFromRenderedText(SDL_Renderer* renderer, TTF_Font *font, std::string textureText, SDL_Color textColor);

    // Deallocates texture
    void free();

    // Renders texture at given point
    void render(SDL_Renderer* renderer, int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

    // Gets image dimensions
    int getWidth()  const { return mWidth; }
    int getHeight() const { return mHeight; }

private:
    // The actual hardware texture
    SDL_Texture* mTexture;

    // Image dimensions
    int mWidth;
    int mHeight;
};


#endif
