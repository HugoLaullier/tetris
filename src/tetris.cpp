#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "SDL2/SDL_mixer.h"
#include <vector>
#include <algorithm>
#include <utility>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <sstream>

#include "headers/constants.hpp"
#include "headers/utils.hpp"

#include "headers/positionInSpace.hpp"
#include "headers/tetrimino.hpp"

class Game
{
private:
    int line_completed;
    int level;
    int score;
    double speed;
    SDL_Event event;
    SDL_Renderer *renderer;
    SDL_Window *window;
    Tetrimino *current_tetrimino;
    Tetrimino *hold;
    // first element is current_tetrimino
    // rest is part of the queue
    std::vector<Tetrimino *> queue_tetrimino;
    tile_name_t board[NUMBER_COLS][NUMBER_ROWS];
    // tetrimino queue on right side todo
    // class player ?
    int offset_y_queue = 37;
    bool is_hold_available = true;
    bool is_game_over = false;

public:
    Game();
    Game(SDL_Window *new_window, SDL_Renderer *new_renderer);
    // TODO destructeur
    void display_board() const;
    void display_current_tetrimino() const;
    // Display grid (lines in gray)
    void display_board_grid() const;
    void display_queue_background() const;
    void display_queue_tetrimino() const;
    void display_queue_grid() const;
    void display_hold_background() const;
    void display_hold_tetrimino() const;
    void display_hold_grid() const;
    // shift down all rows above the k th row
    void shift_down_board(int k);
    void new_tetrimino();
    void new_hold();
    // remove line 1, 2, 3 or 4
    // return false if the current tetrimino is blocked
    bool move_down();
    bool move_left();
    bool move_right();
    void fast_down();
    bool rotate(rotate_dir_t dir);
    void keyboard(const Uint8 *keys);
    void render_text(TTF_Font *font, int x, int y, const char *text);
    // display score, level, line completed
    void display_game_info();
    void display_results();
    status_t play();
    void end();
};

Game::Game(){};

Game::Game(SDL_Window *window, SDL_Renderer *renderer) : window(window), renderer(renderer),
                                                         current_tetrimino(nullptr), speed(DEFAULT_GAME_SPEED), line_completed(0), level(1), score(0), hold(nullptr)
{
    for (int i = 0; i < NUMBER_COLS; i++)
        for (int j = 0; j < NUMBER_ROWS; j++)
            board[i][j] = tile_empty;

    for (int i = 0; i < NB_TETRIMONO; i++)
    {
        int r = rand() % 7;
        r = 0; // DEBUG
        switch (r)
        {
        case 0:
            queue_tetrimino.push_back(new I);
            break;
        case 1:
            queue_tetrimino.push_back(new O);
            break;
        case 2:
            queue_tetrimino.push_back(new T);
            break;
        case 3:
            queue_tetrimino.push_back(new L);
            break;
        case 4:
            queue_tetrimino.push_back(new J);
            break;
        case 5:
            queue_tetrimino.push_back(new Z);
            break;
        case 6:
            queue_tetrimino.push_back(new S);
            break;
        default:
            queue_tetrimino.push_back(new I);
            break;
        }
    }
    current_tetrimino = queue_tetrimino[0];
}

void Game::display_board() const
{
    for (int row = 0; row < NUMBER_ROWS; row++)
    {
        for (int col = 0; col < NUMBER_COLS; col++)
        {
            SDL_Rect r = {
                unit_to_pix_col_board(col),
                unit_to_pix_row_board(row),
                unit_to_pix_row_board(1),
                unit_to_pix_row_board(1)};
            if (board[col][row] != tile_empty)
            {
                std::vector<int> color =
                    get_color_from_tile_name(board[col][row]);
                SDL_SetRenderDrawColor(
                    renderer, color[0], color[1], color[2], 255);
            }
            else
            {
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            }
            SDL_RenderFillRect(renderer, &r);
        }
    }
}

void Game::display_current_tetrimino() const
{
    int pos[4][2];
    current_tetrimino->get_position(&pos);
    for (int i = 0; i < 4; i++)
    {
        if (pos[i][1] >= 0)
        {
            SDL_Rect r = {
                unit_to_pix_col_board(pos[i][0]),
                unit_to_pix_row_board(pos[i][1]),
                unit_to_pix_row_board(1),
                unit_to_pix_row_board(1)};
            std::vector<int> color = current_tetrimino->get_color();
            SDL_SetRenderDrawColor(
                renderer, color[0], color[1], color[2], 255);
            SDL_RenderFillRect(renderer, &r);
        }
    }
}

