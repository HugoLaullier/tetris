#include "headers/positionInSpace.hpp"

PositionInSpace::PositionInSpace(){};

PositionInSpace::PositionInSpace(std::vector<int> elements)
{
    for (int i = 0; i < elements.size(); i++)
        position[elements[i] / 4][elements[i] % 4] = 1;

    position[1][2] = 2;
};