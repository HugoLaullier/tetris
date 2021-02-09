#include <SDL2/SDL.h>
#include <utility>     

#include "headers/constants.hpp"
#include "headers/utils.hpp"

#include "headers/positionInSpace.hpp"
#include "headers/tetrimino.hpp"



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
            { 
                SDL_Rect r;
                r.x = unit_to_pix_col(col);
                r.y = unit_to_pix(row);
                r.w = unit_to_pix(1);
                r.h = unit_to_pix(1);

                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

                // Render rect
                SDL_RenderFillRect(renderer, &r);

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
        SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);

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
    }

    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