void Game::display_board_grid() const
{
    SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);

    for (int row = 0; row < NUMBER_ROWS + 1; row++)
    {
        SDL_RenderDrawLine(renderer,
                           unit_to_pix_col_board(0),
                           unit_to_pix_row_board(row),
                           unit_to_pix_col_board(NUMBER_COLS),
                           unit_to_pix_row_board(row));
    }

    for (int col = 0; col < NUMBER_COLS + 1; col++)
    {
        SDL_RenderDrawLine(renderer,
                           unit_to_pix_col_board(col),
                           0,
                           unit_to_pix_col_board(col),
                           unit_to_pix_row_board(NUMBER_ROWS));
    }
}

void Game::display_queue_background() const
{
    for (int row = 0; row < 5 * QUEUE_SIZE + 1; row++)
    {
        for (int col = 0; col < 4; col++)
        {
            SDL_Rect r = {
                unit_to_pix_col_queue(col),
                unit_to_pix_row_queue(row) + offset_y_queue,
                unit_to_pix_row_queue(1),
                unit_to_pix_row_queue(1)};
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderFillRect(renderer, &r);
        }
    }
}

void Game::display_queue_tetrimino() const
{
    for (int i = 1; i < NB_TETRIMONO; i++)
    {
        int pos[4][2];
        queue_tetrimino[i]->get_preview_position(&pos);
        for (int j = 0; j < 4; j++)
        {
            SDL_Rect r = {
                unit_to_pix_col_queue(pos[j][0]),
                unit_to_pix_row_queue(pos[j][1] + 1 + 5 * (i - 1)) + offset_y_queue,
                unit_to_pix_row_queue(1),
                unit_to_pix_row_queue(1)};
            std::vector<int> color = queue_tetrimino[i]->get_color();
            SDL_SetRenderDrawColor(
                renderer, color[0], color[1], color[2], 255);
            SDL_RenderFillRect(renderer, &r);
        }
    }
}

void Game::display_queue_grid() const
{
    SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);

    for (int row = 0; row <= 5 * QUEUE_SIZE + 1; row++)
    {
        SDL_RenderDrawLine(renderer,
                           unit_to_pix_col_queue(0),
                           unit_to_pix_row_queue(row) + offset_y_queue,
                           unit_to_pix_col_queue(4),
                           unit_to_pix_row_queue(row) + offset_y_queue);
    }

    for (int col = 0; col <= 4; col++)
    {
        SDL_RenderDrawLine(renderer,
                           unit_to_pix_col_queue(col),
                           unit_to_pix_row_queue(0) + offset_y_queue,
                           unit_to_pix_col_queue(col),
                           unit_to_pix_row_queue(5 * QUEUE_SIZE + 1) + offset_y_queue);
    }
}

void Game::display_hold_background() const
{
    for (int row = 0; row <= 5; row++)
    {
        for (int col = 0; col <= 4; col++)
        {
            SDL_Rect r = {
                unit_to_pix_col_hold(col),
                unit_to_pix_row_hold(row) + offset_y_queue,
                unit_to_pix_row_hold(1),
                unit_to_pix_row_hold(1)};
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderFillRect(renderer, &r);
        }
    }
}

void Game::display_hold_tetrimino() const
{
    if (hold == nullptr)
        return;

    int pos[4][2];
    hold->get_preview_position(&pos);
    for (int i = 0; i < 4; i++)
    {
        SDL_Rect r = {
            unit_to_pix_col_hold(pos[i][0] + 1),
            unit_to_pix_row_hold(pos[i][1] + 1) + offset_y_queue,
            unit_to_pix_row_hold(1),
            unit_to_pix_row_hold(1)};
        std::vector<int> color = hold->get_color();
        SDL_SetRenderDrawColor(
            renderer, color[0], color[1], color[2], 255);
        SDL_RenderFillRect(renderer, &r);
    }
}

