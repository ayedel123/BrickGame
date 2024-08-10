

extern "C"
{
#include <ncurses.h>
//#include <cstdlib> // или <stdlib.h>, если у вас C
}
#include "./tetris/tetris.h"
#include "./snake/snake.h"

//#include <list>
//  #include "./tetris/snake.h"

void SetUp(WINDOW **windows, int winCount, GameInfo *game_info, int **field)
{
    srand(time(0));
    cursesSetUp();
    setUpBrickGameWindows(windows, winCount);
    InitGameInfo(game_info, field, TETRIS_GAME_SPEED, TETRIS_GAME_ACCELERATION, RANDOM_BRICK);
}

void print_menu(WINDOW *menu_win, int highlight, const char *choices[], int n_choices)
{
    int x, y, i;

    x = 2;
    y = 2;
    for (i = 0; i < n_choices; ++i)
    {
        if (i == highlight)
        {
            wattron(menu_win, A_REVERSE);
        }
        mvwprintw(menu_win, y, x, "%s", choices[i]);
        wattroff(menu_win, A_REVERSE);
        y++;
    }
    wrefresh(menu_win);
}

int ChoseGame(WINDOW *win)
{
    int height = 10, width = 30, start_y = 4, start_x = 4;
    int highlight = 0;
    int choice;
    const char *choices[] = {"Tetris", "Snake", "Exit"};
    int n_choices = sizeof(choices) / sizeof(char *);
    while (1)
    {
        choice = userInput(); // Получение ввода
        switch (choice)
        {
        case KEY_UP:
            highlight = (highlight == 0) ? n_choices - 1 : highlight - 1;
            break;
        case KEY_DOWN:
            highlight = (highlight + 1) % n_choices;
            break;
        case 10:                            // Enter key
            if (highlight == n_choices - 1) // Если "Exit"
                return -1;
            else
                return highlight;
            break;
        default:
            break;
        }
        print_menu(win, highlight, choices, n_choices);
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
    //
    endwin();
    DeleteField(field, GAME_WINDOW_HEIGHT);

    putchar('0' + game);

    return 0;
}