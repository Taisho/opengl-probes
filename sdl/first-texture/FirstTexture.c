#include "FirstTexture.h"
 
bool FirstTexture::OnInit() {
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        return false;
    }

    SDL_Window *sdlWindow = SDL_CreateWindow(NULL,
                                SDL_WINDOWPOS_UNDEFINED,
                                SDL_WINDOWPOS_UNDEFINED,
                                0, 0,
                                SDL_WINDOW_FULLSCREEN_DESKTOP);

    renderer = SDL_CreateRenderer(sdlWindow, -1, 0);

    return true;
}
 
void FirstTexture::OnEvent(SDL_Event* Event) {
    if(Event->type == SDL_QUIT) {
        Running = false;
    }
}

void FirstTexture::OnLoop() {
}

void FirstTexture::OnRender() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
}

void FirstTexture::OnCleanup() {
    SDL_Quit();
}

FirstTexture::FirstTexture() {
    renderer = NULL;

    Running = true;
}
 
int FirstTexture::OnExecute() {
    if(OnInit() == false) {
        return -1;
    }

    SDL_Event Event;

    while(Running) {
        while(SDL_PollEvent(&Event)) {
            OnEvent(&Event);
        }

        OnLoop();
        OnRender();
    }

    OnCleanup();

    return 0;
}

int main(int argc, char* argv[]) {
    FirstTexture theApp;
 
    return theApp.OnExecute();
}
