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

/*!
*\brief Transforms tetris units (the size of one side of a square) into pixels for columns
*
* \param unit : unit of tetris to be transformed into a pixel
*/
int unit_to_pix_col(int unit);

/*!
*\brief Transforms tetris units (the size of one side of a square) into pixels
*
* \param unit : unit of tetris to be transformed into a pixel
*/
int unit_to_pix(int unit);

#endif