#include "headers/tetrimino.hpp"

Tetrimino::Tetrimino () {}

Tetrimino::Tetrimino (int x, int y) : x(x), y(y) {}

Tetrimino::Tetrimino (const Tetrimino & tetrimino) :
    x(tetrimino.x), 
    y(tetrimino.y), 
    type(tetrimino.type), 
    name(tetrimino.name),
    orientation(tetrimino.orientation),
    color(tetrimino.color),
    preview_x(tetrimino.preview_x),
    preview_y(tetrimino.preview_y),
    preview_orientation(tetrimino.preview_orientation)
{
    for (int i = 0; i < 4; i++)
        positionsInSpace[i] = PositionInSpace(tetrimino.positionsInSpace[i]);
}

tile_name_t Tetrimino::get_name () const {
    return name;
}

void Tetrimino::get_position (int (*pos)[4][2]) const
{
    int cur_tile = 0;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (positionsInSpace[orientation].get_position_i_j(i,j))
            {
                (*pos)[cur_tile][0] = i + x;
                (*pos)[cur_tile][1] = j + y;
                cur_tile ++;
            }
        }
    }
}

void Tetrimino::get_preview_position (int(*pos)[4][2]) const
{
    int cur_tile = 0;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (positionsInSpace[preview_orientation].get_position_i_j(i,j))
            {
                (*pos)[cur_tile][0] = i + preview_x;
                (*pos)[cur_tile][1] = j + preview_y;
                cur_tile ++;
            }
        }
    }
}

std::vector<int> Tetrimino::get_color() const
{
    return color;
}

int Tetrimino::get_x() const
{
    return x;
}

int Tetrimino::get_y() const
{
    return y;
}

int Tetrimino::get_orientation() const
{
    return orientation;
}

void Tetrimino::set_x(int x_)
{
    x = x_;
}

void Tetrimino::set_y(int y_)
{
    y = y_;
}

int Tetrimino::get_preview_x() const
{
    return preview_x;
}

int Tetrimino::get_preview_y() const
{
    return preview_y;
}

int Tetrimino::get_preview_orientation() const
{
    return preview_orientation;
}

void Tetrimino::move_down()
{
    y ++;
}

void Tetrimino::move_left()
{
    x --;
}

void Tetrimino::move_right()
{
    x ++;
}

void Tetrimino::move_x_y(int x_, int y_)
{
    x += x_;
    y += y_;
}

void Tetrimino::rotate_left()
{
    orientation = (orientation - 1) % 4;
    if (orientation < 0)
        orientation += 4;
}
void Tetrimino::rotate_right()
{
    orientation = (orientation + 1) % 4;
    if (orientation > 3)
        orientation -= 4;
}

void Tetrimino::reset_pos()
{
    x = DEFAULT_STARTING_POS_X;
    y = DEFAULT_STARTING_POS_Y;
}

std::vector<int> Tetrimino::get_wall_kick(int test, int rotation) const
{
    return std::vector<int>{wallkick_table[rotation][test][0], 
                            wallkick_table[rotation][test][1]};
}

I::I() : Tetrimino(DEFAULT_STARTING_POS_X, DEFAULT_STARTING_POS_Y)
{
    type = 'I';
    name = tile_I;
    preview_x = 0;
    preview_y = 0;
    preview_orientation = 3;
    color = get_color_from_tile_name(tile_I);
    positionsInSpace[0] = PositionInSpace({{0,1}, {1,1}, {2,1}, {3,1}});
    positionsInSpace[1] = PositionInSpace({{2,0}, {2,1}, {2,2}, {2,3}});
    positionsInSpace[2] = PositionInSpace({{0,2}, {1,2}, {2,2}, {3,2}});
    positionsInSpace[3] = PositionInSpace({{1,0}, {1,1}, {1,2}, {1,3}});
};

