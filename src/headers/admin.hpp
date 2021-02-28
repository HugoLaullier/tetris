#ifndef _ADMIN_HPP_
#define _ADMIN_HPP_

#include "constants.hpp"
#include "utils.hpp"
#include "game.hpp"

class Admin
{
private:
    status_t status;
    SDL_Renderer *renderer;
    SDL_Window *window;
    SDL_Event event;
    Mix_Music *music;
    TTF_Font *font;
    TTF_Font *font_small;
    int window_w;
    int window_h;

public:
    Admin();
    ~Admin();
    void load_font();
    void start();
    void menu();
    void help();
    void play_1();
    void menu_play_2();
    void play_2(int difficulty);
    void play_3();
};

#endif