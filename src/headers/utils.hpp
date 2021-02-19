/**
* \file utils.hpp
* \brief Declaration file of useful general functions
* \date 09/02/2021
* \author Hugo LAULLIER and Antoine BALZANO
*/
//------------------------------
#ifndef _UTILS_HPP_
#define _UTILS_HPP_
//------------------------------
#include <vector>
#include <iostream>
#include <stdarg.h>
#include "constants.hpp"

/*!
*\brief Transforms tetris units (the size of one side of a square) into pixels for columns
*
* \param unit : unit of tetris to be transformed into a pixel
*/
int unit_to_pix_col_board(int unit);

/*!
*\brief Transforms tetris units (the size of one side of a square) into pixels
*
* \param unit : unit of tetris to be transformed into a pixel
*/
int unit_to_pix_row_board(int unit);

int unit_to_pix_col_queue(int unit);

int unit_to_pix_row_queue(int unit);

int unit_to_pix_col_hold(int unit);

int unit_to_pix_row_hold(int unit);

bool is_in_board(int x, int y);

std::vector<int> get_color_from_tile_name(tile_name_t tile);

#define BUFF_SIZE 1024

#define CHECK_SNPRINFT(n) do {if(n<0||n>=BUFF_SIZE)handle_perror(#n);}while(0)

[[ noreturn ]] void handle_error(const char * msg, ...);

[[ noreturn ]] void handle_perror(const char * msg, ...);

#endif