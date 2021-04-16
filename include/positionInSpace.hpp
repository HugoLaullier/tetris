/**
* \file positionInSpace.hpp
* \brief Class PositionInSpace
* \date 09/02/2021
* \author Hugo LAULLIER and Antoine BALZANO
*/

#ifndef _POSITION_IN_SPACE_HPP_
#define _POSITION_IN_SPACE_HPP_

#include "constants.hpp"

/**
* \class positionInSpace
* \brief Class positionInSpace represent the position of a tetrimino on the 
* board
*/
class PositionInSpace
{
public:
    /*!
     * \brief Constructor of the class Tetrimino (default position)
     */
    PositionInSpace();

    /*!
     * \brief Constructor of the class Tetrimino given a specific position
     * \param position_ : vector of coordinates in range [0,4[, [0,4[
     */
    PositionInSpace(std::vector<std::vector<int>> position_);

    /*!
     * \brief Copy constructor of the class Tetrimino
     * \param positionInSpace : Object to copy
     */
    PositionInSpace (const PositionInSpace & positionInSpace);

    /*!
     * \brief return true if position (i,j) is occupied else return false
     * \param i : x coordinate
     * \param j : y coordinate
     */
    bool get_position_i_j(int i, int j) const;

private:
    /*!< tiles occupied by a tetrimino on a 4x4 grid */
    int position[4][4] = {0};
};

#endif