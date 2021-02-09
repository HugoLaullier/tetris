#ifndef _TETRIMINO_HPP_
#define _TETRIMINO_HPP_

#include "positionInSpace.hpp"

class Tetrimino
{
public:
    Tetrimino();
    Tetrimino(int x, int y) : x(x), y(y){};

protected:
    int x;
    int y;
    int color_r;
    int color_g;
    int color_b;
    PositionInSpace positionsInSpace[4];
};

class I : public Tetrimino
{
public:
    I();
};

class O : public Tetrimino
{
public:
    O();
};

class T : public Tetrimino
{
public:
    T();
};

class L : public Tetrimino
{
public:
    L();
};

class J : public Tetrimino
{
public:
    J();
};

class Z : public Tetrimino
{
public:
    Z();
};

class S : public Tetrimino
{
public:
    S();
};

#endif