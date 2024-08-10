#include "tetrisStats.h"

void printPoints(WINDOW *menuWin, GameInfo *game_info, int *y) {
  mvwprintw(menuWin, *y, 1, "%2d lvl", game_info->level);
  mvwprintw(menuWin, *y + 2, 1, "points");
  mvwprintw(menuWin, *y + 3, 1, "%5d", game_info->points);
  mvwprintw(menuWin, *y + 5, 1, "record");
  mvwprintw(menuWin, *y + 6, 1, "%5d", game_info->high_score);
  (*y) += 8;
}

void printNextBrick(WINDOW *menuWin, Brick *next, int *y) {

  mvwprintw(menuWin, *y, 1, "next:");
  (*y)++;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      mvwprintw(menuWin, *y + 1 + i, j + 3, " ");
    }
  }
  wattron(menuWin, COLOR_PAIR(next->color));

  for (int i = 0; i < 4; i++) {
    mvwprintw(menuWin, *y + 1 + next->cords[i][1], next->cords[i][0] + 3, "$");
  }
  wattroff(menuWin, COLOR_PAIR(next->color));
}

void printTetrisStats(WINDOW *menuWin, GameInfo *game_info, int isOnPause) {

  int y = 1;
  if (isOnPause) {
    mvwprintw(menuWin, y, 1, "%10s", "playing");
  } else {
    mvwprintw(menuWin, y, 1, "%10s", "on pause");
  }
  y++;
  printPoints(menuWin, game_info, &y);
  printNextBrick(menuWin, &game_info->next_Brick, &y);
  wrefresh(menuWin);
}