void Game::display_hold_grid() const
{
    SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);

    for (int row = 0; row <= 6; row++)
    {
        SDL_RenderDrawLine(renderer,
                           unit_to_pix_col_hold(0),
                           unit_to_pix_row_hold(row) + offset_y_queue,
                           unit_to_pix_col_hold(5),
                           unit_to_pix_row_hold(row) + offset_y_queue);
    }

    for (int col = 0; col <= 5; col++)
    {
        SDL_RenderDrawLine(renderer,
                           unit_to_pix_col_hold(col),
                           unit_to_pix_row_hold(0) + offset_y_queue,
                           unit_to_pix_col_hold(col),
                           unit_to_pix_row_hold(6) + offset_y_queue);
    }
}

void Game::shift_down_board(int k)
{
    for (int i = k - 1; i >= 0; i--)
        for (int j = 0; j < NUMBER_COLS; j++)
            board[j][i + 1] = board[j][i];
}

void Game::new_tetrimino()
{
    std::rotate(queue_tetrimino.begin(),
                queue_tetrimino.begin() + 1,
                queue_tetrimino.end());
    current_tetrimino = queue_tetrimino[0];
    queue_tetrimino.pop_back();
    int r = rand() % 7;
    //int r = 0;
    switch (r)
    {
    case 0:
        queue_tetrimino.push_back(new I);
        break;
    case 1:
        queue_tetrimino.push_back(new O);
        break;
    case 2:
        queue_tetrimino.push_back(new T);
        break;
    case 3:
        queue_tetrimino.push_back(new L);
        break;
    case 4:
        queue_tetrimino.push_back(new J);
        break;
    case 5:
        queue_tetrimino.push_back(new Z);
        break;
    case 6:
        queue_tetrimino.push_back(new S);
        break;
    default:
        queue_tetrimino.push_back(new I);
        break;
    }
    // set the position for the new tetrimino
    int x = current_tetrimino->get_x();
    int y = current_tetrimino->get_y();
    int max_y_occupied = -1; // higher row not empty
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (board[i + x][j + y] != tile_empty &&
                (max_y_occupied == -1 || max_y_occupied > j + y))
            {
                max_y_occupied = j + y;
            }
        }
    }
    if (max_y_occupied != -1)
    {
        current_tetrimino->set_y(y - 4);
    }

    // detect if a line is full
    std::vector<int> line_full;
    for (int i = NUMBER_ROWS - 1; i >= 0; i--)
    {
        int c = 0;
        for (int j = 0; j < NUMBER_COLS; j++)
            if (board[j][i] != tile_empty)
                c++;

        if (c == NUMBER_COLS)
            line_full.push_back(i);
    }
    for (int i = 0; i < line_full.size(); i++)
        for (int j = 0; j < NUMBER_COLS; j++)
            board[j][line_full[i]] = tile_empty;

    int i = 0;
    for (int i = 0; i < line_full.size(); i++)
        shift_down_board(line_full[i] + i);

    // update game info
    // TODO increase speed
    line_completed += line_full.size();
    if (line_completed >= level * 10 && level <= 30)
        level++;
    switch (line_full.size())
    {
    case 1:
        score += 40 * level;
        break;
    case 2:
        score += 100 * level;
        break;
    case 3:
        score += 300 * level;
        break;
    case 4:
        score += 1200 * level;
        break;
    default:
        break;
    }
    is_hold_available = true;
    // TODO animation ?
    //TODO TEST IF BOARD FULL
    // ---------------------------
    // std::cout << std::endl;
    //test if game over here todo (can't place a new tetrimino)
}

void Game::new_hold()
{
    if (is_hold_available)
    {
        if (hold == nullptr)
        {
            hold = new Tetrimino(*current_tetrimino);
            hold->reset_pos();
            new_tetrimino();
        }
        else
        {
            Tetrimino *temp_copy = new Tetrimino(*current_tetrimino);
            current_tetrimino = hold;
            hold = temp_copy;
            hold->reset_pos();
        }
        is_hold_available = false;
    }
}

bool Game::move_down()
{
    int pos[4][2];
    current_tetrimino->get_position(&pos);
    bool is_outside = false;
    for (int i = 0; i < 4; i++)
        if (pos[i][1] < 0)
            is_outside = true;

    for (int i = 0; i < 4; i++)
    {
        if (pos[i][1] + 1 >= 0 &&
            (board[pos[i][0]][pos[i][1] + 1] != tile_empty ||
             pos[i][1] + 1 >= NUMBER_ROWS))
        {
            if (is_outside)
            {
                is_game_over = true;
                return false;
            }
            for (int i = 0; i < 4; i++)
            {
                board[pos[i][0]][pos[i][1]] = current_tetrimino->get_name();
            }
            return false;
        }
    }
    current_tetrimino->move_down();
    return true;
}

