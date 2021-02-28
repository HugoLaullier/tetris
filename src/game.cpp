#include "headers/game.hpp"


Game::Game(SDL_Window *window, SDL_Renderer *renderer,
           TTF_Font *font, TTF_Font *font_small,
           int window_w, int window_h, status_t status, double difficulty,
           Player *player) : window(window),
                             renderer(renderer),
                             font(font),
                             font_small(font_small),
                             window_w(window_w),
                             window_h(window_h),
                             self_status(status),
                             difficulty(difficulty),
                             player_1(player),
                             player_2(nullptr) {}

Game::Game(SDL_Window *window, SDL_Renderer *renderer,
           TTF_Font *font, TTF_Font *font_small,
           int window_w, int window_h, status_t status, double difficulty,
           Player *p1, Player *p2) : window(window),
                                     renderer(renderer),
                                     font(font),
                                     font_small(font_small),
                                     window_w(window_w),
                                     window_h(window_h),
                                     self_status(status),
                                     difficulty(difficulty),
                                     player_1(p1),
                                     player_2(p2) {}

void Game::display_fps(double fps) const
{
    char *text = new char[BUFF_SIZE];
    CHECK_SNPRINFT(snprintf(text, BUFF_SIZE, "fps : %i", (int)fps));
    render_text(renderer, font_small, MARGIN_X, window_h - 20 - MARGIN_Y, text);
    delete[] text;
}

