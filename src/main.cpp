#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <string>

#pragma execution_character_set("utf-8")


bool init();

void close();

SDL_Window* gWindow{ nullptr };


SDL_Renderer* gRenderer{ nullptr };

SDL_Texture* gTexture{ nullptr };


bool init() {

    bool success{ true };

    if (SDL_Init(SDL_INIT_VIDEO) == false) {
        SDL_Log("SDL_Init Err: %s\n", SDL_GetError());
        success = false;
    }
    else {

        gWindow = SDL_CreateWindow("SDL3 SoftWare", 800, 600, SDL_WINDOW_TRANSPARENT);
        if(gWindow == nullptr){
            SDL_Log("SDL_CreateWindow Err: %s\n", SDL_GetError());
            success = false;
        }


        gRenderer = SDL_CreateRenderer(gWindow, "software");
        if (gRenderer == nullptr) {
            SDL_Log("SDL_CreateRenderer Err: %s\n", SDL_GetError());
            return false;
        }

        if (!SDL_SetRenderDrawBlendMode(gRenderer, SDL_BLENDMODE_BLEND_PREMULTIPLIED)){
            SDL_Log("SDL_SetRenderDrawBlendMode Err: %s\n", SDL_GetError());
            return false;
        }

        gTexture = SDL_CreateTexture(gRenderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_TARGET, 800, 600);
        if (gTexture == nullptr) {
            SDL_Log("SDL_CreateTexture Err: %s\n", SDL_GetError());
            return false;
        }

        SDL_SetTextureBlendMode(gTexture, SDL_BLENDMODE_BLEND_PREMULTIPLIED);
    }

    return success;
}



void close() {

    SDL_DestroyTexture(gTexture);

    SDL_DestroyRenderer(gRenderer);

    SDL_DestroyWindow(gWindow);
    gWindow = nullptr;
    gRenderer = nullptr;
    gTexture = nullptr;

    SDL_Quit();
}

int main(int argc, char* args[]) {

    int exitCode{ 0 };

    if (init() == false) {
        SDL_Log("SDL init err!\n");
        exitCode = 1;
    }
    else {

        bool quit{ false };

        SDL_Event e;
        SDL_zero(e);
        
        while (quit == false) {
            while (SDL_PollEvent(&e) == true) {
                if (e.type == SDL_EVENT_QUIT) {
                    quit = true;
                }
            }

            SDL_FRect destRect;
            destRect.x = 0;
            destRect.y = 0;
            destRect.w = 100;
            destRect.h = 100;

            // Çå³ý´°¿Ú
            SDL_SetRenderDrawColor(gRenderer, 255, 0, 0, 255);
            SDL_SetRenderTarget(gRenderer, gTexture);

            SDL_RenderFillRect(gRenderer, &destRect);


            SDL_SetRenderTarget(gRenderer, nullptr);

            SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0);
            SDL_RenderClear(gRenderer);


            SDL_RenderTexture(gRenderer, gTexture, nullptr, nullptr);

            SDL_RenderPresent(gRenderer);
        }
    }

    close();
    return exitCode;
}