bool Game::move_left()
{
    int pos[4][2];
    current_tetrimino->get_position(&pos);
    for (int i = 0; i < 4; i++)
    {
        if (pos[i][1] < 0)
        {
            if (pos[i][0] - 1 < 0)
            {
                return false;
            }
        }
        else
        {
            if (board[pos[i][0] - 1][pos[i][1]] != tile_empty ||
                pos[i][0] - 1 < 0)
            {
                return false; // movement is blocked
            }
        }
    }
    current_tetrimino->move_left();
    return true;
}

bool Game::move_right()
{
    int pos[4][2];
    current_tetrimino->get_position(&pos);
    for (int i = 0; i < 4; i++)
    {
        if (pos[i][1] < 0)
        {
            if (pos[i][0] + 1 >= NUMBER_COLS)
            {
                return false;
            }
        }
        else
        {
            if (board[pos[i][0] + 1][pos[i][1]] != tile_empty ||
                pos[i][0] + 1 >= NUMBER_COLS)
            {
                return false; // movement is blocked
            }
        }
    }
    current_tetrimino->move_right();
    return true;
}

void Game::fast_down()
{
    while (move_down())
        ;
    new_tetrimino();
}

bool Game::rotate(rotate_dir_t dir)
{
    int rotation;
    if (dir == RIGHT)
        rotation = current_tetrimino->get_orientation() * 2;
    else
        rotation = current_tetrimino->get_orientation() * 2 + 1;

    // rotate a test tetrimino (copy of current)
    Tetrimino *test_tetrimino = new Tetrimino(*current_tetrimino);
    if (dir == RIGHT)
        test_tetrimino->rotate_right();
    else
        test_tetrimino->rotate_left();

    bool is_rotation_possible = false;
    int origin_x = current_tetrimino->get_x();
    int origin_y = current_tetrimino->get_y();
    std::vector<int> wall_kick;
    // do 5 tests (https://tetris.fandom.com/wiki/SRS)
    for (int i = 0; i < 5; i++)
    {
        wall_kick = test_tetrimino->get_wall_kick(i, rotation);
        if (test_tetrimino->get_name() == tile_O)
        {
            is_rotation_possible = true;
            break;
        }
        test_tetrimino->set_x(origin_x + wall_kick[0]);
        test_tetrimino->set_y(origin_y + wall_kick[1]);
        int pos[4][2];
        test_tetrimino->get_position(&pos);
        int count_empty_tiles = 0;
        for (int j = 0; j < 4; j++)
        {
            if (!is_in_board(pos[j][0], pos[j][1]) ||
                board[pos[j][0]][pos[j][1]] != tile_empty)
                break;
            count_empty_tiles++;
        }
        if (count_empty_tiles == 4)
        {
            is_rotation_possible = true;
            break;
        }
    }
    if (is_rotation_possible)
    {
        if (dir == RIGHT)
            current_tetrimino->rotate_right();
        else
            current_tetrimino->rotate_left();
        current_tetrimino->move_x_y(wall_kick[0], wall_kick[1]);
    }
    else
    {
        printf("rotation blocked\n"); // DEBUG
    }
    delete test_tetrimino;
    return true;
}

void Game::keyboard(const Uint8 *keys)
{
    static bool fast_down_available = true;
    static bool rotate_available = true;
    if (keys[SDL_SCANCODE_C])
    {
        new_hold();
    }
    if (keys[SDL_SCANCODE_SPACE] && fast_down_available)
    {
        fast_down();
        fast_down_available = false;
    }
    if (!keys[SDL_SCANCODE_SPACE])
    {
        fast_down_available = true;
    }
    if (keys[SDL_SCANCODE_UP] && rotate_available)
    {
        rotate(RIGHT);
        rotate_available = false;
    }
    if (keys[SDL_SCANCODE_LCTRL] && rotate_available)
    {
        rotate(LEFT);
        rotate_available = false;
    }
    if (!keys[SDL_SCANCODE_UP] && !keys[SDL_SCANCODE_LCTRL])
    {
        rotate_available = true;
    }
    if (keys[SDL_SCANCODE_LEFT])
    {
        move_left();
    }
    if (keys[SDL_SCANCODE_RIGHT])
    {
        move_right();
    }
    if (keys[SDL_SCANCODE_DOWN])
    {
        if (!move_down())
        {
            if (is_game_over)
            {
                return;
            }
            new_tetrimino();
        }
    }
}

