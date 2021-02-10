#include "headers/tetrimino.hpp"


Tetrimino::Tetrimino(){};

Tetrimino::Tetrimino(int x, int y) : x(x), y(y) {};

I::I() : Tetrimino(1, 1)
{
    type = 'I';
    color[0] = 173;
    color[1] = 216;
    color[2] = 230;
    positionsInSpace[0] = PositionInSpace({4, 5, 7});
    positionsInSpace[1] = PositionInSpace({2, 10, 14});
    positionsInSpace[2] = PositionInSpace({4, 5, 7});
    positionsInSpace[3] = PositionInSpace({2, 10, 14});
};

O::O() : Tetrimino(1, 1)
{
    type = 'O';
    color[0] = 255;
    color[1] = 255;
    color[2] = 0;
    positionsInSpace[0] = PositionInSpace({5, 9, 10});
    positionsInSpace[1] = PositionInSpace({5, 9, 10});
    positionsInSpace[2] = PositionInSpace({5, 9, 10});
    positionsInSpace[3] = PositionInSpace({5, 9, 10});
};

T::T() : Tetrimino(1, 1)
{
    type = 'T';
    color[0] = 128;
    color[1] = 0;
    color[2] = 128;
    positionsInSpace[0] = PositionInSpace({5, 7, 10});
    positionsInSpace[1] = PositionInSpace({2, 7, 10});
    positionsInSpace[2] = PositionInSpace({2, 5, 7});
    positionsInSpace[3] = PositionInSpace({5, 9, 10});
};

L::L() : Tetrimino(1, 1)
{
    type = 'L';
    color[0] = 255;
    color[1] = 140;
    color[2] = 0;
    positionsInSpace[0] = PositionInSpace({5, 7, 9});
    positionsInSpace[1] = PositionInSpace({2, 10, 11});
    positionsInSpace[2] = PositionInSpace({3, 5, 7});
    positionsInSpace[3] = PositionInSpace({1, 2, 10});
};

J::J() : Tetrimino(1, 1)
{
    type = 'J';
    color[0] = 0;
    color[1] = 0;
    color[2] = 139;
    positionsInSpace[0] = PositionInSpace({5, 7, 11});
    positionsInSpace[1] = PositionInSpace({2, 3, 10});
    positionsInSpace[2] = PositionInSpace({1, 5, 7});
    positionsInSpace[3] = PositionInSpace({2, 9, 10});
};

Z::Z() : Tetrimino(1, 1)
{
    type = 'Z';
    color[0] = 139;
    color[1] = 0;
    color[2] = 0;
    positionsInSpace[0] = PositionInSpace({5, 10, 11});
    positionsInSpace[1] = PositionInSpace({3, 7, 10});
    positionsInSpace[2] = PositionInSpace({5, 10, 11});
    positionsInSpace[3] = PositionInSpace({3, 7, 10});
};

S::S() : Tetrimino(1, 1)
{
    type = 'S';
    color[0] = 0;
    color[1] = 255;
    color[2] = 0;
    positionsInSpace[0] = PositionInSpace({7, 9, 10});
    positionsInSpace[1] = PositionInSpace({2, 7, 11});
    positionsInSpace[2] = PositionInSpace({7, 9, 10});
    positionsInSpace[3] = PositionInSpace({2, 7, 11});
};
