#include "game.h"

// Load media files
bool Game::loadMedia() {
    // Open the font
    mFont = TTF_OpenFont("PxPlus_IBM_VGA8.ttf", 28);
    if (mFont == NULL) {
        std::cout << "Failed to load the font PxPlus_IBM_VGA8! SDL_ttf Error: " << TTF_GetError() << std::endl;
        return false;
    }
    
    return true;
}

bool Game::init() {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) == 0) {
        // Set texture filtering to linear
        if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
            std::cout << "Warning: Linear texture filtering is disabled!" << std::endl;
        }
        
        // Creating the window
        mWindow = SDL_CreateWindow(mTitle, mXpos, mYpos, mScreenWidth, mScreenHight, mFlags);
        if (mWindow != NULL) {
            // Vsynced renderer is created for the window
            mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            if (mRenderer != NULL) {
                // Initialize renderer color
                SDL_SetRenderDrawColor(mRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
                
                // Initialize SDL_ttf
                if( TTF_Init() == -1 ) {
                    std::cout << "Unable to initialize SDL_ttf! SDL_ttf Error: " << TTF_GetError() << std::endl;
                    return false;
                }
            } else {
                std::cout << "Unable to create Renderer! SDL Error: " << SDL_GetError() << std::endl;
                return false;
            }
        } else {
            std::cout << "Unable to create Window! SDL Error: " << SDL_GetError() << std::endl;
            return false;
        }
    } else {
        std::cout << "Unable to initialize SDL! SDL Error: " << SDL_GetError() << std::endl;
        return false;
    }
    
    return true;
}

void Game::render() {
    // Render objects
    mText.render(mRenderer, (mScreenWidth - mText.getWidth() ) / 2, 12);
    dot.render(mRenderer);
    paddleOne.render(mRenderer);
    paddleTwo.render(mRenderer);
    
    // Update screen
    SDL_RenderPresent(mRenderer);
}

void Game::update() {
    // Set text to be rendered
    scoreText.str("");
    scoreText << dot.getPlayerOneScore() << " - " << dot.getPlayerTwoScore();
    
    // Render text
    SDL_Color textColor = { 0xFF, 0xFF, 0xFF, 0xFF };
    if (!mText.loadFromRenderedText(mRenderer, mFont, scoreText.str().c_str(), textColor)) {
        std::cout << "Unable to render score texture!" << std::endl;
    }
    
    dot.move(mScreenWidth, mScreenHight, paddleOne.getColliders(), paddleTwo.getColliders());   // Move the dot
    paddleOne.move(mScreenWidth, mScreenHight, dot.getCollider());                              // Move the paddle
    paddleTwo.move(mScreenWidth, mScreenHight, dot.getCollider());                              // Move the Paddle
    
    // Clear screen
    SDL_SetRenderDrawColor(mRenderer, 0x00, 0x00, 0x00, 0x00);
    SDL_RenderClear(mRenderer);
}

void Game::handleEvents() {
    SDL_Event event;
    
    while (SDL_PollEvent(&event) != 0) {
        // User requests quit
        if (event.type == SDL_QUIT) {
            mRunning = false;
        }
        
        paddleOne.handleEvent(event);   // Handle input for the paddle
        paddleTwo.handleEvent(event);   // Handle input for the paddle
    }
}

void Game::clean() {
    // Free loaded text
    mText.free();
    
    // Free font
    TTF_CloseFont(mFont);
    mFont = NULL;
    
    // Destroy window
    SDL_DestroyRenderer(mRenderer);
    SDL_DestroyWindow(mWindow);
    mWindow = NULL;
    mRenderer = NULL;
    
    // Quit SDL subsystems
    TTF_Quit();
    SDL_Quit();
}