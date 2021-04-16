#include "../include/player.hpp"

/*-------------------------------------------------------------------*/

Human_player::Human_player(SDL_Renderer *renderer_,
                           int player_number_,
                           int offset_x_) :
    Player(renderer_, player_number_, offset_x_) {}

void Human_player::handle_player_input(double difficulty,
                                       double *counter,
                                       double *counter_input_delay)
{
    (void)difficulty;
    // delay between inputs
    if (*counter_input_delay > KEY_INPUT_COUNTER)
    {
        *counter_input_delay = 0;
        const Uint8 *state = SDL_GetKeyboardState(NULL);
        keyboard(state);
    }
    // move down tetrimino depending on the current speed
    if (*counter > get_speed())
    {
        *counter = 0;
        if (!move_down())
            new_tetrimino();
    }
}

void Human_player::display_projection()
{
    bool can_move_down = true;
    int pos[4][2];
    current_tetrimino->get_position(&pos);
    while (can_move_down)
    {
        for (int i = 0; i < 4; i++)
        {
            if (pos[i][1] + 1 >= 0 &&
                (board[pos[i][0]][pos[i][1] + 1] != tile_empty ||
                 pos[i][1] + 1 >= NUMBER_ROWS))
            {
                can_move_down = false;
            }
        }
        if (can_move_down)
        {
            for (int i = 0; i < 4; i++)
            {
                pos[i][1] += 1;
            }
        }
    }
    int pos_ref[4][2];
    current_tetrimino->get_position(&pos_ref);
    for (int i = 0; i < 4; i++)
    {
        if (pos[i][1] >= 0)
        {
            std::vector<int> color = current_tetrimino->get_color();
            SDL_SetRenderDrawColor(
                renderer, color[0], color[1], color[2], 255);
            for (int j = 0; j < 4; j++)
                if (pos[i][0] == pos_ref[j][0] && pos[i][1] == pos_ref[j][1])
                {
                    SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
                    break;
                }
            
            SDL_RenderDrawLine(renderer, 
                offset_x + unit_to_pix_col_board(pos[i][0]),
                unit_to_pix_row_board(pos[i][1]), 
                offset_x + unit_to_pix_col_board(pos[i][0]) + TILE_SIZE_PX * 2,
                unit_to_pix_row_board(pos[i][1]));
            SDL_RenderDrawLine(renderer, 
                offset_x + unit_to_pix_col_board(pos[i][0]),
                unit_to_pix_row_board(pos[i][1]),
                offset_x + unit_to_pix_col_board(pos[i][0]),
                unit_to_pix_row_board(pos[i][1]) + TILE_SIZE_PX * 2);
            SDL_RenderDrawLine(renderer,
                offset_x + unit_to_pix_col_board(pos[i][0]) + TILE_SIZE_PX * 2,
                unit_to_pix_row_board(pos[i][1]),
                offset_x + unit_to_pix_col_board(pos[i][0]) + TILE_SIZE_PX * 2,
                unit_to_pix_row_board(pos[i][1]) + TILE_SIZE_PX * 2);
            SDL_RenderDrawLine(renderer,
                offset_x + unit_to_pix_col_board(pos[i][0]),
                unit_to_pix_row_board(pos[i][1]) + TILE_SIZE_PX * 2,
                offset_x + unit_to_pix_col_board(pos[i][0]) + TILE_SIZE_PX * 2,
                unit_to_pix_row_board(pos[i][1]) + TILE_SIZE_PX * 2);
        }
    }
}

