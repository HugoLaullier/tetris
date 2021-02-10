/**
* \file tetrimino.hpp
* \brief Declaration file of the Tetrimino class
* \date 09/02/2021
* \author Hugo LAULLIER and Antoine BALZANO
*/
//------------------------------
#ifndef _TETRIMINO_HPP_
#define _TETRIMINO_HPP_

#include "positionInSpace.hpp"
//------------------------------

/**
* \class Tetrimino
* \brief Tetrimino class representing a piece in the Tetris game
*/
class Tetrimino
{
public:
    /*!
     * \brief Contructor of the Tetrimino class
     *
     */
    Tetrimino();

    /*!
     * \brief Constructor of the Tetrimino class with starting position
     *
     * \param x : starting position of the tetrimino according to the rows
     * \param y : starting position of the tetrimino according to the columns
     */
    Tetrimino(int x, int y);

protected:
    char type;                           /*!< type of the tetrimino (O for a square, I for a bar...)*/
    int orientation = 0;                 /*!< current orientation of the tetrimino (between 0 et 3)*/
    int x;                               /*!< position of the tetrimino according to the rows*/
    int y;                               /*!< position of the tetrimino according to the columns*/
    int color[3];                        /*!< tetrimino colour in RGB*/
    PositionInSpace positionsInSpace[4]; /*!< possible positions of the tetrimino*/
};

/**
* \class I
* \brief Class I representing the tretromino I (light blue)
*/
class I : public Tetrimino
{
public:
    /*!
     *  \brief Constructor of the class I
     *
     */
    I();
};

/**
* \class O
* \brief Class O representing the tretromino O (yellow)
*/
class O : public Tetrimino
{
public:
    /*!
     *  \brief Constructor of the class O
     *
     */
    O();
};

/**
* \class T
* \brief Class T representing the tretromino T (purple)
*/
class T : public Tetrimino
{
public:
    /*!
     *  \brief Constructor of the class T
     *
     */
    T();
};

/**
* \class L
* \brief Class L representing the tretromino L (orange)
*/
class L : public Tetrimino
{
public:
    /*!
     *  \brief Constructor of the class L
     *
     */
    L();
};

/**
* \class J
* \brief Class J representing the tretromino J (dark blue)
*/
class J : public Tetrimino
{
public:
    /*!
     *  \brief Constructor of the class J
     *
     */
    J();
};

/**
* \class Z
* \brief Class Z representing the tretromino Z (red)
*/
class Z : public Tetrimino
{
public:
    /*!
     *  \brief Constructor of the class Z
     *
     */
    Z();
};

/**
* \class S
* \brief Class S representing the tretromino S (green)
*/
class S : public Tetrimino
{
public:
    /*!
     *  \brief Constructor of the class S
     *
     */
    S();
};

#endif