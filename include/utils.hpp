/**
* \file utils.hpp
* \brief Declaration file of useful general functions
* \date 09/02/2021
* \author Hugo LAULLIER and Antoine BALZANO
*/

#ifndef _UTILS_HPP_
#define _UTILS_HPP_

#include "constants.hpp"

// -------------------------------------------------------------------------- //

/*!
* \brief Transforms tetris units (the size of one side of a square)
* into pixels for columns in board
* \param unit : unit of tetris to be transformed into a pixel
*/
int unit_to_pix_col_board(int unit);

/*!
* \brief Transforms tetris units (the size of one side of a square)
* into pixels for rows in board
* \param unit : unit of tetris to be transformed into a pixel
*/
int unit_to_pix_row_board(int unit);

// -------------------------------------------------------------------------- //

/*!
* \brief Transforms tetris units (the size of one side of a square)
* into pixels for columns in queue board
* \param unit : unit of tetris to be transformed into a pixel
*/
int unit_to_pix_col_queue(int unit);

/*!
* \brief Transforms tetris units (the size of one side of a square)
* into pixels for rows in queue board
* \param unit : unit of tetris to be transformed into a pixel
*/
int unit_to_pix_row_queue(int unit);

// -------------------------------------------------------------------------- //

/*!
* \brief Transforms tetris units (the size of one side of a square)
* into pixels for columns in hold board
* \param unit : unit of tetris to be transformed into a pixel
*/
int unit_to_pix_col_hold(int unit);

/*!
* \brief Transforms tetris units (the size of one side of a square)
* into pixels for rows in hold board
* \param unit : unit of tetris to be transformed into a pixel
*/
int unit_to_pix_row_hold(int unit);

// -------------------------------------------------------------------------- //

/*!
* \brief return true if (x,y) position is in board else false
* \param x : x position
* \param y : y position
*/
bool is_in_board(int x, int y);

/*!
* \brief return rgb color (vect 3) of a tile by its name
* \param tile : tile name (type tile_name_t)
*/
std::vector<int> get_color_from_tile_name(tile_name_t tile);

#define CHECK_SNPRINFT(n) do {if(n<0||n>=BUFF_SIZE)handle_perror(#n);}while(0)

/*!
* \brief exit program with a given error message
* \param msg : message to print in stderr
*/
[[ noreturn ]] void handle_error(const char * msg, ...);

/*!
* \brief exit program with a given error message
* \param msg : message to print in stderr
*/
[[ noreturn ]] void handle_perror(const char * msg, ...);

/*!
* \brief render text in canevas at position x,y
*/
void render_text(SDL_Renderer *renderer, TTF_Font *font, 
                 int x, int y, const char *text);

#endif