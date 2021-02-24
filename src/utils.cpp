#include "headers/utils.hpp"

int unit_to_pix_col_board(int unit)
{
    return 2 * TILE_SIZE_PX * unit + 2 * MARGIN_X + 5 * TILE_SIZE_PX;
}

int unit_to_pix_row_board(int unit)
{
    return 2 * TILE_SIZE_PX * unit + MARGIN_Y;
}

int unit_to_pix_col_queue(int unit)
{
    return TILE_SIZE_PX * unit + 3 * MARGIN_X 
        + (5 + NUMBER_COLS*2) * TILE_SIZE_PX;
}

int unit_to_pix_row_queue(int unit)
{
    return TILE_SIZE_PX * unit + MARGIN_Y;
}

int unit_to_pix_col_hold(int unit)
{
    return TILE_SIZE_PX * unit + MARGIN_X;
}

int unit_to_pix_row_hold(int unit)
{
    return TILE_SIZE_PX * unit + MARGIN_Y;
}

bool is_in_board(int x, int y)
{
    return x >= 0 && y >= 0 && x < NUMBER_COLS && y < NUMBER_ROWS ;
}

std::vector<int> get_color_from_tile_name(tile_name_t tile)
{
    std::vector<int> color;
    switch (tile)
    {
    case tile_I:
        color.push_back(43);
        color.push_back(250);
        color.push_back(250);
    case tile_O:
        color.push_back(255);
        color.push_back(228);
        color.push_back(54);
        break;
    case tile_T:
        color.push_back(147);
        color.push_back(112);
        color.push_back(219);
        break;
    case tile_L:
        color.push_back(255);
        color.push_back(131);
        color.push_back(0);
        break;
    case tile_J:
        color.push_back(1);
        color.push_back(49);
        color.push_back(180);
        break;
    case tile_Z:
        color.push_back(187);
        color.push_back(11);
        color.push_back(11);
        break;
    case tile_S:
        color.push_back(158);
        color.push_back(253);
        color.push_back(56);
        break;
    default:
        color.push_back(0);
        color.push_back(0);
        color.push_back(0);
        break;
    }
    return color;
}

[[ noreturn ]] void handle_error(const char * msg, ...) {
    va_list ap;

    va_start(ap, msg);
    vfprintf(stderr, "error : ", ap);
    vfprintf(stderr, msg, ap);
    fprintf(stderr, "\n");
    va_end(ap);

    exit(EXIT_FAILURE);
}

[[ noreturn ]] void handle_perror(const char * msg, ...) {
    va_list ap;

    va_start(ap, msg);
    vfprintf(stderr, "perror : ", ap);
    vfprintf(stderr, msg, ap);
    fprintf(stderr, "\n");
    va_end(ap);
    perror("");

    exit(EXIT_FAILURE);
}
void render_text(SDL_Renderer *renderer, TTF_Font *font, 
                 int x, int y, const char *text)
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