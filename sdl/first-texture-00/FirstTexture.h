#ifndef _CAPP_H_
    #define _CAPP_H_
 
#include <SDL.h>
 
class FirstTexture {

    private:
        bool            Running;

        SDL_Renderer * renderer;

    public:
 
        FirstTexture();
 
        int OnExecute();
 
    public:

        FirstTexture();
        bool OnInit();
        void OnEvent(SDL_Event* Event);
        void OnRender();
        void OnLoop();
        void OnCleanup();

};
 
#endif
