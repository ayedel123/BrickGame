#include "stats.h"

void printPoints(WINDOW *menu_win, GameInfo *game_info, int *y) {
  mvwprintw(menu_win, *y, 1, "%2d lvl", game_info->level);
  mvwprintw(menu_win, *y + 2, 1, "points");
  mvwprintw(menu_win, *y + 3, 1, "%5d", game_info->points);
  mvwprintw(menu_win, *y + 5, 1, "record");
  mvwprintw(menu_win, *y + 6, 1, "%5d", game_info->high_score);
  (*y) += 8;
}

void printNextBrick(WINDOW *menu_win, Brick *next, int *y) {

  mvwprintw(menu_win, *y, 1, "next:");
  (*y)++;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      mvwprintw(menu_win, *y + 1 + i, j + 3, " ");
    }
  }
  wattron(menu_win, COLOR_PAIR(next->color));

  for (int i = 0; i < 4; i++) {
    mvwprintw(menu_win, *y + 1 + next->cords[i][1], next->cords[i][0] + 3, "$");
  }
  wattroff(menu_win, COLOR_PAIR(next->color));
}

void printTetrisStats(WINDOW *menu_win, GameInfo *game_info, int on_pause) {

  int y = 1;
  if (on_pause) {
    mvwprintw(menu_win, y, 1, "%10s", "playing");
  } else {
    mvwprintw(menu_win, y, 1, "%10s", "on pause");
  }
  y++;
  printPoints(menu_win, game_info, &y);
  printNextBrick(menu_win, &game_info->next_brick, &y);
  wrefresh(menu_win);
}