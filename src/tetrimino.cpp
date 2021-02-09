#include "headers/tetrimino.hpp"

I::I() : Tetrimino(1, 1)
{
    color_r = 173;
    color_g = 216;
    color_b = 230;
    positionsInSpace[0] = PositionInSpace({4, 5, 7});
    positionsInSpace[1] = PositionInSpace({2, 10, 14});
    positionsInSpace[2] = PositionInSpace({4, 5, 7});
    positionsInSpace[3] = PositionInSpace({2, 10, 14});
};

O::O() : Tetrimino(1, 1)
{
    color_r = 255;
    color_g = 255;
    color_b = 0;
    positionsInSpace[0] = PositionInSpace({5, 9, 10});
    positionsInSpace[1] = PositionInSpace({5, 9, 10});
    positionsInSpace[2] = PositionInSpace({5, 9, 10});
    positionsInSpace[3] = PositionInSpace({5, 9, 10});
};

T::T() : Tetrimino(1, 1)
{
    color_r = 128;
    color_g = 0;
    color_b = 128;
    positionsInSpace[0] = PositionInSpace({5, 7, 10});
    positionsInSpace[1] = PositionInSpace({2, 7, 10});
    positionsInSpace[2] = PositionInSpace({2, 5, 7});
    positionsInSpace[3] = PositionInSpace({5, 9, 10});
};

L::L() : Tetrimino(1, 1)
{
    color_r = 255;
    color_g = 140;
    color_b = 0;
    positionsInSpace[0] = PositionInSpace({5, 7, 9});
    positionsInSpace[1] = PositionInSpace({2, 10, 11});
    positionsInSpace[2] = PositionInSpace({3, 5, 7});
    positionsInSpace[3] = PositionInSpace({1, 2, 10});
};

J::J() : Tetrimino(1, 1)
{
    color_r = 0;
    color_g = 0;
    color_b = 139;
    positionsInSpace[0] = PositionInSpace({5, 7, 11});
    positionsInSpace[1] = PositionInSpace({2, 3, 10});
    positionsInSpace[2] = PositionInSpace({1, 5, 7});
    positionsInSpace[3] = PositionInSpace({2, 9, 10});
};

Z::Z() : Tetrimino(1, 1)
{
    color_r = 139;
    color_g = 0;
    color_b = 0;
    positionsInSpace[0] = PositionInSpace({5, 10, 11});
    positionsInSpace[1] = PositionInSpace({3, 7, 10});
    positionsInSpace[2] = PositionInSpace({5, 10, 11});
    positionsInSpace[3] = PositionInSpace({3, 7, 10});
};

S::S() : Tetrimino(1, 1)
{
    color_r = 0;
    color_g = 255;
    color_b = 0;
    positionsInSpace[0] = PositionInSpace({7, 9, 10});
    positionsInSpace[1] = PositionInSpace({2, 7, 11});
    positionsInSpace[2] = PositionInSpace({7, 9, 10});
    positionsInSpace[3] = PositionInSpace({2, 7, 11});
};
