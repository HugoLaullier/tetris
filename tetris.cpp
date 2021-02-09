
#include <SDL2/SDL.h>
#include <vector>
#include <iostream>
#include <utility>     

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Freq : 60Hz

#define NUMBER_COLS 12
#define NUMBER_ROWS 20

class PositionInSpace
{
public:
    PositionInSpace();
    PositionInSpace(std::vector<std::pair<int, int>> elements, std::pair<int, int> pivot) : 
    {
        for(int i = 0; i < elements.size; i++)
        {
            position[elements[i].first][elements[i].second] = 1;
        }

        position[pivot.first][pivot.second] = 2;
    };

private:
    int position[4][4] = {0};
    
};


class PositionInSpace
{
public:
    PositionInSpace();
    PositionInSpace(int elements[3], int pivot) : 
    {
        for(int i = 0; i < 3; i++)
            position[elements[i]/4][elements[i]%4]=1;
        
        position[pivot/4][pivot%4]=2;
    };

private:
    int position[4][4];
    
};


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
    I() : Tetrimino(1, 1)
    {
        color_r = 173;
        color_g = 216;
        color_b = 230;
        positionsInSpace[0] = PositionInSpace({4, 5, 7}, 6);
        positionsInSpace[1] = PositionInSpace({2, 10, 14}, 6);
        positionsInSpace[2] = PositionInSpace({4, 5, 7}, 6);
        positionsInSpace[3] = PositionInSpace({2, 10, 14}, 6);
    };
};

class O : public Tetrimino
{
public:
    O() : Tetrimino(1, 1)
    {
        color_r = 255;
        color_g = 255;
        color_b = 0;
        positionsInSpace[0] = PositionInSpace({5, 9, 10}, 6);
        positionsInSpace[1] = PositionInSpace({5, 9, 10}, 6);
        positionsInSpace[2] = PositionInSpace({5, 9, 10}, 6);
        positionsInSpace[3] = PositionInSpace({5, 9, 10}, 6);
    };
};

class T : public Tetrimino
{
public:
    T() : Tetrimino(1, 1)
    {
        color_r = 128;
        color_g = 0;
        color_b = 128;
        positionsInSpace[0] = PositionInSpace({5, 9, 10}, 6);
        positionsInSpace[1] = PositionInSpace({5, 9, 10}, 6);
        positionsInSpace[2] = PositionInSpace({5, 9, 10}, 6);
        positionsInSpace[3] = PositionInSpace({5, 9, 10}, 6);
    };
};

class L : public Tetrimino
{
public:
    L() : Tetrimino(1, 1)
    {
        color_r = 255;
        color_g = 140;
        color_b = 0;
        positionsInSpace[0] = PositionInSpace({5, 9, 10}, 6);
        positionsInSpace[1] = PositionInSpace({5, 9, 10}, 6);
        positionsInSpace[2] = PositionInSpace({5, 9, 10}, 6);
        positionsInSpace[3] = PositionInSpace({5, 9, 10}, 6);
    };
};

class J : public Tetrimino
{
public:
    J() : Tetrimino(1, 1)
    {
        color_r = 0;
        color_g = 0;
        color_b = 139;
        positionsInSpace[0] = PositionInSpace({5, 9, 10}, 6);
        positionsInSpace[1] = PositionInSpace({5, 9, 10}, 6);
        positionsInSpace[2] = PositionInSpace({5, 9, 10}, 6);
        positionsInSpace[3] = PositionInSpace({5, 9, 10}, 6);
    };
};

class Z : public Tetrimino
{
public:
    Z() : Tetrimino(1, 1)
    {
        color_r = 139;
        color_g = 0;
        color_b = 0;
        positionsInSpace[0] = PositionInSpace({5, 9, 10}, 6);
        positionsInSpace[1] = PositionInSpace({5, 9, 10}, 6);
        positionsInSpace[2] = PositionInSpace({5, 9, 10}, 6);
        positionsInSpace[3] = PositionInSpace({5, 9, 10}, 6);
    };
};

class S : public Tetrimino
{
public:
    S() : Tetrimino(1, 1)
    {
        color_r = 0;
        color_g = 255;
        color_b = 0;
        positionsInSpace[0] = PositionInSpace({5, 9, 10}, 6);
        positionsInSpace[1] = PositionInSpace({5, 9, 10}, 6);
        positionsInSpace[2] = PositionInSpace({5, 9, 10}, 6);
        positionsInSpace[3] = PositionInSpace({5, 9, 10}, 6);
    };
};

int unit_to_pix_col(int unit)
{
    return 30 * (unit + 5);
}

int unit_to_pix(int unit)
{
    return 30 * unit;
}

int main(int argc, char **argv)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
        return 1;

    SDL_Window *window = SDL_CreateWindow("Tetris", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, unit_to_pix_col(NUMBER_COLS + 5), unit_to_pix(NUMBER_ROWS), SDL_WINDOW_SHOWN);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    Tetrimino *board[NUMBER_COLS][NUMBER_ROWS] = {nullptr};
   
    bool quit = false;
    while (!quit)
    {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);
        SDL_Event event;
        while (!quit && SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                quit = true;
                break;
            case SDL_MOUSEBUTTONDOWN:
                printf("mouse click %d\n", event.button.button);
                break;
            default:
                break;
            }
        }

        for (int row = 0; row < NUMBER_ROWS; row++)
        {
            for (int col = 0; col < NUMBER_COLS; col++)
            { // Creat a rect at pos ( 50, 50 ) that's 50 pixels wide and 50 pixels high.
                SDL_Rect r;
                r.x = unit_to_pix_col(col);
                r.y = unit_to_pix(row);
                r.w = unit_to_pix(1);
                r.h = unit_to_pix(1);

                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

                // Render rect
                SDL_RenderFillRect(renderer, &r);

                // Set render color to blue ( rect will be rendered in this color )
                if (board[col][row] != nullptr)
                {
                    SDL_Rect piece_square_bckgrnd;
                    piece_square_bckgrnd.x = unit_to_pix_col(col);
                    piece_square_bckgrnd.y = unit_to_pix(row);
                    piece_square_bckgrnd.w = unit_to_pix(1);
                    piece_square_bckgrnd.h = unit_to_pix(1);
                    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                    SDL_RenderFillRect(renderer, &r);

                    int marge_square_piece = 1;
                    SDL_Rect piece_square;
                    piece_square.x = unit_to_pix_col(col) + marge_square_piece;
                    piece_square.y = unit_to_pix(row) + marge_square_piece;
                    piece_square.w = unit_to_pix(1) - 2 * marge_square_piece;
                    piece_square.h = unit_to_pix(1) - 2 * marge_square_piece;
                    SDL_SetRenderDrawColor(renderer, 229, 214, 15, 255);
                    SDL_RenderFillRect(renderer, &piece_square);
                }
            }
        }
        SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255); //Couleur rouge

        for (int row = 0; row < NUMBER_ROWS + 1; row++)
        {
            SDL_RenderDrawLine(renderer, unit_to_pix_col(0), unit_to_pix(row), unit_to_pix_col(NUMBER_COLS), unit_to_pix(row));
        }

        for (int col = 0; col < NUMBER_COLS + 1; col++)
        {
            SDL_RenderDrawLine(renderer, unit_to_pix_col(col), 0, unit_to_pix_col(col), unit_to_pix(NUMBER_ROWS));
        }
        // Render the rect to the screen
        SDL_RenderPresent(renderer);

        // SDL_UpdateWindowSurface(window);
    }

    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
