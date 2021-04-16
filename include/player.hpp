/**
* \file player.hpp
* \brief Declaration file of the Player class
* \date 09/02/2021
* \author Antoine BALZANO and Hugo LAULLIER
*/
#ifndef _PLAYER_HPP_
#define _PLAYER_HPP_

#include "constants.hpp"
#include "tetrimino.hpp"

/**
* \class Player
* \brief Player, contains methods and variables for a game of tetris 
* mother class of Human_player and AI_player
*/
class Player
{
protected:
    /*!< number of player */
    int player_number;

    /*!< number of completed lines */
    int line_completed;

    /*!< level */
    int level;

    /*!< score */
    int score;

    /*!< speed */
    double speed;

    /*!< boolean indicating if the game is over */
    bool is_game_over = false;

    /*!< boolean indicating if the player can hold the current tetrimino */
    bool is_hold_available = true;

    /*!< boolean indicating if the player can drop the tetrimino fast */
    bool fast_down_available = true;

    /*!< boolean indicating if the player can rotate the tetrimino */
    bool rotate_available = true;

    /*!< boolean indicating if current tetrimino is a new tetrimino */
    bool is_new_tetrimino = true;

    /*!< x offset in pixels for display on canevas */
    int offset_x;

    /*!< current tetrimino that can be moved by the player on board */
    Tetrimino *current_tetrimino;

    /*!< tetrimino in hold (init at nullptr) */
    Tetrimino *hold;

    /*!< tetrimino queue on right of the board, first element of list is
         current_tetrimino and rest is part of the queue */
    std::vector<Tetrimino *> queue_tetrimino;

    /*!< board containing the name of each tile (current tetrimino is not 
         represented in this array) */
    tile_name_t board[NUMBER_COLS][NUMBER_ROWS];

    /*!< SDL renderer */
    SDL_Renderer *renderer;

    /*!< number of lines that have been send by the ennemy to the player */
    int send_lines;

public:
    /*!
     * \brief Constructor of the class Player
     */
    Player(SDL_Renderer *renderer_, int player_number_, int offset_x_);

    /*!
     * \brief Destructor of the class Player
     */
    ~Player();

    /*!
     * \brief Get attribute player_number value
     */
    int get_player_number() const;

    /*!
     * \brief Get attribute line_completed value
     */
    int get_line_completed() const;

    /*!
     * \brief Get attribute level value
     */
    int get_level() const;

    /*!
     * \brief Get attribute score value
     */
    int get_score() const;

    /*!
     * \brief Get attribute speed value
     */
    double get_speed() const;

    /*!
     * \brief Get attribute is_game_over value
     */
    bool get_is_game_over() const;

    /*!
     * \brief Get attribute is_new_tetrimino value
     */
    bool get_is_new_tetrimino() const;

    /*!
     * \brief Get attribute send_lines value
     */
    int get_send_lines();

    /*!
     * \brief Set attribute is_new_tetrimino
     * \param value : new value of is_new_tetrimino
     */
    void set_is_new_tetrimino(bool value);

    /*!
     * \brief Display board on canevas
     */
    void display_board() const;

    /*!
     * \brief Display current_tetrimino on canevas
     */
    void display_current_tetrimino() const;

    /*!
     * \brief Display queue_tetrimino on canevas
     */
    void display_queue_tetrimino() const;

    /*!
     * \brief Display hold_tetrimino on canevas
     */
    void display_hold_tetrimino() const;

    /*!
     * \brief Shift down all rows above the k th row
     */
    void shift_down_board(int k);

    /*!
     * \brief heandle the ceration of a new tetrimino
     */
    void new_tetrimino();

    /*!
     * \brief place the current tetrimino in hold
     */
    void new_hold();

    /*!
     * \brief Move down the current tetrimino
     * return false if the current tetrimino is blocked
     */
    bool move_down();

    /*!
     * \brief Move left the current tetrimino
     * return false if the current tetrimino is blocked
     */
    bool move_left();

    /*!
     * \brief Move right the current tetrimino
     * return false if the current tetrimino is blocked
     */
    bool move_right();

    /*!
     * \brief Move down the current tetrimino until it reach the bottom 
     * of the board
     */
    void fast_down();

    /*!
     * \brief rotate the current tetrimino
     * \param dir : direction of the rotation
     */
    bool rotate(rotate_dir_t dir);

    /*!
     * \brief Display score, level, line completed
     * \param font : text font
     */
    virtual void display_player_info(TTF_Font *font) = 0;

    /*!
     * \brief analyse keyboard and execute action from keypress inputs
     * \param keys : state of keyboard
     */
    void keyboard(const Uint8 *keys);