void Game::display_results(int winner) const
{
    int offset_y = 80;
    char *text = new char[BUFF_SIZE];
    int width_text;

    if (winner == 0)
    {
        TTF_SetFontStyle(font, TTF_STYLE_BOLD);
        TTF_SizeText(font, "GAME OVER", &width_text, NULL);
        render_text(renderer, font,
                    unit_to_pix_col_board(NUMBER_COLS + 5) / 2 - width_text / 2,
                    offset_y, "GAME OVER");
        TTF_SetFontStyle(font, TTF_STYLE_NORMAL);
        CHECK_SNPRINFT(snprintf(text, BUFF_SIZE, "Score : %i",
                                player_1->get_score()));
        TTF_SizeText(font, text, &width_text, NULL);
        render_text(renderer, font,
                    unit_to_pix_col_board(NUMBER_COLS + 5) / 2 - width_text / 2,
                    offset_y + 110, text);
        CHECK_SNPRINFT(snprintf(text, BUFF_SIZE, "Lines : %i",
                                player_1->get_line_completed()));
        TTF_SizeText(font, text, &width_text, NULL);
        render_text(renderer, font,
                    unit_to_pix_col_board(NUMBER_COLS + 5) / 2 - width_text / 2,
                    offset_y + 160, text);
        if (player_1->get_level() == LEVEL_MAX)
            CHECK_SNPRINFT(snprintf(text, BUFF_SIZE, "Level : max"));
        else
            CHECK_SNPRINFT(snprintf(text, BUFF_SIZE, "Level : %i",
                                    player_1->get_level()));
        TTF_SizeText(font, text, &width_text, NULL);
        render_text(renderer, font,
                    unit_to_pix_col_board(NUMBER_COLS + 5) / 2 - width_text / 2,
                    offset_y + 210, text);
    }
    else
    {
        if (winner == 1)
        {
            TTF_SetFontStyle(font, TTF_STYLE_BOLD);
            TTF_SizeText(font, "YOU WIN !", &width_text, NULL);
            render_text(renderer, font,
                        unit_to_pix_col_board(NUMBER_COLS + 5) / 2 
                        - width_text / 2,
                        offset_y, "YOU WIN !");
            TTF_SetFontStyle(font, TTF_STYLE_NORMAL);
        }
        else
        {
            TTF_SetFontStyle(font, TTF_STYLE_BOLD);
            TTF_SizeText(font, "YOU LOSE !", &width_text, NULL);
            render_text(renderer, font,
                        unit_to_pix_col_board(NUMBER_COLS + 5) / 2 
                        - width_text / 2,
                        offset_y, "YOU LOSE !");
            TTF_SetFontStyle(font, TTF_STYLE_NORMAL);
        }
        // your results
        TTF_SetFontStyle(font, TTF_STYLE_BOLD);
        TTF_SizeText(font, "You", &width_text, NULL);
        render_text(renderer, font,
                    unit_to_pix_col_board(NUMBER_COLS + 5) / 4 - width_text / 4,
                    offset_y + 110, "You");
        TTF_SetFontStyle(font, TTF_STYLE_NORMAL);
        CHECK_SNPRINFT(snprintf(text, BUFF_SIZE, "Score : %i",
                                player_1->get_score()));
        TTF_SizeText(font, text, &width_text, NULL);
        render_text(renderer, font,
                    unit_to_pix_col_board(NUMBER_COLS + 5) / 4 - width_text / 4,
                    offset_y + 160, text);
        CHECK_SNPRINFT(snprintf(text, BUFF_SIZE, "Lines : %i",
                                player_1->get_line_completed()));
        TTF_SizeText(font, text, &width_text, NULL);
        render_text(renderer, font,
                    unit_to_pix_col_board(NUMBER_COLS + 5) / 4 - width_text / 4,
                    offset_y + 210, text);
        if (player_1->get_level() == LEVEL_MAX)
            CHECK_SNPRINFT(snprintf(text, BUFF_SIZE, "Level : max"));
        else
            CHECK_SNPRINFT(snprintf(text, BUFF_SIZE, "Level : %i",
                                    player_1->get_level()));
        TTF_SizeText(font, text, &width_text, NULL);
        render_text(renderer, font,
                    unit_to_pix_col_board(NUMBER_COLS + 5) / 4 - width_text / 4,
                    offset_y + 260, text);

        // enemy results
        TTF_SetFontStyle(font, TTF_STYLE_BOLD);
        TTF_SizeText(font, "Ennemy", &width_text, NULL);
        render_text(renderer, font,
                    3 * unit_to_pix_col_board(NUMBER_COLS + 5) / 4 
                    - 3 * width_text / 4,
                    offset_y + 110, "Ennemy");
        TTF_SetFontStyle(font, TTF_STYLE_NORMAL);
        CHECK_SNPRINFT(snprintf(text, BUFF_SIZE, "Score : %i",
                                player_2->get_score()));
        TTF_SizeText(font, text, &width_text, NULL);
        render_text(renderer, font,
                    3 * unit_to_pix_col_board(NUMBER_COLS + 5) / 4 
                    - 3 * width_text / 4,
                    offset_y + 160, text);
        CHECK_SNPRINFT(snprintf(text, BUFF_SIZE, "Lines : %i",
                                player_2->get_line_completed()));
        TTF_SizeText(font, text, &width_text, NULL);
        render_text(renderer, font,
                    3 * unit_to_pix_col_board(NUMBER_COLS + 5) / 4 
                    - 3 * width_text / 4,
                    offset_y + 210, text);
        if (player_2->get_level() == LEVEL_MAX)
            CHECK_SNPRINFT(snprintf(text, BUFF_SIZE, "Level : max"));
        else
            CHECK_SNPRINFT(snprintf(text, BUFF_SIZE, "Level : %i",
                                    player_2->get_level()));
        TTF_SizeText(font, text, &width_text, NULL);
        render_text(renderer, font,
                    3 * unit_to_pix_col_board(NUMBER_COLS + 5) / 4 
                    - 3 * width_text / 4,
                    offset_y + 260, text);
    }
    TTF_SetFontStyle(font_small, TTF_STYLE_NORMAL);
    // TTF_SetFontStyle(font_small, TTF_STYLE_ITALIC);
    TTF_SizeText(font_small, "Press R - play again", &width_text, NULL);
    render_text(renderer, font_small,
                unit_to_pix_col_board(NUMBER_COLS + 5) / 2 - width_text / 2,
                offset_y + 380, "Press R - play again");
    TTF_SizeText(font_small, "Press M - return to menu", &width_text,NULL);
    render_text(renderer, font_small,
                unit_to_pix_col_board(NUMBER_COLS + 5) / 2 - width_text / 2,
                offset_y + 430, "Press M - return to menu");
    TTF_SetFontStyle(font_small, TTF_STYLE_NORMAL);
    delete[] text;
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
        if (self_status == PLAY_2)
        {
            SDL_RenderDrawLine(renderer,
                               window_w + unit_to_pix_col_board(0),
                               unit_to_pix_row_board(row),
                               window_w + unit_to_pix_col_board(NUMBER_COLS),
                               unit_to_pix_row_board(row));
        }
    }

    for (int col = 0; col < NUMBER_COLS + 1; col++)
    {
        SDL_RenderDrawLine(renderer,
                           unit_to_pix_col_board(col),
                           unit_to_pix_row_board(0),
                           unit_to_pix_col_board(col),
                           unit_to_pix_row_board(NUMBER_ROWS));
        if (self_status == PLAY_2)
        {
            SDL_RenderDrawLine(renderer,
                               window_w + unit_to_pix_col_board(col),
                               unit_to_pix_row_board(0),
                               window_w + unit_to_pix_col_board(col),
                               unit_to_pix_row_board(NUMBER_ROWS));
        }
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    if (self_status == PLAY_2)
    {
        SDL_RenderDrawLine(renderer, window_w, unit_to_pix_row_board(0), 
            window_w, unit_to_pix_row_board(NUMBER_ROWS));
    }
}