O::O() : Tetrimino(DEFAULT_STARTING_POS_X, DEFAULT_STARTING_POS_Y)
{
    type = 'O';
    name = tile_O;
    preview_x = 0;
    preview_y = 1;
    preview_orientation = 0;
    color = get_color_from_tile_name(tile_O);
    positionsInSpace[0] = PositionInSpace({{1,0}, {2,0}, {1,1}, {2,1}});
    positionsInSpace[1] = PositionInSpace({{1,0}, {2,0}, {1,1}, {2,1}});
    positionsInSpace[2] = PositionInSpace({{1,0}, {2,0}, {1,1}, {2,1}});
    positionsInSpace[3] = PositionInSpace({{1,0}, {2,0}, {1,1}, {2,1}});
};

T::T() : Tetrimino(DEFAULT_STARTING_POS_X, DEFAULT_STARTING_POS_Y)
{
    type = 'T';
    name = tile_T;
    preview_x = 0;
    preview_y = 0;
    preview_orientation = 1;
    color = get_color_from_tile_name(tile_T);
    positionsInSpace[0] = PositionInSpace({{1,0}, {0,1}, {1,1}, {2,1}});
    positionsInSpace[1] = PositionInSpace({{1,0}, {1,1}, {2,1}, {1,2}});
    positionsInSpace[2] = PositionInSpace({{0,1}, {1,1}, {2,1}, {1,2}});
    positionsInSpace[3] = PositionInSpace({{1,0}, {0,1}, {1,1}, {1,2}});
};

L::L() : Tetrimino(DEFAULT_STARTING_POS_X, DEFAULT_STARTING_POS_Y)
{
    type = 'L';
    name = tile_L;
    preview_x = 0;
    preview_y = 0;
    preview_orientation = 1;
    color = get_color_from_tile_name(tile_L);
    positionsInSpace[0] = PositionInSpace({{2,0}, {0,1}, {1,1}, {2,1}});
    positionsInSpace[1] = PositionInSpace({{1,0}, {1,1}, {1,2}, {2,2}});
    positionsInSpace[2] = PositionInSpace({{0,1}, {1,1}, {2,1}, {0,2}});
    positionsInSpace[3] = PositionInSpace({{0,0}, {1,0}, {1,1}, {1,2}});
};

J::J() : Tetrimino(DEFAULT_STARTING_POS_X, DEFAULT_STARTING_POS_Y)
{
    type = 'J';
    name = tile_J;
    preview_x = 0;
    preview_y = 0;
    preview_orientation = 1;
    color = get_color_from_tile_name(tile_J);
    positionsInSpace[0] = PositionInSpace({{0,0}, {0,1}, {1,1}, {2,1}});
    positionsInSpace[1] = PositionInSpace({{1,0}, {2,0}, {1,1}, {1,2}});
    positionsInSpace[2] = PositionInSpace({{0,1}, {1,1}, {2,1}, {2,2}});
    positionsInSpace[3] = PositionInSpace({{1,0}, {1,1}, {0,2}, {1,2}});
};

Z::Z() : Tetrimino(DEFAULT_STARTING_POS_X, DEFAULT_STARTING_POS_Y)
{
    type = 'Z';
    name = tile_Z;
    preview_x = 0;
    preview_y = 0;
    preview_orientation = 1;
    color = get_color_from_tile_name(tile_Z);
    positionsInSpace[0] = PositionInSpace({{0,0}, {1,0}, {1,1}, {2,1}});
    positionsInSpace[1] = PositionInSpace({{2,0}, {1,1}, {2,1}, {1,2}});
    positionsInSpace[2] = PositionInSpace({{0,1}, {1,1}, {1,2}, {2,2}});
    positionsInSpace[3] = PositionInSpace({{1,0}, {0,1}, {1,1}, {0,2}});
};

S::S() : Tetrimino(DEFAULT_STARTING_POS_X, DEFAULT_STARTING_POS_Y)
{
    type = 'S';
    name = tile_S;
    preview_x = 0;
    preview_y = 0;
    preview_orientation = 1;
    color = get_color_from_tile_name(tile_S);
    positionsInSpace[0] = PositionInSpace({{1,0}, {2,0}, {0,1}, {1,1}});
    positionsInSpace[1] = PositionInSpace({{1,0}, {1,1}, {2,1}, {2,2}});
    positionsInSpace[2] = PositionInSpace({{1,1}, {2,1}, {0,2}, {1,2}});
    positionsInSpace[3] = PositionInSpace({{0,0}, {0,1}, {1,1}, {1,2}});
};
