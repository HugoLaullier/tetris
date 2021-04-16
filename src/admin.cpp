#include "../include/admin.hpp"

Admin::~Admin()
{
    TTF_CloseFont(font);
    TTF_CloseFont(font_small);
    TTF_Quit();
    Mix_FreeMusic(music);
    Mix_CloseAudio();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Admin::load_font()
{
    font = TTF_OpenFont("./font/OpenSans-Regular.ttf", 24);
    if (font == NULL)
    {
        fprintf(stderr, "error: font not found\n");
        exit(EXIT_FAILURE);
    }
    font_small = TTF_OpenFont("./font/OpenSans-Regular.ttf", 19);
    if (font_small == NULL)
    {
        fprintf(stderr, "error: font not found\n");
        exit(EXIT_FAILURE);
    }
}

Admin::Admin() : status(MENU)
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
    {
        fprintf(stderr, "error: SDL Init\n");
        exit(EXIT_FAILURE);
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) 
        == -1) //Initialisation de l'API Mixer
    {
        fprintf(stderr, "%s", Mix_GetError());
        exit(EXIT_FAILURE);
    }
    music = Mix_LoadMUS("./mp3/tetris_music.mp3");
    Mix_PlayMusic(music, -1);
    Mix_PauseMusic();

    TTF_Init();

    // Window
    window_w = 4 * MARGIN_X + (5 + NUMBER_COLS * 2 + 4) * TILE_SIZE_PX;
    window_h = NUMBER_ROWS * 2 * TILE_SIZE_PX + MARGIN_Y * 2;
    window = SDL_CreateWindow("Tetris",
                              SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED,
                              window_w,
                              window_h,
                              SDL_WINDOW_SHOWN);

    // Renderer on the window
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    load_font();
}

void Admin::start()
{
    Uint64 prev, now = SDL_GetPerformanceCounter(); // timers
    double delta_t;                                 // frame duration in ms

    while (status != QUIT)
    {
        prev = now;
        now = SDL_GetPerformanceCounter();
        delta_t = (double)((now-prev) / (double)SDL_GetPerformanceFrequency());
        switch (status)
        {
        case MENU:
            menu();
            break;
        case PLAY_1:
            play_1();
            break;
        case PLAY_2:
            menu_play_2();
            break;
        case PLAY_3:
            play_3();
            break;
        case HELP:
            help();
            break;
        default:
            break;
        }
        int delay_ms = (int)floor(16.666f - delta_t);
        if (delay_ms < 100 && delay_ms > 0)
            SDL_Delay(delay_ms);
    }
}

