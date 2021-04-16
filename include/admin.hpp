/**
* \file admin.hpp
* \brief Class Admin
* \date 09/02/2021
* \author Antoine BALZANO and Hugo LAULLIER
*/
#ifndef _ADMIN_HPP_
#define _ADMIN_HPP_

#include "constants.hpp"
#include "utils.hpp"
#include "game.hpp"

/**
* \class Admin
* \brief Admin class handling menus and games in single and multi player (vs IA)
*/
class Admin
{
private:
    /*!< status of the game IN_GAME, QUIT, PLAY_1, PLAY_2, PLAY_3, MENU, HELP */
    status_t status;

    /*!< SDL renderer */
    SDL_Renderer *renderer;

    /*!< SDL window */
    SDL_Window *window;

    /*!< SDL event */
    SDL_Event event;

    /*!< SDL music */
    Mix_Music *music;

    /*!< normal text font */
    TTF_Font *font;

    /*!< small text font */
    TTF_Font *font_small;

    /*!< window width */
    int window_w;

    /*!< window height */
    int window_h;

public:
    /*!
     * \brief Constructor of the class Admin
     */
    Admin();

    /*!
     * \brief Destructor of the class Admin
     */
    ~Admin();

    /*!
     * \brief Load text font
     */
    void load_font();

    /*!
     * \brief start the game
     */
    void start();

    /*!
     * \brief main menu
     */
    void menu();

    /*!
     * \brief help menu
     */
    void help();

    /*!
     * \brief launch a game in single player
     */
    void play_1();

    /*!
     * \brief multiplayer menu
     */
    void menu_play_2();

    /*!
     * \brief launch a multiplayer game (vs AI)
     * \param difficulty : difficulty of the AI
     */
    void play_2(int difficulty);

    /*!
     * \brief launch the AI demo
     */
    void play_3();
};

#endif