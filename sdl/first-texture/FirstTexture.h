#ifndef _CAPP_H_
    #define _CAPP_H_
 
#include <SDL.h>
 
class FirstTexture {

    private:
        bool            Running;

        SDL_Surface*    Surf_Display;
 
    public:
 
        CApp();
 
        int OnExecute();
 
    public:

        bool OnInit();
        void OnEvent(SDL_Event* Event);
        void OnLoop();
        void OnCleanup();

};
 
#endif