void Human_player::display_player_info(TTF_Font *font)
{
    int offset_y = 300;
    char *text = new char[BUFF_SIZE];
    render_text(renderer, font, offset_x + MARGIN_X, offset_y, "Score :");
    CHECK_SNPRINFT(snprintf(text, BUFF_SIZE, "%i", score));
    render_text(renderer, font, offset_x + MARGIN_X, offset_y + 40, text);
    render_text(renderer, font, offset_x + MARGIN_X, offset_y + 80, "Lines :");
    CHECK_SNPRINFT(snprintf(text, BUFF_SIZE, "%i", line_completed));
    render_text(renderer, font, offset_x + MARGIN_X, offset_y + 120, text);
    render_text(renderer, font, offset_x + MARGIN_X, offset_y + 160, "Level :");
    if (level == LEVEL_MAX)
        CHECK_SNPRINFT(snprintf(text, BUFF_SIZE, "max"));
    else
        CHECK_SNPRINFT(snprintf(text, BUFF_SIZE, "%i", level));
    render_text(renderer, font, offset_x + MARGIN_X, offset_y + 200, text);
    render_text(renderer, font, offset_x + MARGIN_X, 150, "Press C");
    render_text(renderer, font, offset_x + MARGIN_X, 180, "to hold");
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderDrawLine(renderer, offset_x + MARGIN_X, offset_y + 255,
        offset_x + unit_to_pix_col_board(0) - MARGIN_X, offset_y + 255);
    int width_text;
    TTF_SizeText(font, "You", &width_text, NULL);
    render_text(renderer, font, 
        offset_x + unit_to_pix_col_board(0) / 2 - width_text / 2,
        offset_y + 270, "You");
    delete[] text;
}

/*-------------------------------------------------------------------*/

AI_player::AI_player(SDL_Renderer *renderer_,
                     int player_number_,
                     int offset_x_) : 
    Player(renderer_, player_number_, offset_x_) {}

void AI_player::handle_player_input(double difficulty,
                                    double *counter,
                                    double *counter_input_delay)
{
    // if it's a new tetrimino then the AI compute the best moves
    // and create a list of input that place the tetrimino in the
    // correct spot
    if (get_is_new_tetrimino())
    {
        std::vector<input_t> new_input_queue;
        if (get_is_first_move())
        {
            set_is_first_move(false);
            new_input_queue = {INPUT_C};
        }
        else
        {
            new_input_queue = compute_best_move();
        }
        set_input_queue(new_input_queue);
        set_is_new_tetrimino(false);
    }
    // computed inputs are played and respect the minimum delay between
    // inputs (AI can't play too fast) -> adjusted with difficulty
    if (*counter_input_delay > KEY_INPUT_COUNTER * difficulty &&
        !get_input_queue().empty())
    {
        *counter_input_delay = 0;
        input_t input = pop_input_queue();
        Uint8 *state = simulate_keyboard_input(input);
        keyboard(state);
        delete[] state;
    }
    // move down tetrimino depending on the current speed
    if (*counter > get_speed())
    {
        *counter = 0;
        if (!move_down())
            new_tetrimino();
    }
}

void AI_player::display_projection() {}

void AI_player::display_player_info(TTF_Font *font)
{
    int offset_y = 300;
    char *text = new char[BUFF_SIZE];
    render_text(renderer, font, offset_x + MARGIN_X, offset_y, "Score :");
    CHECK_SNPRINFT(snprintf(text, BUFF_SIZE, "%i", score));
    render_text(renderer, font, offset_x + MARGIN_X, offset_y + 40, text);
    render_text(renderer, font, offset_x + MARGIN_X, offset_y + 80, "Lines :");
    CHECK_SNPRINFT(snprintf(text, BUFF_SIZE, "%i", line_completed));
    render_text(renderer, font, offset_x + MARGIN_X, offset_y + 120, text);
    render_text(renderer, font, offset_x + MARGIN_X, offset_y + 160, "Level :");
    if (level == LEVEL_MAX)
        CHECK_SNPRINFT(snprintf(text, BUFF_SIZE, "max"));
    else
        CHECK_SNPRINFT(snprintf(text, BUFF_SIZE, "%i", level));
    render_text(renderer, font, offset_x + MARGIN_X, offset_y + 200, text);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderDrawLine(renderer, offset_x + MARGIN_X, offset_y + 255, 
        offset_x + unit_to_pix_col_board(0) - MARGIN_X, offset_y + 255);
    int width_text;
    TTF_SizeText(font, "AI", &width_text, NULL);
    render_text(renderer, font, offset_x + unit_to_pix_col_board(0) / 2 
        - width_text / 2, offset_y + 270, "AI");
    delete[] text;
}

