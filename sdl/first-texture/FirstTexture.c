#include "CApp.h"
 
bool FirstTexture::OnInit() {
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        return false;
    }

    if((Surf_Display = SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE | SDL_DOUBLEBUF)) == NULL) {
        return false;
    }

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
}

void FirstTexture::OnCleanup() {
    SDL_Quit();
}

FirstTexture::FirstTexture() {
    Surf_Display = NULL;

    Running = true;
}
 
int FirstTexture::FirstTexture() {
    return 0;
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
