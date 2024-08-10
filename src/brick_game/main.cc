

extern "C"
{
#include <ncurses.h>
}
#include "./tetris/tetris.h"
#include "./snake/snake.h"


void SetUp(WINDOW **windows, int win_count, GameInfo *game_info, int **field)
{
    srand(time(0));
    CursesSetUp();
    SetUpBrickGameWindows(windows, win_count);
    InitGameInfo(game_info, field, TETRIS_GAME_SPEED, TETRIS_GAME_ACCELERATION, RANDOM_BRICK);
}
int ChoseGame(WINDOW *win)
{
    int height = 10, width = 30, start_y = 4, start_x = 4;
    int highlight = 0;
    int choice;
    const char *choices[] = {"Tetris", "Snake", "Exit"};
    int choices_count = sizeof(choices) / sizeof(char *);
    while (1)
    {
        choice = UserInput();
        switch (choice)
        {
        case KEY_UP:
            highlight = (highlight == 0) ? choices_count - 1 : highlight - 1;
            break;
        case KEY_DOWN:
            highlight = (highlight + 1) % choices_count;
            break;
        case 10:
            if (highlight == choices_count - 1)
                return -1;
            else
                return highlight;
            break;
        default:
            break;
        }
        PrintMenu(win, highlight, choices, choices_count);
    }
    return 0;
}

int main()
{
    WINDOW *windows[3];
    GameInfo game_info;
    int **field = NULL;
    InitField(&field, GAME_WINDOW_HEIGHT, GAME_WINDOW_WIDTH);
    ClearField(field, GAME_WINDOW_HEIGHT, GAME_WINDOW_WIDTH);
    SetUp(windows, 2, &game_info, field);

    int game = ChoseGame(windows[0]);
    if (game == 0)
    {
        TetrisSetUp(&game_info, field);
        TetrisGameLoop(&game_info, windows);
    }
    else if (game == 1)
    {
        SnakeSetUp(&game_info, field);
        SnakeGameLoop(&game_info, windows);
    }
    endwin();
    DeleteField(field, GAME_WINDOW_HEIGHT);

    putchar('0' + game);

    return 0;
}