void Game::render_text(TTF_Font *font, int x, int y, const char *text)
{
    SDL_Surface *message =
        TTF_RenderText_Shaded(font, text, {0, 0, 0}, {255, 255, 255});
    //TTF_RenderText_Blended(font, text, {0, 0, 0}); // (slower)
    SDL_Texture *texture =
        SDL_CreateTextureFromSurface(renderer, message);
    int texW = 0;
    int texH = 0;
    SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
    SDL_Rect rect = {x, y, texW, texH};
    SDL_RenderCopy(renderer, texture, NULL, &rect);
    SDL_FreeSurface(message);
    SDL_DestroyTexture(texture);
}

void Game::display_game_info()
{
    TTF_Font *font = TTF_OpenFont("./src/font/OpenSans-Regular.ttf", 24);
    if (font == NULL)
    {
        fprintf(stderr, "error: font not found\n");
        exit(EXIT_FAILURE);
    }
    int offset_x = 10;
    int offset_y = 300;
    char *text = new char[BUFF_SIZE];
    render_text(font, offset_x, offset_y, "Score :");
    CHECK_SNPRINFT(snprintf(text, BUFF_SIZE, "%i", score));
    render_text(font, offset_x, offset_y + 40, text);
    render_text(font, offset_x, offset_y + 80, "Lines :");
    CHECK_SNPRINFT(snprintf(text, BUFF_SIZE, "%i", line_completed));
    render_text(font, offset_x, offset_y + 120, text);
    render_text(font, offset_x, offset_y + 160, "Level :");
    if (level == 30)
        CHECK_SNPRINFT(snprintf(text, BUFF_SIZE, "max"));
    else
        CHECK_SNPRINFT(snprintf(text, BUFF_SIZE, "%i", level));
    render_text(font, offset_x, offset_y + 200, text);
    render_text(font, offset_x + 25, 150, "Press C");
    render_text(font, offset_x + 25, 180, "to hold");
    delete[] text;
    TTF_CloseFont(font);
}

void Game::display_results()
{
    TTF_Font *font = TTF_OpenFont("./src/font/OpenSans-Regular.ttf", 24);
    if (font == NULL)
    {
        fprintf(stderr, "error: font not found\n");
        exit(EXIT_FAILURE);
    }
    TTF_Font *font_small = TTF_OpenFont("./src/font/OpenSans-Regular.ttf", 19);
    if (font_small == NULL)
    {
        fprintf(stderr, "error: font not found\n");
        exit(EXIT_FAILURE);
    }
    int offset_y = 80;
    char *text = new char[BUFF_SIZE];
    int width_text;
    TTF_SetFontStyle(font, TTF_STYLE_BOLD);
    TTF_SizeText(font, "GAME OVER", &width_text, NULL);
    render_text(font, unit_to_pix_col_board(NUMBER_COLS + 5) / 2 - width_text / 2, offset_y, "GAME OVER");
    TTF_SetFontStyle(font, TTF_STYLE_NORMAL);
    CHECK_SNPRINFT(snprintf(text, BUFF_SIZE, "Score : %i", score));
    TTF_SizeText(font, text, &width_text, NULL);
    render_text(font, unit_to_pix_col_board(NUMBER_COLS + 5) / 2 - width_text / 2, offset_y + 110, text);
    CHECK_SNPRINFT(snprintf(text, BUFF_SIZE, "Lines : %i", line_completed));
    TTF_SizeText(font, text, &width_text, NULL);
    render_text(font, unit_to_pix_col_board(NUMBER_COLS + 5) / 2 - width_text / 2, offset_y + 160, text);
    if (level == 30)
        CHECK_SNPRINFT(snprintf(text, BUFF_SIZE, "Level : max"));
    else
        CHECK_SNPRINFT(snprintf(text, BUFF_SIZE, "Level : %i", level));
    TTF_SizeText(font, text, &width_text, NULL); // TODO check error
    render_text(font, unit_to_pix_col_board(NUMBER_COLS + 5) / 2 - width_text / 2, offset_y + 210, text);
    TTF_SetFontStyle(font_small, TTF_STYLE_ITALIC);
    TTF_SizeText(font_small, "Press R to play again", &width_text, NULL);
    render_text(font_small, unit_to_pix_col_board(NUMBER_COLS + 5) / 2 - width_text / 2, offset_y + 380, "Press R to play again");
    TTF_SizeText(font_small, "Press M to return to the menu", &width_text, NULL);
    render_text(font_small, unit_to_pix_col_board(NUMBER_COLS + 5) / 2 - width_text / 2, offset_y + 430, "Press M to return to the menu");
    TTF_SetFontStyle(font_small, TTF_STYLE_NORMAL);
    delete[] text;
    TTF_CloseFont(font);
    TTF_CloseFont(font_small);
}

