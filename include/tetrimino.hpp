/**
* \file tetrimino.hpp
* \brief Declaration file of the Tetrimino class
* \date 09/02/2021
* \author Hugo LAULLIER and Antoine BALZANO
*/

#ifndef _TETRIMINO_HPP_
#define _TETRIMINO_HPP_

#include "positionInSpace.hpp"
#include "constants.hpp"
#include "utils.hpp"

/**
* \class Tetrimino
* \brief Tetrimino class representing a piece in the Tetris game
*/
class Tetrimino
{
public:
    /*!
     * \brief Contructor of the Tetrimino class
     */
    Tetrimino ();

    /*!
     * \brief Constructor of the Tetrimino class with starting position
     * \param x : starting position of the tetrimino according to the rows
     * \param y : starting position of the tetrimino according to the columns
     */
    Tetrimino (int x, int y);

    /*!
     * \brief Copy constructor of the Tetrimino class
     * \param tetrimino : object to copy
     */
    Tetrimino (const Tetrimino& tetrimino);

    /*!
     * \brief Get the name of the tetrimino
     */
    tile_name_t get_name () const;

    /*!
     * \brief Get the position of the tetrimino
     */
    void get_position (int (*pos)[4][2]) const;

    /*!
     * \brief Get the preview position of the tetrimino
     */
    void get_preview_position(int(*pos)[4][2]) const;

    /*!
     * \brief Get the color of the tetrimino
     */
    std::vector<int> get_color() const;

    /*!
     * \brief Get the position x of the tetrimino
     */
    int get_x() const;

    /*!
     * \brief Get the position y of the tetrimino
     */
    int get_y() const;

    /*!
     * \brief Get the orientation of the tetrimino
     */
    int get_orientation() const;

    /*!
     * \brief Get the preview position x of the tetrimino
     */
    int get_preview_x() const;

    /*!
     * \brief Get the preview position y of the tetrimino
     */
    int get_preview_y() const;

    /*!
     * \brief Get the preview orientation of the tetrimino
     */
    int get_preview_orientation() const;

    /*!
     * \brief Set the position x of the tetrimino
     * \param x_ : value of new x position
     */
    void set_x(int x_);

    /*!
     * \brief Set the position x of the tetrimino
     * \param x_ : value of new x position
     */
    void set_y(int y_);

    /*!
     * \brief move down the tetrimino
     */
    void move_down();

    /*!
     * \brief move left the tetrimino
     */
    void move_left();

    /*!
     * \brief move right the tetrimino
     */
    void move_right();

    /*!
     * \brief move tetrimino to a specitic location
     * \param x_ : value of new x position
     * \param y_ : value of new y position
     */
    void move_x_y(int x_, int y_);

    /*!
     * \brief rotate left the tetrimino
     */
    void rotate_left();

    /*!
     * \brief rotate right the tetrimino
     */
    void rotate_right();

    /*!
     * \brief reset the position of the tetrimino
     */
    void reset_pos();

    /*!
     * \brief get the wall kick movement for a given test number and a rotation
     * \param test : test number [0,5[ (1st dimension in wall kick table)
     * \param rotation : rotation [0,8[ (2nd dimension in wall kick table)
     */
    std::vector<int> get_wall_kick(int test, int rotation) const;

protected:
    /*!< type of the tetrimino (O for a square, I for a bar...) */
    char type;

    /*!< name of the tetrimino */
    tile_name_t name;

    /*!< current orientation of the tetrimino (between 0 et 3) */
    int orientation = 0;
    
    /*!< position of the tetrimino according to the rows */
    int x;
    
    /*!< position of the tetrimino according to the columns */
    int y;
    
    /*!< position of the tetrimino according to the rows for its preview */
    int preview_x;
    
    /*!< position of the tetrimino according to the columns for its preview */
    int preview_y;
    
    /*!< orientation of the tetrimino for its preview */
    int preview_orientation;

    /*!< tetrimino colour in RGB */
    std::vector<int> color;
    
    /*!< possible positions of the tetrimino */
    PositionInSpace positionsInSpace[4];
    
    /*!< wall kick table of the tetrimino for the deplacement added to the 
         rotation, when the rotation is blocked by a piece or a wall */
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

// -------------------------------------------------------------------------- //

/**
* \class I
* \brief Class I representing the tretromino I (light blue)
*/
class I : public Tetrimino
{
public:
    /*!
     * \brief Constructor of the class I
     */
    I();
    /*!< specific Wall kick table for I tetrimino */
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
     * \brief Constructor of the class O
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
     * \brief Constructor of the class T
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
     * \brief Constructor of the class L
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
     * \brief Constructor of the class J
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
     * \brief Constructor of the class Z
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
     * \brief Constructor of the class S
     */
    S();
};

#endif