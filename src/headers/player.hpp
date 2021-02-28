#ifndef _PLAYER_HPP_
#define _PLAYER_HPP_

#include "constants.hpp"
#include "tetrimino.hpp"

class Player
{
protected:
    int player_number;
    int line_completed;
    int level;
    int score;
    double speed;
    bool is_game_over = false;
    bool is_hold_available = true;
    bool fast_down_available = true;
    bool rotate_available = true;
    bool is_new_tetrimino = true;
    int offset_x;
    Tetrimino *current_tetrimino;
    Tetrimino *hold;
    // first element is current_tetrimino
    // rest is part of the queue
    std::vector<Tetrimino *> queue_tetrimino;
    tile_name_t board[NUMBER_COLS][NUMBER_ROWS];
    SDL_Renderer *renderer;
    int send_lines;

public:
    // constructor
    Player(SDL_Renderer *renderer_, int player_number_, int offset_x_);
    // get
    int get_player_number() const;
    int get_line_completed() const;
    int get_level() const;
    int get_score() const;
    double get_speed() const;
    bool get_is_game_over() const;
    // set
    bool get_is_new_tetrimino() const;
    void set_is_new_tetrimino(bool value);
    // methods
    void display_board() const;
    void display_current_tetrimino() const;
    void display_queue_tetrimino() const;
    void display_hold_tetrimino() const;
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
    // display score, level, line completed
    virtual void display_player_info(TTF_Font *font) = 0;
    void keyboard(const Uint8 *keys);
    virtual void handle_player_input(double difficulty,
                                     double *counter,
                                     double *counter_input_delay) = 0;
    virtual void display_projection() = 0;
    int get_send_lines();
    void reset_send_lines();
    void receive_lines(int nb_lines);
};

class Human_player : public Player
{
private:
public:
    Human_player(SDL_Renderer *renderer_, int player_number_, int offset_x_);
    void handle_player_input(double difficulty,
                             double *counter,
                             double *counter_input_delay) override;
    void display_projection() override;
    void display_player_info(TTF_Font *font) override;
};

class AI_player : public Player
{
private:
    bool is_first_move = true;
    std::vector<input_t> input_queue;

public:
    // constructor
    AI_player(SDL_Renderer *renderer_, int player_number_, int offset_x_);
    // get
    bool get_is_first_move() const;
    void set_is_first_move(bool value);
    std::vector<input_t> get_input_queue() const;
    // set
    void set_input_queue(std::vector<input_t> new_input_queue);
    // methods
    input_t pop_input_queue();

    Uint8 *simulate_keyboard_input(input_t input) const;

    std::vector<input_t> compute_best_move() const;

    bool is_move_down_valid(
        tile_name_t test_board[NUMBER_COLS][NUMBER_ROWS],
        int test_pos[4][2]) const;

    bool is_in_board_tetrimino(
        tile_name_t test_board[NUMBER_COLS][NUMBER_ROWS],
        int test_pos[4][2]) const;

    void reset_test_board(
        tile_name_t (*test_board)[NUMBER_COLS][NUMBER_ROWS]) const;

    double evaluate_board(
        tile_name_t test_board[NUMBER_COLS][NUMBER_ROWS]) const;

    void compute_scores(
        Tetrimino *test_tetrimino,
        double (*scores)[2][4][NUMBER_COLS + 2], int hold) const;
    // overrided methods
    void handle_player_input(double difficulty,
                             double *counter,
                             double *counter_input_delay) override;
    void display_projection() override;
    void display_player_info(TTF_Font *font) override;
};

#endif