void Game::display_hold_grid() const
{
    SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);

    for (int row = 0; row <= 6; row++)
    {
        SDL_RenderDrawLine(renderer,
                           unit_to_pix_col_hold(0),
                           unit_to_pix_row_hold(row),
                           unit_to_pix_col_hold(5),
                           unit_to_pix_row_hold(row));
        if (self_status == PLAY_2)
        {
            SDL_RenderDrawLine(renderer,
                               window_w + unit_to_pix_col_hold(0),
                               unit_to_pix_row_hold(row),
                               window_w + unit_to_pix_col_hold(5),
                               unit_to_pix_row_hold(row));
        }
    }

    for (int col = 0; col <= 5; col++)
    {
        SDL_RenderDrawLine(renderer,
                           unit_to_pix_col_hold(col),
                           unit_to_pix_row_hold(0),
                           unit_to_pix_col_hold(col),
                           unit_to_pix_row_hold(6));
        if (self_status == PLAY_2)
        {
            SDL_RenderDrawLine(renderer,
                               window_w + unit_to_pix_col_hold(col),
                               unit_to_pix_row_hold(0),
                               window_w + unit_to_pix_col_hold(col),
                               unit_to_pix_row_hold(6));
        }
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
                unit_to_pix_row_hold(row),
                TILE_SIZE_PX,
                TILE_SIZE_PX};
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderFillRect(renderer, &r);
            if (self_status == PLAY_2)
            {
                r = {window_w + unit_to_pix_col_hold(col),
                     unit_to_pix_row_hold(row),
                     TILE_SIZE_PX,
                     TILE_SIZE_PX};
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                SDL_RenderFillRect(renderer, &r);
            }
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
                           unit_to_pix_row_queue(row),
                           unit_to_pix_col_queue(4),
                           unit_to_pix_row_queue(row));
        if (self_status == PLAY_2)
        {
            SDL_RenderDrawLine(renderer,
                               window_w + unit_to_pix_col_queue(0),
                               unit_to_pix_row_queue(row),
                               window_w + unit_to_pix_col_queue(4),
                               unit_to_pix_row_queue(row));
        }
    }

    for (int col = 0; col <= 4; col++)
    {
        SDL_RenderDrawLine(renderer,
                           unit_to_pix_col_queue(col),
                           unit_to_pix_row_queue(0),
                           unit_to_pix_col_queue(col),
                           unit_to_pix_row_queue(5 * QUEUE_SIZE + 1));
        if (self_status == PLAY_2)
        {
            SDL_RenderDrawLine(renderer,
                               window_w + unit_to_pix_col_queue(col),
                               unit_to_pix_row_queue(0),
                               window_w + unit_to_pix_col_queue(col),
                               unit_to_pix_row_queue(5 * QUEUE_SIZE + 1));
        }
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
                unit_to_pix_row_queue(row),
                TILE_SIZE_PX,
                TILE_SIZE_PX};
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderFillRect(renderer, &r);
            if (self_status == PLAY_2)
            {
                r = {window_w + unit_to_pix_col_queue(col),
                     unit_to_pix_row_queue(row),
                     TILE_SIZE_PX,
                     TILE_SIZE_PX};
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                SDL_RenderFillRect(renderer, &r);
            }
        }
    }
}