status_t Game::play()
{
    // DEBUG create some tiles
    // ---------------------------------------
    // board[0][9]  = tile_I;
    // board[2][10] = tile_O;
    // board[3][11] = tile_T;
    // board[0][10] = tile_L;
    // board[1][10] = tile_J;
    // board[2][11] = tile_Z;
    // board[7][13] = tile_S;
    for (int i = 0; i < NUMBER_COLS - 1; i++)
    {
        board[i][16] = tile_J;
        board[i][17] = tile_J;
        board[i][18] = tile_J;
        board[i][19] = tile_J;
    }
    // board[0][18] = tile_empty;
    // board[0][17] = tile_empty;

    board[0][16] = tile_empty;
    board[0][19] = tile_empty;
    // ---------------------------------------

    Uint64 prev, now = SDL_GetPerformanceCounter(); // timers
    double delta_t;                                 // frame duration in ms
    double time = 0;
    double counter = 0;
    double counter_input_delay = 0;
    int fps_counter = 0;
    //bool is_key_pressed = false;
    status_t status = IN_GAME;
    is_game_over = false;
    while (status == IN_GAME)
    {
        if (!is_game_over)
        {
            // Background color (white)
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            SDL_RenderClear(renderer);

            // update timers and counters
            prev = now;
            now = SDL_GetPerformanceCounter();
            delta_t = (double)((now - prev) / (double)SDL_GetPerformanceFrequency());
            time += delta_t;
            counter += delta_t;
            counter_input_delay += delta_t;
            fps_counter++;

            // Key management
            while (status == IN_GAME && SDL_PollEvent(&event))
            {
                switch (event.type)
                {
                case SDL_QUIT:
                    status = QUIT;
                    break;
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym)
                    {
                    case SDLK_ESCAPE:
                        status = QUIT;
                        break;
                    case SDLK_r:
                        status = PLAY_1;
                        break;
                    case SDLK_m:
                        status = MENU;
                        break;
                    case SDLK_s:
                        if (Mix_PausedMusic() == 1)
                            Mix_ResumeMusic();
                        else
                            Mix_PauseMusic();
                        break;
                    }
                    break;
                default:
                    break;
                }
            }
            if (counter_input_delay > KEY_INPUT_COUNTER)
            {
                counter_input_delay = 0;
                const Uint8 *state = SDL_GetKeyboardState(NULL);
                keyboard(state);
            }

            // print fps
            if (counter > speed)
            {
                printf("fps : %f\n", fps_counter / counter);
                fps_counter = 0;
            }

            // move every 500 ms
            if (counter > speed)
            {
                counter = 0;
                if (!move_down())
                {
                    new_tetrimino(); // score uptdate todo ?
                    // test line full todo
                }
            }
            // display queue
            display_board();
            display_current_tetrimino();
            display_board_grid();
            // display board
            display_queue_background();
            display_queue_tetrimino();
            display_queue_grid();
            // display hold
            display_hold_background();
            display_hold_tetrimino();
            display_hold_grid();
            //display game info (score, level, line completed)
            display_game_info();
            // Render on the screen
            SDL_RenderPresent(renderer);
        }
        else
        {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            SDL_RenderClear(renderer);
            display_results();
            SDL_RenderPresent(renderer);
            while (status == IN_GAME && SDL_PollEvent(&event))
            {
                switch (event.type)
                {
                case SDL_QUIT:
                    status = QUIT;
                    break;
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym)
                    {
                    case SDLK_ESCAPE:
                        status = QUIT;
                        break;
                    case SDLK_r:
                        status = PLAY_1;
                        break;
                    case SDLK_m:
                        status = MENU;
                        break;
                    case SDLK_s:
                        if (Mix_PausedMusic() == 1)
                            Mix_ResumeMusic();
                        else
                            Mix_PauseMusic();
                        break;
                    }
                    break;
                default:
                    break;
                }
            }
        }
    }

    return status;
}

