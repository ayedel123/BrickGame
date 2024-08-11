

extern "C"
{
#include <ncurses.h>
}
#include "./tetris/tetris.h"
#include "./snake/snake.h"
#include "./snake/snake_game_loop.h"

void SetUp(WINDOW **windows, int win_count, GameInfo *game_info, int **field)
{
    srand(time(0));
    CursesSetUp();
    SetUpBrickGameWindows(windows, win_count);
    InitGameInfo(game_info, field, TETRIS_GAME_SPEED, TETRIS_GAME_ACCELERATION, RANDOM_BRICK);
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
    while (game == 0 || game == 1)
    {
        if (game == 0)
        {
            TetrisSetUp(&game_info, field);
            TetrisGameLoop(&game_info, windows);
        }
        else if (game == 1)
        {
            s21::Snake snake = s21::Snake(&game_info, field);
            SnakeGameLoop(snake, windows);
        }
        game = ChoseGame(windows[0]);
    }
    endwin();
    DeleteField(field, GAME_WINDOW_HEIGHT);

    putchar('0' + game);

    return 0;
}