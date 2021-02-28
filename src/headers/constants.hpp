/**
* \file constants.hpp
* \brief Declaration file of constants
* \date 09/02/2021
* \author Hugo LAULLIER and Antoine BALZANO
*/
//------------------------------
#ifndef _CONSTANTS_HPP_
#define _CONSTANTS_HPP_
//------------------------------

// includes

#include <vector>
#include <stdarg.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "SDL2/SDL_mixer.h"
#include <algorithm>
#include <utility>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <sstream>
#include <climits>

// Freq : 60Hz

/** 
 * \def NUMBER_COLS
 * \brief Number of columns on the tetris board
*/
#define NUMBER_COLS 10

/** 
 * \def NUMBER_ROWS
 * \brief Number of rows on the tetris tray
*/
#define NUMBER_ROWS 20

#define TILE_SIZE_PX 15
#define MARGIN_Y 35
#define MARGIN_X 35

enum status_t {IN_GAME, QUIT, PLAY_1, PLAY_2, PLAY_3, MENU, HELP}; 

enum tile_name_t {tile_I, tile_O, tile_T, 
    tile_L, tile_J, tile_Z, tile_S, tile_empty, title_add_line};

#define QUEUE_SIZE 5
#define NB_TETRIMONO QUEUE_SIZE+1

#define DEFAULT_STARTING_POS_X 3
#define DEFAULT_STARTING_POS_Y 0

#define DEFAULT_GAME_SPEED 0.4
#define KEY_INPUT_COUNTER 0.07 // delay between inputs

#define LEVEL_MAX 30

enum rotate_dir_t {RIGHT, LEFT};

enum input_t {INPUT_RIGHT, INPUT_LEFT, INPUT_UP, INPUT_DOWN, INPUT_CTRL,
              INPUT_C, INPUT_SPACE, INPUT_NONE};

#define DIFFICULTY_EASY 8
#define DIFFICULTY_NORMAL 4
#define DIFFICULTY_HARD 2
#define DIFFICULTY_IMPOSSIBLE 0

#define COMPUTE_FPS true

#define BUFF_SIZE 1024

#endif