    /*!
     * \brief handle player input, add some delay between inputs 
     * \param difficulty
     * \param counter
     * \param counter_input_delay
     */
    virtual void handle_player_input(double difficulty,
                                     double *counter,
                                     double *counter_input_delay) = 0;

    /*!
     * \brief display the shadow of the current tetrimino
     * (only for human player)
     */
    virtual void display_projection() = 0;

    /*!
     * \brief reset attribute send_lines
     */
    void reset_send_lines();

    /*!
     * \brief add nb_lines to attribute send_lines
     * \param nb_lines : value to add to send_lines
     */
    void receive_lines(int nb_lines);
};

// -------------------------------------------------------------------------- //

/**
* \class Human_player
* \brief Human_player herited class of Player class
*/
class Human_player : public Player
{
private:
public:
    /*!
     * \brief Constructor of the class Human_player
     */
    Human_player(SDL_Renderer *renderer_, int player_number_, int offset_x_);

    /*!
     * \brief handle player input, add some delay between inputs 
     * \param difficulty
     * \param counter
     * \param counter_input_delay
     */
    void handle_player_input(double difficulty,
                             double *counter,
                             double *counter_input_delay) override;

    /*!
     * \brief display the shadow of the current tetrimino
     * (only for human player)
     */
    void display_projection() override;

    /*!
     * \brief Display score, level, line completed
     * \param font : text font
     */
    void display_player_info(TTF_Font *font) override;
};

// -------------------------------------------------------------------------- //

/**
* \class AI_player
* \brief AI_player herited class of Player class, contains methods to compute 
* the AI moves
*/
class AI_player : public Player
{
private:
    /*!< boolean indicating if the current tetrimino is the first tetrimino
         of the game */
    bool is_first_move = true;

    /*!< keypress input list */
    std::vector<input_t> input_queue;

public:
    /*!
     * \brief Constructor of the class AI_player
     */
    AI_player(SDL_Renderer *renderer_, int player_number_, int offset_x_);

    /*!
     * \brief Get attribute is_first_move value
     */
    bool get_is_first_move() const;

    /*!
     * \brief Set attribute is_first_move value
     * \param value : new value of is_first_move
     */
    void set_is_first_move(bool value);

    /*!
     * \brief Get attribute input_queue value (vector)
     */
    std::vector<input_t> get_input_queue() const;
    
    /*!
     * \brief Set attribute set_input_queue value
     * \param new_input_queue : new value of set_input_queue
     */
    void set_input_queue(std::vector<input_t> new_input_queue);

    /*!
     * \brief pop last element of input_queue
     */
    input_t pop_input_queue();

    /*!
     * \brief return an empty keyboard except for the input given, to
     * simulate a keypress by the AI
     * \param input : input of the AI
     */
    Uint8 *simulate_keyboard_input(input_t input) const;

    /*!
     * \brief return a serie of moves to execute the best move
     */
    std::vector<input_t> compute_best_move() const;

    /*!
     * \brief test if move is valid in test_board
     * \param test_board : test board simulation
     * \param test_pos : simulation of current tetrimino
     */
    bool is_move_down_valid(
        tile_name_t test_board[NUMBER_COLS][NUMBER_ROWS],
        int test_pos[4][2]) const;

    /*!
     * \brief test if test_pos is in test_board
     * \param test_board : test board simulation
     * \param test_pos : simulation of current tetrimino
     */
    bool is_in_board_tetrimino(
        tile_name_t test_board[NUMBER_COLS][NUMBER_ROWS],
        int test_pos[4][2]) const;

    /*!
     * \brief reset test_board (modify a pointer)
     * \param test_board : test board simulation
     */
    void reset_test_board(
        tile_name_t (*test_board)[NUMBER_COLS][NUMBER_ROWS]) const;

    /*!
     * \brief evaluate a board (compute 1 score)
     * \param test_board : test board simulation
     */
    double evaluate_board(
        tile_name_t test_board[NUMBER_COLS][NUMBER_ROWS]) const;

    /*!
     * \brief compute the score of all possible board for a the current 
     * tetrimino and the current board state
     * \param test_board : test board simulation
     * \param scores : array storing all the scores
     */
    void compute_scores(
        Tetrimino *test_tetrimino,
        double (*scores)[2][4][NUMBER_COLS + 2], int hold) const;

    /*!
     * \brief handle player input, add some delay between inputs 
     * \param difficulty
     * \param counter
     * \param counter_input_delay
     */
    void handle_player_input(double difficulty,
                             double *counter,
                             double *counter_input_delay) override;

    /*!
     * \brief display the shadow of the current tetrimino
     * (only for human player) do nothing for AI
     */
    void display_projection() override;

    /*!
     * \brief Display score, level, line completed
     * \param font : text font
     */
    void display_player_info(TTF_Font *font) override;
};

#endif