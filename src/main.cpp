#include "window.hpp"
#include "room.hpp"
#include "dclock.hpp"
#include "ui.hpp"

#include <iostream>
#include <memory>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#ifdef __EMSCRIPTEN__
#include <emscripten/emscripten.h>
#include <emscripten/html5.h>
#endif

std::unique_ptr<arc::Window> win;
arc::DeltaClock dclock;
const Uint8* keyboardState; // TODO: is it safe to turn this into a smart ptr?
Room room;

SDL_Texture* ptex;
SDL_Texture* ctex;

Uint32 mouseState;
int* mouseX;
int* mouseY;

static void mainloop()
{
    win->pollEvents();
    dclock.Tick();

    mouseState = SDL_GetMouseState(mouseX, mouseY);

    room.getInput(keyboardState);
    room.tick(dclock.dt);
    if (room.getState() == Room::GameState::GameOver) std::cout << "FUCK YOU" << std::endl;;

    win->clearScreen({ 255, 0, 255, 255 });
    win->draw(room);
    /* arc::ui::drawFrame(0, 0, 440, 340, {169, 147, 110, 255});
    arc::ui::drawFrame(0, 0, 400, 300, { 32, 32, 32, 255 });
    arc::ui::drawTextWrapped(0, 0, "int main()\n{\n    puts(\"hello world\");\n}", arc::ui::Mono, { 0, 255, 0, 255 }, 380); */
    win->display();
 
    if (!win->isOpen()) // like that will ever happen
    {
        //delete win; //zzzzzzzzzzzzzzno longer needed with smart pointer
        arc::ui::quit();
        SDL_DestroyTexture(ptex);
        SDL_DestroyTexture(ctex);
        IMG_Quit();
        TTF_Quit();
        SDL_Quit();
        delete mouseX; delete mouseY;

#ifdef __EMSCRIPTEN__
        emscripten_cancel_main_loop();
#else
        exit(0);
#endif
    }
}

int main(int argc, char** argv)
{
    if (SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO) != 0)
    {
        std::cerr << "SDL2 initialisation failed: "       << SDL_GetError() << std::endl;
        return 1;
    }
    if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG)
    {
        std::cerr << "SDL2_image initialisation failed: " << IMG_GetError() << std::endl;
        return 1;
    }
    if (TTF_Init() != 0)
    {
        std::cerr << "SDL2_ttf intialisation failed: "    << TTF_GetError() << std::endl;
        return 1;
    }
    std::cout << "Everything initialised properly" << std::endl;

    srand(time(0));

    win = std::make_unique<arc::Window>("Uniwersalna Maszyna Cyfrowa", 800, 600);
    if (!win->isOpen()) return 1;

    arc::ui::init("res/font/NotoSansMono.ttf", "res/font/NotoSerif.ttf", win->getSDLRenderer());
    
    ptex = win->loadTexture("res/img/fatguy.png");
    ctex = win->loadTexture("res/img/elwro.png");
    room.create(*ctex, *ptex, &mouseState, mouseX, mouseY);

    keyboardState = SDL_GetKeyboardState(NULL);

#ifdef __EMSCRIPTEN__
    emscripten_set_main_loop(mainloop, 0, 0);
#else
    while (true) mainloop();
#endif
}
