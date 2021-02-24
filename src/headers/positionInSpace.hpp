/**
* \file positionInSpace.hpp
* \brief Fichier de déclaration de la classe positionInSpace
* \date 09/02/2021
* \author Hugo LAULLIER and Antoine BALZANO
*/
//------------------------------
#ifndef _POSITION_IN_SPACE_HPP_
#define _POSITION_IN_SPACE_HPP_

#include <vector>
//------------------------------

/**
* \class positionInSpace
* \brief Classe positionInSpace représentant une position possible d'un tetrimino
*/
class PositionInSpace
{
public:
    /*!
     * \brief Constructeur de la classe Tetrimino
     *
     */
    PositionInSpace();

    /*!
     * \brief Constructeur de la classe Tetrimino avec la position des éléments formant le tetrimino
     * 
     * \param position_ : vector of coordinates in range [0,4[, [0,4[
     */
    PositionInSpace(std::vector<std::vector<int>> position_);

    PositionInSpace (const PositionInSpace & positionInSpace);

    // return a bool indicating if the position i, j is occupied
    bool get_position_i_j(int i, int j) const;

private:
    int position[4][4] = {0}; /*!< les éléments d'un tetrimino dans un tableau 4X4*/
};

#endif