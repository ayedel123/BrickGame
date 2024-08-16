#include "ui.h"

void DrawGame(GameState state, GameInfo *game_info, WINDOW **windows)
{

  if (state == kGameOver)
  {
    GameOverMessage(windows[kGameWin], game_info->win_info.width);
  }
  else
  {
    DrawField(windows[kGameWin], game_info);
  }
}

void DrawField(WINDOW *win, GameInfo *game_info)
{

  for (int i = 0; i < game_info->win_info.height; i++)
  {
    for (int j = 0; j < game_info->win_info.width; j++)
    {

      if (game_info->field[i][j] != 0)
      {
        wrefresh(win);
        wattron(win, COLOR_PAIR(game_info->field[i][j]));
        mvwprintw(win, i + 1, j + 1, "0");
        wattroff(win, COLOR_PAIR(game_info->field[i][j]));
      }
      else
        mvwprintw(win, i + 1, j + 1, ".");
    }
  }

  wrefresh(win);
}

WINDOW *SetUpWindow(int win_number)
{

  int height = GAME_WINDOW_HEIGHT + 2;
  int width = GAME_WINDOW_WIDTH + 2;
  int starty = (LINES - height) / 2;
  int startx = 2 + width * win_number;
  refresh();
  WINDOW *local_win = CreateNewWin(height, width, starty, startx);
  return local_win;
}

int *SetUpBrickGameWindows(WINDOW **windows, int win_count)
{
  for (int i = 0; i < win_count; i++)
  {
    windows[i] = SetUpWindow(i);
  }
  return 0;
}

void InitColors()
{
  init_color(2, 0, 1000, 0);
  init_color(7, 1000, 400, 0);
  init_color(4, 200, 200, 1000);
  init_color(1, 1000, 200, 200);
  init_pair(1, COLOR_WHITE, 1);
  init_pair(2, COLOR_WHITE, 2);
  init_pair(3, COLOR_WHITE, 3);
  init_pair(4, COLOR_WHITE, 4);
  init_pair(5, COLOR_WHITE, 5);
  init_pair(6, COLOR_WHITE, 6);
  init_pair(7, COLOR_WHITE, 7);
}

void CursesSetUp()
{
  initscr();
  cbreak();
  noecho();
  keypad(stdscr, TRUE);
  start_color();
  use_default_colors();
  curs_set(0);
  InitColors();
  timeout(0);
}

void GameOverMessage(WINDOW *win, int height)
{
  mvwprintw(win, height / 2, 1, "game over");
  mvwprintw(win, height / 2 + 1, 1, "  press ");
  mvwprintw(win, height / 2 + 2, 1, " any key ");
  mvwprintw(win, height / 2 + 3, 1, "to start ");
  mvwprintw(win, height / 2 + 4, 1, " or 0 ");
  mvwprintw(win, height / 2 + 5, 1, "to exit ");

  wrefresh(win);
}

void StartMessage(WINDOW *win, int height)
{
  mvwprintw(win, height / 2, 2, "  press ");
  mvwprintw(win, height / 2 + 1, 2, " any key ");
  mvwprintw(win, height / 2 + 2, 2, "to start ");
  mvwprintw(win, height / 2 + 3, 2, "  or 0 ");
  mvwprintw(win, height / 2 + 4, 2, " to exit ");
  wrefresh(win);
}

void PrintMenu(WINDOW *menu_win, int highlight, const char *choices[], int choices_count)
{
  int x, y, i;

  x = 2;
  y = 2;
  for (i = 0; i < choices_count; ++i)
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
