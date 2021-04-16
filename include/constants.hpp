/**
* \file constants.hpp
* \brief Declaration file of constants
* \date 09/02/2021
* \author Hugo LAULLIER and Antoine BALZANO
*/
#ifndef _CONSTANTS_HPP_
#define _CONSTANTS_HPP_

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

/** 
 * \def TILE_SIZE_PX
 * \brief size of a tile on the board in px
 */
#define TILE_SIZE_PX 15

/** 
 * \def MARGIN_Y
 * \brief margin y of board in px
 */
#define MARGIN_Y 35

/** 
 * \def MARGIN_Y
 * \brief margin x of board in px
 */
#define MARGIN_X 35

/** 
 * \def status_t
 * \brief represent the status of the game, in menu, in gqme, in help, etc ...
 */
enum status_t {IN_GAME, QUIT, PLAY_1, PLAY_2, PLAY_3, MENU, HELP}; 

/** 
 * \def tile_name_t
 * \brief name of each different tiles type (1 name = 1 color)
 */
enum tile_name_t {tile_I, tile_O, tile_T, 
    tile_L, tile_J, tile_Z, tile_S, tile_empty, title_add_line};

/** 
 * \def QUEUE_SIZE
 * \brief size of the queue of next tetrimino
 */
#define QUEUE_SIZE 5

/** 
 * \def NB_TETRIMONO
 * \brief Number of tetrimino in queue + current tetrimino
 */
#define NB_TETRIMONO QUEUE_SIZE+1

/** 
 * \def DEFAULT_STARTING_POS_X
 * \brief default starting position x of a tetrimino on the board
 */
#define DEFAULT_STARTING_POS_X 3

/** 
 * \def DEFAULT_STARTING_POS_Y
 * \brief default starting position y of a tetrimino on the board
 */
#define DEFAULT_STARTING_POS_Y 0

/** 
 * \def DEFAULT_GAME_SPEED
 * \brief delay between 2 drop of a piece (speed of the fall of a tetrimino)
 */
#define DEFAULT_GAME_SPEED 0.4

/** 
 * \def KEY_INPUT_COUNTER
 * \brief delay between 2 player inputs
 */
#define KEY_INPUT_COUNTER 0.07

/** 
 * \def LEVEL_MAX
 * \brief maximum level possible
 */
#define LEVEL_MAX 30

/** 
 * \def rotate_dir_t
 * \brief indicate the direction of the rotation
 */
enum rotate_dir_t {RIGHT, LEFT};

/** 
 * \def input_t
 * \brief represent an player input on the keyboard
 */
enum input_t {INPUT_RIGHT, INPUT_LEFT, INPUT_UP, INPUT_DOWN, INPUT_CTRL,
              INPUT_C, INPUT_SPACE, INPUT_NONE};

/** 
 * \def DIFFICULTY_EASY
 * \brief multiplier for the speed of the AI for easy difficulty
 */
#define DIFFICULTY_EASY 8

/** 
 * \def DIFFICULTY_NORMAL
 * \brief multiplier for the speed of the AI for normal difficulty
 */
#define DIFFICULTY_NORMAL 4

/** 
 * \def DIFFICULTY_HARD
 * \brief multiplier for the speed of the AI for hard difficulty
 */
#define DIFFICULTY_HARD 2

/** 
 * \def DIFFICULTY_IMPOSSIBLE
 * \brief multiplier for the speed of the AI for impossible difficulty
 */
#define DIFFICULTY_IMPOSSIBLE 0

/** 
 * \def COMPUTE_FPS
 * \brief indicate if the fps should be displayed on screen
 */
#define COMPUTE_FPS true

/** 
 * \def BUFF_SIZE
 * \brief buff size for static allocation
 */
#define BUFF_SIZE 1024

#endif