Player::Player(SDL_Renderer *renderer_, int player_number_, int offset_x_) : 
    renderer(renderer_),
    player_number(player_number_),
    offset_x(offset_x_),
    current_tetrimino(nullptr),
    speed(DEFAULT_GAME_SPEED),
    line_completed(0),
    level(1),
    score(0),
    hold(nullptr),
    send_lines(0)
{
    for (int i = 0; i < NUMBER_COLS; i++)
        for (int j = 0; j < NUMBER_ROWS; j++)
            board[i][j] = tile_empty;

    for (int i = 0; i < NB_TETRIMONO; i++)
    {
        int r = rand() % 7;
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

Player::~Player()
{
    for (int i = 0; i < NB_TETRIMONO; i++)
    {
        queue_tetrimino.pop_back();
    }
    if (hold != nullptr)
        delete hold;
}

int Player::get_player_number() const
{
    return player_number;
}

int Player::get_line_completed() const
{
    return line_completed;
}

int Player::get_level() const
{
    return level;
}

int Player::get_score() const
{
    return score;
}

double Player::get_speed() const
{
    return speed;
}

bool Player::get_is_game_over() const
{
    return is_game_over;
}

bool Player::get_is_new_tetrimino() const
{
    return is_new_tetrimino;
}

bool AI_player::get_is_first_move() const
{
    return is_first_move;
}

void AI_player::set_is_first_move(bool value)
{
    is_first_move = value;
}

std::vector<input_t> AI_player::get_input_queue() const
{
    return input_queue;
}

void Player::set_is_new_tetrimino(bool value)
{
    is_new_tetrimino = value;
}

void AI_player::set_input_queue(std::vector<input_t> new_input_queue)
{
    input_queue = new_input_queue;
}

input_t AI_player::pop_input_queue()
{
    input_t input = input_queue[input_queue.size() - 1];
    input_queue.pop_back();
    return input;
}

void Player::display_board() const
{
    for (int row = 0; row < NUMBER_ROWS; row++)
    {
        for (int col = 0; col < NUMBER_COLS; col++)
        {
            SDL_Rect r = {
                offset_x + unit_to_pix_col_board(col),
                unit_to_pix_row_board(row),
                TILE_SIZE_PX * 2,
                TILE_SIZE_PX * 2};
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

void Player::display_current_tetrimino() const
{
    int pos[4][2];
    current_tetrimino->get_position(&pos);
    for (int i = 0; i < 4; i++)
    {
        if (pos[i][1] >= 0)
        {
            SDL_Rect r = {
                offset_x + unit_to_pix_col_board(pos[i][0]),
                unit_to_pix_row_board(pos[i][1]),
                TILE_SIZE_PX * 2,
                TILE_SIZE_PX * 2};
            std::vector<int> color = current_tetrimino->get_color();
            SDL_SetRenderDrawColor(
                renderer, color[0], color[1], color[2], 255);
            SDL_RenderFillRect(renderer, &r);
        }
    }
}

void Player::display_queue_tetrimino() const
{
    for (int i = 1; i < NB_TETRIMONO; i++)
    {
        int pos[4][2];
        queue_tetrimino[i]->get_preview_position(&pos);
        for (int j = 0; j < 4; j++)
        {
            SDL_Rect r = {
                offset_x + unit_to_pix_col_queue(pos[j][0]),
                unit_to_pix_row_queue(pos[j][1] + 1 + 5 * (i - 1)),
                TILE_SIZE_PX,
                TILE_SIZE_PX};
            std::vector<int> color = queue_tetrimino[i]->get_color();
            SDL_SetRenderDrawColor(
                renderer, color[0], color[1], color[2], 255);
            SDL_RenderFillRect(renderer, &r);
        }
    }
}

void Player::display_hold_tetrimino() const
{
    if (hold == nullptr)
        return;

    int pos[4][2];
    hold->get_preview_position(&pos);
    for (int i = 0; i < 4; i++)
    {
        SDL_Rect r = {
            offset_x + unit_to_pix_col_hold(pos[i][0] + 1),
            unit_to_pix_row_hold(pos[i][1] + 1),
            TILE_SIZE_PX,
            TILE_SIZE_PX};
        std::vector<int> color = hold->get_color();
        SDL_SetRenderDrawColor(
            renderer, color[0], color[1], color[2], 255);
        SDL_RenderFillRect(renderer, &r);
    }
}

void Player::shift_down_board(int k)
{
    for (int i = k - 1; i >= 0; i--)
        for (int j = 0; j < NUMBER_COLS; j++)
            board[j][i + 1] = board[j][i];
}

void Player::new_tetrimino()
{
    std::rotate(queue_tetrimino.begin(),
                queue_tetrimino.begin() + 1,
                queue_tetrimino.end());
    current_tetrimino = queue_tetrimino[0];
    queue_tetrimino.pop_back();
    int r = rand() % 7;
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
    line_completed += line_full.size();
    if (line_completed >= level * 10 && level < LEVEL_MAX)
    {
        level++;
        static double a =
            ((DEFAULT_GAME_SPEED / 2) - DEFAULT_GAME_SPEED) / LEVEL_MAX;
        speed = a * level + DEFAULT_GAME_SPEED; // increase speed linearly
    }
    if (line_full.size() == 2)
    {
        send_lines = 1;
    }
    else if (line_full.size() == 3)
    {
        send_lines = 2;
    }
    else if (line_full.size() == 4)
    {
        send_lines = 4;
    }
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
    is_new_tetrimino = true;
}

void Player::new_hold()
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
            //delete current_tetrimino;
            current_tetrimino = hold;
            hold = temp_copy;
            hold->reset_pos();
        }
        is_hold_available = false;
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
}

bool Player::move_down()
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

bool Player::move_left()
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
            if (!is_in_board(pos[i][0] - 1, pos[i][1]) ||
                board[pos[i][0] - 1][pos[i][1]] != tile_empty ||
                pos[i][0] - 1 < 0)
            {
                return false; // movement is blocked
            }
        }
    }
    current_tetrimino->move_left();
    return true;
}

