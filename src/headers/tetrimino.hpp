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
#include "constants.hpp"
#include "utils.hpp"

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
    Tetrimino ();

    /*!
     * \brief Constructor of the Tetrimino class with starting position
     *
     * \param x : starting position of the tetrimino according to the rows
     * \param y : starting position of the tetrimino according to the columns
     */
    Tetrimino (int x, int y);

    Tetrimino (const Tetrimino& tetrimino);

    tile_name_t get_name () const;

    void get_position (int (*pos)[4][2]) const;
    void get_preview_position(int(*pos)[4][2]) const;

    std::vector<int> get_color() const;

    int get_x() const;
    int get_y() const;
    int get_orientation() const;
    void set_x(int x_);
    void set_y(int y_);

    int get_preview_x() const;
    int get_preview_y() const;
    int get_preview_orientation() const;

    void move_down();
    void move_left();
    void move_right();
    void move_x_y(int x_, int y_);
    void rotate_left();
    void rotate_right();
    void reset_pos();
    // return wallkick value for a given rotation and test number
    std::vector<int> get_wall_kick(int test, int rotation) const;

protected:
    char type;                           /*!< type of the tetrimino (O for a square, I for a bar...)*/
    tile_name_t name;                    /*!< name of the tetrimino*/
    int orientation = 0;                 /*!< current orientation of the tetrimino (between 0 et 3)*/
    int x;                               /*!< position of the tetrimino according to the rows*/
    int y;                               /*!< position of the tetrimino according to the columns*/
    int preview_x;
    int preview_y;
    int preview_orientation;
    std::vector<int> color;              /*!< tetrimino colour in RGB*/
    PositionInSpace positionsInSpace[4]; /*!< possible positions of the tetrimino*/
    int wallkick_table [8][5][2] = 
        {
            {{0,0},{-1,0},{-1,1}, {0,-2},{-1,-2}},
            {{0,0},{1,0}, {1,-1}, {0,2}, {1,2}  },

            {{0,0},{1,0}, {1,-1}, {0,2}, {1,2}  },
            {{0,0},{-1,0},{-1,1}, {0,-2},{-1,-2}},

            {{0,0},{1,0}, {1,1},  {0,-2},{1,-2} },
            {{0,0},{-1,0},{-1,-1},{0,2}, {-1,2} },

            {{0,0},{-1,0},{-1,-1},{0,2}, {-1,2} },
            {{0,0},{1,0}, {1,1},  {0,-2},{1,-2} }
        };
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
    int wallkick_table [8][5][2] = 
        {
            {{0,0},{-2,0},{1,0}, {-2,-1},{1,2}  },
            {{0,0},{2,0}, {-1,0},{2,1},  {-1,-2}},

            {{0,0},{-1,0},{2,0}, {-1,2}, {2,-1} },
            {{0,0},{1,0}, {-2,0},{1,-2}, {-2,-1}},

            {{0,0},{2,0}, {-1,0},{2,1},  {-1,-2}},
            {{0,0},{-2,0},{1,0}, {-2,-1},{1,2}  },

            {{0,0},{1,0}, {-2,0},{1,-2}, {-2,1} },
            {{0,0},{-1,0},{2,0}, {-1,2}, {2,-1} }
        };
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