class Admin
{
private:
    status_t status;
    SDL_Renderer *renderer;
    SDL_Window *window;
    SDL_Event event;
    Mix_Music *music;

public:
    Admin();
    void start();
    void render_text(TTF_Font *font, int x, int y, const char *text);
    void menu();
    void help();
    void play_1();
    void play_2();
    void end();
};

Admin::Admin() : status(MENU)
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
    {
        fprintf(stderr, "error: SDL Init\n");
        exit(EXIT_FAILURE);
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1) //Initialisation de l'API Mixer
    {
        fprintf(stderr, "%s", Mix_GetError());
        exit(EXIT_FAILURE);
    }
    music = Mix_LoadMUS("./mp3/tetris_music.mp3");
    Mix_PlayMusic(music, -1);
    Mix_PauseMusic();

    TTF_Init();

    //srand (time(NULL)); TODO SEED IS FIXED FOR THE MOMENT
    srand(1);

    // Window
    window = SDL_CreateWindow("Tetris",
                              SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED,
                              unit_to_pix_col_board(NUMBER_COLS + 5),
                              unit_to_pix_row_board(NUMBER_ROWS),
                              SDL_WINDOW_SHOWN);

    // Renderer on the window
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

void Admin::start()
{
    while (status != QUIT)
    {
        switch (status)
        {
        case MENU:
            menu();
            break;

        case PLAY_1:
            play_1();
            break;

        case PLAY_2:
            play_2();
            break;

        case HELP:
            help();
            break;

        default:
            break;
        }
    }
}

void Admin::render_text(TTF_Font *font, int x, int y, const char *text)
{
    SDL_Surface *message =
        TTF_RenderText_Shaded(font, text, {0, 0, 0}, {255, 255, 255});
    //TTF_RenderText_Blended(font, text, {0, 0, 0}); // (slower)
    SDL_Texture *texture =
        SDL_CreateTextureFromSurface(renderer, message);
    int texW = 0;
    int texH = 0;
    SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
    SDL_Rect rect = {x, y, texW, texH};
    SDL_RenderCopy(renderer, texture, NULL, &rect);
    SDL_FreeSurface(message);
    SDL_DestroyTexture(texture);
}

void Admin::menu()
{

    TTF_Font *font = TTF_OpenFont("./src/font/OpenSans-Regular.ttf", 24);
    if (font == NULL)
    {
        fprintf(stderr, "error: font not found\n");
        exit(EXIT_FAILURE);
    }
    TTF_Font *font_small = TTF_OpenFont("./src/font/OpenSans-Regular.ttf", 19);
    if (font_small == NULL)
    {
        fprintf(stderr, "error: font not found\n");
        exit(EXIT_FAILURE);
    }
    int offset_y = 80;
    char *text = new char[BUFF_SIZE];
    int width_text;

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    TTF_SetFontStyle(font, TTF_STYLE_BOLD);
    TTF_SizeText(font, "TETRIS : THE GAME", &width_text, NULL);
    render_text(font, unit_to_pix_col_board(NUMBER_COLS + 5) / 2 - width_text / 2, offset_y, "TETRIS : THE GAME");
    TTF_SetFontStyle(font, TTF_STYLE_NORMAL);
    TTF_SetFontStyle(font_small, TTF_STYLE_ITALIC);
    TTF_SizeText(font_small, "Press 1 to play in solo", &width_text, NULL);
    render_text(font_small, unit_to_pix_col_board(NUMBER_COLS + 5) / 2 - width_text / 2, offset_y + 180, "Press 1 to play in solo");
    TTF_SizeText(font_small, "Press 2 to play in multiplayer", &width_text, NULL);
    render_text(font_small, unit_to_pix_col_board(NUMBER_COLS + 5) / 2 - width_text / 2, offset_y + 230, "Press 2 to play in multiplayer");
    TTF_SizeText(font_small, "Press H to have help", &width_text, NULL);
    render_text(font_small, unit_to_pix_col_board(NUMBER_COLS + 5) / 2 - width_text / 2, offset_y + 280, "Press H to have help");
    TTF_SizeText(font_small, "Press Escape to quit", &width_text, NULL);
    render_text(font_small, unit_to_pix_col_board(NUMBER_COLS + 5) / 2 - width_text / 2, offset_y + 330, "Press Escape to quit");
    TTF_SetFontStyle(font_small, TTF_STYLE_NORMAL);
    SDL_RenderPresent(renderer);
    delete[] text;
    TTF_CloseFont(font);
    TTF_CloseFont(font_small);

    while (status == MENU && SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            status = QUIT;
            break;
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym)
            {
            case SDLK_ESCAPE:
                status = QUIT;
                break;

            case SDLK_1:
                status = PLAY_1;
                break;

            case SDLK_2:
                status = PLAY_2;
                break;

            case SDLK_h:
                status = HELP;
                break;
            case SDLK_s:
                if (Mix_PausedMusic() == 1)
                    Mix_ResumeMusic();
                else
                    Mix_PauseMusic();
                break;
            }
            break;
        default:
            break;
        }
    }
}

