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

// Freq : 60Hz

/** 
 * \def NUMBER_COLS
 * \brief Number of columns on the tetris board
*/
#define NUMBER_COLS 12

/** 
 * \def NUMBER_ROWS
 * \brief Number of rows on the tetris tray
*/
#define NUMBER_ROWS 20

enum tile_name_t {tile_I, tile_O, tile_T, 
    tile_L, tile_J, tile_Z, tile_S, tile_empty}; // TODO maybe rename ?

#define QUEUE_SIZE 5
#define NB_TETRIMONO QUEUE_SIZE+1

#define DEFAULT_STARTING_POS_X 4
#define DEFAULT_STARTING_POS_Y 0

#define DEFAULT_GAME_SPEED 0.5
#define KEY_INPUT_COUNTER 0.1 // delay between inputs

enum rotate_dir_t {RIGHT, LEFT};

#endif