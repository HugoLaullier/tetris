#ifndef _GAME_HPP_
#define _GAME_HPP_

#include "constants.hpp"
#include "player.hpp"

class Game
{
private:
    Player *player_1;
    Player *player_2;
    SDL_Event event;
    SDL_Renderer *renderer;
    SDL_Window *window;
    TTF_Font *font;
    TTF_Font *font_small;
    int window_w;
    int window_h;
    double difficulty;
    status_t self_status; // PLAY_1 or PLAY_2 or PLAY_3

public:
    Game(SDL_Window *window, SDL_Renderer *renderer,
         TTF_Font *font, TTF_Font *font_small,
         int window_w, int window_h, status_t status, double difficulty,
         Player *player);
    Game(SDL_Window *window, SDL_Renderer *renderer,
         TTF_Font *font, TTF_Font *font_small,
         int window_w, int window_h, status_t status, double difficulty,
         Player *p1, Player *p2);
    void display_fps(double fps) const;
    void display_results(int winner) const;
    void display_board_grid() const;
    void display_hold_grid() const;
    void display_hold_background() const;
    void display_queue_grid() const;
    void display_queue_background() const;
    void game_loop(status_t *status,
                   double *delta_t,
                   double *counter_p1,
                   double *counter_p2,
                   double *counter_input_delay_p1,
                   double *counter_input_delay_p2);
    void score_screen_loop(status_t *status);
    status_t play();
};

#endif