void Admin::help()
{
    TTF_Font *font = TTF_OpenFont("./src/font/OpenSans-Regular.ttf", 24);
    if (font == NULL)
    {
        fprintf(stderr, "error: font not found\n");
        exit(EXIT_FAILURE);
    }
    TTF_Font *font_small = TTF_OpenFont("./src/font/OpenSans-Regular.ttf", 19);
    if (font_small == NULL)
    {
        fprintf(stderr, "error: font not found\n");
        exit(EXIT_FAILURE);
    }
    int offset_x = 20;
    int offset_y = 80;
    char *text = new char[BUFF_SIZE];
    int width_text;

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    TTF_SetFontStyle(font, TTF_STYLE_BOLD);
    TTF_SizeText(font, "HELP : THE CONTROLS", &width_text, NULL);
    render_text(font, unit_to_pix_col_board(NUMBER_COLS + 5) / 2 - width_text / 2, offset_y, "HELP : THE CONTROLS");
    TTF_SetFontStyle(font, TTF_STYLE_NORMAL);
    TTF_SetFontStyle(font_small, TTF_STYLE_ITALIC);
    render_text(font_small, offset_x, offset_y + 80, "Left arrow : move left");
    render_text(font_small, offset_x, offset_y + 115, "Right arrow : move right");
    render_text(font_small, offset_x, offset_y + 150, "Up arrow : rotate clockwise");
    render_text(font_small, offset_x, offset_y + 185, "Ctrl : rotate counter-clockwise");
    render_text(font_small, offset_x, offset_y + 220, "Bottom arrow : soft drop");
    render_text(font_small, offset_x, offset_y + 255, "Spacebar : hard drop");
    render_text(font_small, offset_x, offset_y + 290, "C : hold piece");
    render_text(font_small, offset_x, offset_y + 325, "S : to play/stop music");
    TTF_SizeText(font_small, "Press M to return to the menu", &width_text, NULL);
    render_text(font_small, unit_to_pix_col_board(NUMBER_COLS + 5) / 2 - width_text / 2, offset_y + 400, "Press M to return to the menu");
    TTF_SizeText(font_small, "Press Escape to quit", &width_text, NULL);
    render_text(font_small, unit_to_pix_col_board(NUMBER_COLS + 5) / 2 - width_text / 2, offset_y + 450, "Press Escape to quit");
    TTF_SetFontStyle(font_small, TTF_STYLE_NORMAL);
    SDL_RenderPresent(renderer);
    delete[] text;
    TTF_CloseFont(font);
    TTF_CloseFont(font_small);

    while (status == HELP && SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            status = QUIT;
            break;
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym)
            {
            case SDLK_ESCAPE:
                status = QUIT;
                break;

            case SDLK_m:
                status = MENU;
                break;
            case SDLK_s:
                if (Mix_PausedMusic() == 1)
                    Mix_ResumeMusic();
                else
                    Mix_PauseMusic();
                break;
            }
            break;
        default:
            break;
        }
    }
}

void Admin::play_1()
{
    Game game = Game(window, renderer);
    status = game.play();
}

void Admin::play_2()
{
    Game game = Game(window, renderer);
    status = game.play();
}

void Admin::end()
{
    Mix_FreeMusic(music);
    Mix_CloseAudio();
    TTF_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

// TODO animation ? ??? piece falling or row completed
int main(int argc, char **argv)
{
    Admin admin;
    admin.start();
    admin.end();

    return EXIT_SUCCESS;
}