void Admin::menu()
{
    int offset_y = 80;
    char *text = new char[BUFF_SIZE];
    int width_text;

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    TTF_SetFontStyle(font, TTF_STYLE_BOLD);
    TTF_SizeText(font, "TETRIS : THE GAME", &width_text, NULL);
    render_text(renderer, font,
                unit_to_pix_col_board(NUMBER_COLS + 5) / 2 - width_text / 2,
                offset_y, "TETRIS : THE GAME");

    TTF_SetFontStyle(font, TTF_STYLE_NORMAL);
    // TTF_SetFontStyle(font_small, TTF_STYLE_ITALIC);
    TTF_SizeText(font_small, "Press 1 - to play in solo", &width_text, NULL);
    render_text(renderer, font_small,
                unit_to_pix_col_board(NUMBER_COLS + 5) / 2 - width_text / 2,
                offset_y + 180, "Press 1 - to play in solo");

    TTF_SizeText(font_small, "Press 2 - to play in multiplayer",
                 &width_text, NULL);
    render_text(renderer, font_small,
                unit_to_pix_col_board(NUMBER_COLS + 5) / 2 - width_text / 2,
                offset_y + 230, "Press 2 - to play in multiplayer");

    TTF_SizeText(font_small, "Press 3 - AI demo",
                 &width_text, NULL);
    render_text(renderer, font_small,
                unit_to_pix_col_board(NUMBER_COLS + 5) / 2 - width_text / 2,
                offset_y + 280, "Press 3 - AI demo");

    TTF_SizeText(font_small, "Press H - display help", &width_text, NULL);
    render_text(renderer, font_small,
                unit_to_pix_col_board(NUMBER_COLS + 5) / 2 - width_text / 2,
                offset_y + 330, "Press H - display help");

    TTF_SizeText(font_small, "Press Escape - quit", &width_text, NULL);
    render_text(renderer, font_small,
                unit_to_pix_col_board(NUMBER_COLS + 5) / 2 - width_text / 2,
                offset_y + 380, "Press Escape - quit");

    TTF_SetFontStyle(font_small, TTF_STYLE_NORMAL);
    SDL_RenderPresent(renderer);
    delete[] text;

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
            case SDLK_3:
                status = PLAY_3;
                break;
            case SDLK_h:
                status = HELP;
                break;
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

void Admin::help()
{
    int offset_x = 20;
    int offset_y = 80;
    char *text = new char[BUFF_SIZE];
    int width_text;

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    TTF_SetFontStyle(font, TTF_STYLE_BOLD);
    TTF_SizeText(font, "HELP : CONTROLS", &width_text, NULL);
    render_text(renderer, font, 
        unit_to_pix_col_board(NUMBER_COLS + 5) / 2 - width_text / 2, 
        offset_y, "HELP : CONTROLS");
    TTF_SetFontStyle(font, TTF_STYLE_NORMAL);
    // TTF_SetFontStyle(font_small, TTF_STYLE_ITALIC);
    render_text(renderer, font_small, offset_x, offset_y + 80,
                "Left arrow : move left");
    render_text(renderer, font_small, offset_x, offset_y + 115,
                "Right arrow : move right");
    render_text(renderer, font_small, offset_x, offset_y + 150,
                "Up arrow : rotate clockwise");
    render_text(renderer, font_small, offset_x, offset_y + 185,
                "Ctrl : rotate counter-clockwise");
    render_text(renderer, font_small, offset_x, offset_y + 220,
                "Bottom arrow : soft drop");
    render_text(renderer, font_small, offset_x, offset_y + 255,
                "Spacebar : hard drop");
    render_text(renderer, font_small, offset_x, offset_y + 290,
                "C : hold piece");
    render_text(renderer, font_small, offset_x, offset_y + 325,
                "S : play/stop music");
    TTF_SizeText(font_small, "Press M - return to menu", 
        &width_text, NULL);
    render_text(renderer, font_small,
                unit_to_pix_col_board(NUMBER_COLS + 5) / 2 - width_text / 2,
                offset_y + 400, "Press M - return to menu");
    TTF_SizeText(font_small, "Press Escape - quit", &width_text, NULL);
    render_text(renderer, font_small,
                unit_to_pix_col_board(NUMBER_COLS + 5) / 2 - width_text / 2,
                offset_y + 450, "Press Escape - quit");
    TTF_SetFontStyle(font_small, TTF_STYLE_NORMAL);
    SDL_RenderPresent(renderer);
    delete[] text;

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
                Mix_PausedMusic() ? Mix_ResumeMusic() : Mix_PauseMusic();
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
    SDL_SetWindowSize(window, window_w, window_h);
    Game *game = new Game(window,
                     renderer,
                     font,
                     font_small,
                     window_w,
                     window_h,
                     status,
                     DIFFICULTY_EASY,
                     new Human_player(renderer, 1, 0));
    status = game->play();
    delete game;
}

void Admin::menu_play_2()
{
    int offset_y = 80;
    char *text = new char[BUFF_SIZE];
    int width_text;

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    TTF_SetFontStyle(font, TTF_STYLE_BOLD);
    TTF_SizeText(font, "CHOOSE AI DIFFICULTY", &width_text, NULL);
    render_text(renderer, font,
                unit_to_pix_col_board(NUMBER_COLS + 5) / 2 - width_text / 2,
                offset_y, "CHOOSE AI DIFFICULTY");

    TTF_SetFontStyle(font, TTF_STYLE_NORMAL);
    // TTF_SetFontStyle(font_small, TTF_STYLE_ITALIC);
    TTF_SizeText(font_small, "Press 1 - Easy", &width_text, NULL);
    render_text(renderer, font_small,
                unit_to_pix_col_board(NUMBER_COLS + 5) / 2 - width_text / 2,
                offset_y + 180, "Press 1 - Easy");

    TTF_SizeText(font_small, "Press 2 - Normal",
                 &width_text, NULL);
    render_text(renderer, font_small,
                unit_to_pix_col_board(NUMBER_COLS + 5) / 2 - width_text / 2,
                offset_y + 230, "Press 2 - Normal");

    TTF_SizeText(font_small, "Press 3 - Hard",
                 &width_text, NULL);
    render_text(renderer, font_small,
                unit_to_pix_col_board(NUMBER_COLS + 5) / 2 - width_text / 2,
                offset_y + 280, "Press 3 - Hard");

    TTF_SizeText(font_small, "Press 4 - Impossible", &width_text, NULL);
    render_text(renderer, font_small,
                unit_to_pix_col_board(NUMBER_COLS + 5) / 2 - width_text / 2,
                offset_y + 330, "Press 4 - Impossible");

    TTF_SetFontStyle(font_small, TTF_STYLE_NORMAL);
    SDL_RenderPresent(renderer);
    delete[] text;

    while (status == PLAY_2 && SDL_PollEvent(&event))
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
                play_2(DIFFICULTY_EASY);
                break;
            case SDLK_2:
                play_2(DIFFICULTY_NORMAL);
                break;
            case SDLK_3:
                play_2(DIFFICULTY_HARD);
                break;
            case SDLK_4:
                play_2(DIFFICULTY_IMPOSSIBLE);
                break;
            case SDLK_m:
                status = MENU;
                break;
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

void Admin::play_2(int difficutly)
{
    SDL_SetWindowSize(window, window_w * 2, window_h);
    Game *game = new Game(window,
                     renderer,
                     font,
                     font_small,
                     window_w,
                     window_h,
                     status,
                     difficutly, // adjust difficulty here (AI)
                     new Human_player(renderer, 1, 0),
                     new AI_player(renderer, 2, window_w));
    status = game->play();
    delete game;
}

void Admin::play_3()
{
    SDL_SetWindowSize(window, window_w, window_h);
    Game *game = new Game(window,
                     renderer,
                     font,
                     font_small,
                     window_w,
                     window_h,
                     status,
                     DIFFICULTY_IMPOSSIBLE,
                     new AI_player(renderer, 1, 0));
    status = game->play();
    delete game;
}