bool Player::move_right()
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
            if (!is_in_board(pos[i][0] + 1, pos[i][1]) ||
                board[pos[i][0] + 1][pos[i][1]] != tile_empty ||
                pos[i][0] + 1 >= NUMBER_COLS)
            {
                return false; // movement is blocked
            }
        }
    }
    current_tetrimino->move_right();
    return true;
}

void Player::fast_down()
{
    while (move_down())
        ;
    new_tetrimino();
}

bool Player::rotate(rotate_dir_t dir)
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
    delete test_tetrimino;
    return true;
}

void Player::keyboard(const Uint8 *keys)
{
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

int Player::get_send_lines()
{
    return send_lines;
}

void Player::reset_send_lines()
{
    send_lines = 0;
}

void Player::receive_lines(int nb_lines)
{
    for (int i = 0; i < nb_lines; i++)
    {
        int pos[4][2];
        current_tetrimino->get_position(&pos);
        bool skip = false;
        for (int row = 1; row < NUMBER_ROWS; row++)
            for (int col = 0; col < NUMBER_COLS; col++)
                for (int j = 0; j < 4; j++)
                    if (pos[j][0] == col && pos[j][1] == row-1 &&
                        board[col][row] != tile_empty)
                            skip = true;
        
        if (skip)
            continue;
        
        for (int row = 1; row < NUMBER_ROWS; row++)
        {
            for (int col = 0; col < NUMBER_COLS; col++)
            {
                if (board[col][row] != tile_empty)
                {
                    board[col][row - 1] = board[col][row];
                    board[col][row] = tile_empty;
                }
            }
        }
        int hole = rand() % NUMBER_COLS;
        for (int col = 0; col < NUMBER_COLS; col++)
        {
            if (col != hole && board[col][NUMBER_ROWS - 1] == tile_empty)
                board[col][NUMBER_ROWS - 1] = title_add_line;
        }
    }
}

Uint8 *AI_player::simulate_keyboard_input(input_t input) const
{
    Uint8 *keys;
    keys = new Uint8[BUFF_SIZE];
    keys[SDL_SCANCODE_RIGHT] = 0;
    keys[SDL_SCANCODE_LEFT] = 0;
    keys[SDL_SCANCODE_UP] = 0;
    keys[SDL_SCANCODE_DOWN] = 0;
    keys[SDL_SCANCODE_LCTRL] = 0;
    keys[SDL_SCANCODE_C] = 0;
    keys[SDL_SCANCODE_SPACE] = 0;
    switch (input)
    {
    case INPUT_RIGHT:
        keys[SDL_SCANCODE_RIGHT] = (Uint8)1;
        break;
    case INPUT_LEFT:
        keys[SDL_SCANCODE_LEFT] = (Uint8)1;
        break;
    case INPUT_UP:
        keys[SDL_SCANCODE_UP] = (Uint8)1;
        break;
    case INPUT_DOWN:
        keys[SDL_SCANCODE_DOWN] = (Uint8)1;
        break;
    case INPUT_CTRL:
        keys[SDL_SCANCODE_LCTRL] = (Uint8)1;
        break;
    case INPUT_C:
        keys[SDL_SCANCODE_C] = (Uint8)1;
        break;
    case INPUT_SPACE:
        keys[SDL_SCANCODE_SPACE] = (Uint8)1;
        break;
    default:
        break;
    }
    return keys;
}

bool AI_player::is_move_down_valid(
    tile_name_t test_board[NUMBER_COLS][NUMBER_ROWS],
    int test_pos[4][2]) const
{
    for (int i = 0; i < 4; i++)
        if (test_pos[i][1] + 1 >= NUMBER_ROWS ||
            test_board[test_pos[i][0]][test_pos[i][1] + 1] != tile_empty)
            return false;
    return true;
}

bool AI_player::is_in_board_tetrimino(
    tile_name_t test_board[NUMBER_COLS][NUMBER_ROWS],
    int test_pos[4][2]) const
{
    for (int i = 0; i < 4; i++)
        if (!is_in_board(test_pos[i][0], test_pos[i][1]))
            return false;
    return true;
}

void AI_player::reset_test_board(
    tile_name_t (*test_board)[NUMBER_COLS][NUMBER_ROWS]) const
{
    for (int i = 0; i < NUMBER_COLS; i++)
        for (int j = 0; j < NUMBER_ROWS; j++)
            (*test_board)[i][j] = board[i][j];
}

double AI_player::evaluate_board(
    tile_name_t test_board[NUMBER_COLS][NUMBER_ROWS]) const
{
    int max_height = 0;
    int nb_holes = 0;
    int nb_completed_lines = 0;
    int spikyness = 0;
    // remove completed lines
    std::vector<int> line_full;
    for (int i = NUMBER_ROWS - 1; i >= 0; i--)
    {
        int c = 0;
        for (int j = 0; j < NUMBER_COLS; j++)
            if (test_board[j][i] != tile_empty)
                c++;
        if (c == NUMBER_COLS)
            line_full.push_back(i);
    }
    for (int i = 0; i < line_full.size(); i++)
        for (int j = 0; j < NUMBER_COLS; j++)
            test_board[j][line_full[i]] = tile_empty;

    int i = 0;
    for (int k = 0; k < line_full.size(); k++)
        for (int i = line_full[k] + k - 1; i >= 0; i--)
            for (int j = 0; j < NUMBER_COLS; j++)
                test_board[j][i + 1] = test_board[j][i];
    nb_completed_lines = line_full.size();

    // array indicating to max higher occupied tile per column
    int height_board[NUMBER_COLS] = {0};
    for (int i = 0; i < NUMBER_COLS; i++)
    {
        height_board[i] = 0;
        for (int j = NUMBER_ROWS - 1; j >= 0; j--)
            if (test_board[i][j] != tile_empty)
                height_board[i] = NUMBER_ROWS - 1 - j;
    }
    // 1 - max height to minimise
    for (int i = 0; i < NUMBER_COLS; i++)
    {
        if (height_board[i] > max_height)
        {
            max_height = height_board[i];
        }
    }
    // 2 - detect holes
    for (int i = 0; i < NUMBER_COLS; i++)
    {
        for (int j = NUMBER_ROWS - height_board[i]; j < NUMBER_ROWS; j++)
            if (test_board[i][j] == tile_empty)
                nb_holes++;
    }
    // 3 - spikyness
    for (int i = 0; i < NUMBER_COLS - 1; i++)
    {
        spikyness += abs(height_board[i] - height_board[i + 1]);
    }

    return 2 * max_height
           + 1.5 * nb_holes
           + 0.5 * spikyness
           - 4 * nb_completed_lines;
}

void AI_player::compute_scores(
    Tetrimino *test_tetrimino,
    double (*scores)[2][4][NUMBER_COLS + 2],
    int hold) const
{
    tile_name_t test_board[NUMBER_COLS][NUMBER_ROWS];
    reset_test_board(&test_board);

    int origin_x = test_tetrimino->get_x();
    int origin_y = test_tetrimino->get_y();
    for (int i = 0; i < 4; i++) // orientation
    {
        for (int j = -2; j < NUMBER_COLS; j++) //each column
        {
            test_tetrimino->set_x(j);
            test_tetrimino->set_y(origin_y);
            int test_pos[4][2];
            test_tetrimino->get_position(&test_pos);
            int count_in_board = 0;
            for (int k = 0; k < 4; k++)
                if (test_pos[k][0] >= 0 && test_pos[k][0] < NUMBER_COLS)
                    count_in_board++;

            if (count_in_board == 4)
            {
                int score = 0;
                // simulate fast drop
                while (is_move_down_valid(test_board, test_pos))
                {
                    test_tetrimino->move_down();
                    test_tetrimino->get_position(&test_pos);
                }
                test_tetrimino->get_position(&test_pos);
                if (!is_in_board_tetrimino(test_board, test_pos))
                {
                    (*scores)[hold][i][j + 2] = DBL_MAX;
                }
                else
                {
                    // add tetrimino to board
                    for (int k = 0; k < 4; k++)
                        test_board[test_pos[k][0]][test_pos[k][1]] = tile_I;

                    // evaluate board
                    score = evaluate_board(test_board);

                    // reset test board
                    reset_test_board(&test_board);
                    (*scores)[hold][i][j + 2] = score;
                }
            }
            else
            {
                (*scores)[hold][i][j + 2] = DBL_MAX;
            }
        }
        test_tetrimino->set_x(origin_x);
        test_tetrimino->set_y(origin_y);
        test_tetrimino->rotate_right();
    }
}
std::vector<input_t> AI_player::compute_best_move() const
{
    std::vector<input_t> moves;
    double scores[2][4][NUMBER_COLS + 2] = {{{0}}};
    Tetrimino *test_tetrimino_current = new Tetrimino(*current_tetrimino);
    compute_scores(test_tetrimino_current, &scores, 0);
    delete test_tetrimino_current;
    if (hold != nullptr && is_hold_available)
    {
        Tetrimino *test_tetrimino_hold = new Tetrimino(*hold);
        compute_scores(test_tetrimino_hold, &scores, 1);
        delete test_tetrimino_hold;
    }
    else
    {
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < NUMBER_COLS + 2; j++)
                scores[1][i][j] = DBL_MAX;
    }

    // get min score
    double min_score = DBL_MAX;
    int min_rotation = 0;
    int min_x = 0;
    int hold = 0;
    for (int k = 1; k >= 0; k--)
    {
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < NUMBER_COLS + 2; j++)
            {
                if (min_score > scores[k][i][j])
                {
                    min_score = scores[k][i][j];
                    min_rotation = i;
                    min_x = j;
                    hold = k;
                }
            }
        }
    }

    moves.push_back(INPUT_NONE);

    // add hold if necessary
    if (hold)
    {
        moves.push_back(INPUT_C);
        moves.push_back(INPUT_NONE);
    }

    // add rotation to move list
    switch (min_rotation)
    {
    case 1:
        moves.push_back(INPUT_UP);
        moves.push_back(INPUT_NONE);
        break;
    case 2:
        moves.push_back(INPUT_UP);
        moves.push_back(INPUT_NONE);
        moves.push_back(INPUT_UP);
        moves.push_back(INPUT_NONE);
        break;
    case 3:
        moves.push_back(INPUT_UP);
        moves.push_back(INPUT_NONE);
        moves.push_back(INPUT_UP);
        moves.push_back(INPUT_NONE);
        moves.push_back(INPUT_UP);
        moves.push_back(INPUT_NONE);
    default:
        break;
    }

    int delta_x = min_x - current_tetrimino->get_x() - 2;
    // add moves along x axis
    if (delta_x < 0)
    {
        for (int i = 0; i < -delta_x; i++)
            moves.push_back(INPUT_LEFT);
    }
    else if (delta_x > 0)
    {
        for (int i = 0; i < delta_x; i++)
            moves.push_back(INPUT_RIGHT);
    }

    // add fast drop
    moves.push_back(INPUT_SPACE);
    std::reverse(moves.begin(), moves.end());
    return moves;
}
