#include "../include/positionInSpace.hpp"

PositionInSpace::PositionInSpace(){};

PositionInSpace::PositionInSpace(std::vector<std::vector<int>> position_)
{
    for (int i = 0; i < 4; i++)
        position[position_[i][0]][position_[i][1]] = 1;
};

PositionInSpace::PositionInSpace (const PositionInSpace & positionInSpace)
{
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            position[i][j] = positionInSpace.position[i][j];
}

bool PositionInSpace::get_position_i_j(int i, int j) const
{
    return position[i][j] != 0;
}
