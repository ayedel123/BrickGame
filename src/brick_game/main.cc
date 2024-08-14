

extern "C"
{
#include <ncurses.h>
}
#include "./tetris/tetris.h"
#include "./snake/snake.h"
#include "./snake/snake_game_loop.h"

void SetUp(WINDOW **windows, int win_count)
{
    srand(time(0));
    CursesSetUp();
    SetUpBrickGameWindows(windows, win_count);
}

int main()
{
    WINDOW *windows[3];
    GameInfo game_info;
    int **field = NULL;
    InitField(&field, GAME_WINDOW_HEIGHT, GAME_WINDOW_WIDTH);
    ClearField(field, GAME_WINDOW_HEIGHT, GAME_WINDOW_WIDTH);
    SetUp(windows, 2);

    int game = 1;
    while (game == 0 || game == 1)
    {
        game = ChoseGame(windows[0]);
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
        
    }
    endwin();
    DeleteField(field, GAME_WINDOW_HEIGHT);


    return 0;
}