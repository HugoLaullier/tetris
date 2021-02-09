#ifndef _POSITION_IN_SPACE_HPP_
#define _POSITION_IN_SPACE_HPP_

#include <vector>

class PositionInSpace
{
public:
    PositionInSpace(){};
    PositionInSpace(std::vector<int> elements);

private:
    int position[4][4] = {0};
};

#endif