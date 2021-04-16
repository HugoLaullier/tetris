/**
* \file game.hpp
* \brief Declaration file of the Game class
* \date 09/02/2021
* \author Antoine BALZANO and Hugo LAULLIER
*/
#ifndef _GAME_HPP_
#define _GAME_HPP_

#include "constants.hpp"
#include "player.hpp"

/**
* \class Game
* \brief Game class, represent a tetris game, 3 possibilities : 
* single human player / human vs IA / IA demonstration
*/
class Game
{
private:
    /*!< player 1 (object Player) */
    Player *player_1;

    /*!< player 1 (object Player or nullptr) */
    Player *player_2;

    /*!< SDL event */
    SDL_Event event;

    /*!< SDL renderer */
    SDL_Renderer *renderer;

    /*!< SDL window */
    SDL_Window *window;

    /*!< normal text font */
    TTF_Font *font;

    /*!< small text font */
    TTF_Font *font_small;

    /*!< window width */
    int window_w;

    /*!< window height */
    int window_h;

    /*!< difficulty */
    double difficulty;

    /*!< status of the game PLAY_1 or PLAY_2 or PLAY_3 */
    status_t self_status;

public:
    /*!
     * \brief Constructor of the class Game for 1 player
     */
    Game(SDL_Window *window, SDL_Renderer *renderer,
         TTF_Font *font, TTF_Font *font_small,
         int window_w, int window_h, status_t status, double difficulty,
         Player *player);

    /*!
     * \brief Constructor of the class Game for 2 players
     */
    Game(SDL_Window *window, SDL_Renderer *renderer,
         TTF_Font *font, TTF_Font *font_small,
         int window_w, int window_h, status_t status, double difficulty,
         Player *p1, Player *p2);

    /*!
     * \brief Destructor of the class Game
     */
    ~Game();

    /*!
     * \brief display fps on canevas
     */
    void display_fps(double fps) const;

    /*!
     * \brief display results on canevas at the end of the game
     */
    void display_results(int winner) const;

    /*!
     * \brief display board grid on canevas
     */
    void display_board_grid() const;

    /*!
     * \brief display hold grid on canevas
     */
    void display_hold_grid() const;

    /*!
     * \brief display hold background on canevas
     */
    void display_hold_background() const;

    /*!
     * \brief display queue grid on canevas
     */
    void display_queue_grid() const;

    /*!
     * \brief display queue background on canevas
     */
    void display_queue_background() const;

    /*!
     * \brief method handling inputs of players, board and all other attributes
     */
    void game_loop(status_t *status,
                   double *delta_t,
                   double *counter_p1,
                   double *counter_p2,
                   double *counter_input_delay_p1,
                   double *counter_input_delay_p2);

    /*!
     * \brief create a loop wanting for a key press to exit the score screen
     * \param status : status of the game
     */
    void score_screen_loop(status_t *status);

    /*!
     * \brief main function handling the game, results, and status of the game
     */
    status_t play();
};

#endif