void Game::game_loop(status_t *status, double *delta_t, double *counter_p1,
                     double *counter_p2, double *counter_input_delay_p1,
                     double *counter_input_delay_p2)
{
    // Key management
    while (*status == IN_GAME && SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            *status = QUIT;
            return;
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym)
            {
            case SDLK_ESCAPE:
                *status = QUIT;
                return;
            case SDLK_r:
                *status = self_status;
                return;
            case SDLK_m:
                *status = MENU;
                return;
            case SDLK_s:
                Mix_PausedMusic() ? Mix_ResumeMusic() : Mix_PauseMusic();
                break;
            }
            break;
        default:
            break;
        }
    }

    //send lines
    if (self_status == PLAY_2 && player_2 != nullptr)
    {
        if (player_1->get_send_lines() != 0)
        {
            player_2->receive_lines(player_1->get_send_lines());
            player_1->reset_send_lines();
        }
        if (player_2->get_send_lines() != 0)
        {
            player_1->receive_lines(player_2->get_send_lines());
            player_2->reset_send_lines();
        }
    }

    // PLAYER 1
    player_1->handle_player_input(difficulty, counter_p1,
                                  counter_input_delay_p1);

    // PLAYER 2
    if (self_status == PLAY_2 && player_2 != nullptr)
    {
        player_2->handle_player_input(difficulty, counter_p2,
                                      counter_input_delay_p2);
    }

    // Background color (white)
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    
    // display queue
    player_1->display_board();
    player_1->display_current_tetrimino();
    if (self_status == PLAY_2 && player_2 != nullptr)
    {
        player_2->display_board();
        player_2->display_current_tetrimino();
    }

    display_board_grid();

    // display projection
    player_1->display_projection();
    if (self_status == PLAY_2 && player_2 != nullptr)
    {
        player_2->display_projection();
    }
    // display board
    display_queue_background();
    player_1->display_queue_tetrimino();
    if (self_status == PLAY_2 && player_2 != nullptr)
        player_2->display_queue_tetrimino();
    display_queue_grid();
    // display hold
    display_hold_background();
    player_1->display_hold_tetrimino();
    if (self_status == PLAY_2 && player_2 != nullptr)
        player_2->display_hold_tetrimino();
    display_hold_grid();
    //display game info (score, level, line completed)
    player_1->display_player_info(font);
    if (self_status == PLAY_2 && player_2 != nullptr)
        player_2->display_player_info(font);
    // display fps
    if (COMPUTE_FPS && difficulty != DIFFICULTY_IMPOSSIBLE)
        display_fps(1.0f / *delta_t);
    // Render on the screen
    SDL_RenderPresent(renderer);
}

void Game::score_screen_loop(status_t *status)
{
    while (*status == IN_GAME && SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            *status = QUIT;
            return;
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym)
            {
            case SDLK_ESCAPE:
                *status = QUIT;
                return;
            case SDLK_r:
                *status = self_status;
                return;
            case SDLK_m:
                *status = MENU;
                return;
            case SDLK_s:
                Mix_PausedMusic() ? Mix_ResumeMusic() : Mix_PauseMusic();
                break;
            }
            break;
        default:
            break;
        }
    }
}

status_t Game::play()
{
    Uint64 prev, now = SDL_GetPerformanceCounter(); // timers
    double delta_t;                                 // frame duration in ms
    double counter_p1 = 0;
    double counter_p2 = 0;
    double counter_input_delay_p1 = 0;
    double counter_input_delay_p2 = 0;

    //bool is_key_pressed = false;
    status_t status = IN_GAME;
    int winner = -1; // 0 no winner (if solo), 1 player 1 is winner, 2 player 2
    while (status == IN_GAME)
    {
        if (winner == -1)
        {
            // update timers and counters
            prev = now;
            now = SDL_GetPerformanceCounter();
            delta_t = (double)((now - prev) /
                               (double)SDL_GetPerformanceFrequency());
            counter_p1 += delta_t;
            if (self_status == PLAY_2 && player_2 != nullptr)
                counter_p2 += delta_t;
            counter_input_delay_p1 += delta_t;
            counter_input_delay_p2 += delta_t;
            // call game loop

            game_loop(&status, &delta_t, &counter_p1, &counter_p2,
                      &counter_input_delay_p1, &counter_input_delay_p2);

            // Cap to 60 FPS
            if (difficulty != DIFFICULTY_IMPOSSIBLE)
            {
                int delay_ms = (int)floor(16.666f - delta_t);
                if (delay_ms < 100 && delay_ms > 0)
                    SDL_Delay(delay_ms);
            }
        }
        else
        {
            SDL_SetWindowSize(window, window_w, window_h);
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            SDL_RenderClear(renderer);
            display_results(winner);
            SDL_RenderPresent(renderer);
            break;
        }
        // search a winner or a game over
        if (self_status == PLAY_2 && player_2 != nullptr)
        {
            if (player_2->get_is_game_over())
                winner = 1;
            if (player_1->get_is_game_over())
                winner = 2;
            if (player_1->get_level() == LEVEL_MAX)
                winner = 1;
            if (player_2->get_level() == LEVEL_MAX)
                winner = 2;
        }
        else
        {
            if (player_1->get_is_game_over())
                winner = 0;
        }
    }
    while (status == IN_GAME)
    {
        // update timers and counters
        prev = now;
        now = SDL_GetPerformanceCounter();
        delta_t = (double)((now - prev) /
                           (double)SDL_GetPerformanceFrequency());
        score_screen_loop(&status);
        // Cap to 60 FPS
        int delay_ms = (int)floor(16.666f - delta_t);
        if (delay_ms < 100 && delay_ms > 0)
            SDL_Delay(delay_ms);
    }
    SDL_SetWindowSize(window, window_w, window_h);
    return status;
}