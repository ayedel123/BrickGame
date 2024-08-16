#ifndef CPP3_BRICKGAME_V2_0_1_SRC_GUI_DESKTOP_BRICK_GAME_MEXT_BRICK_WINDOW_H_
#define CPP3_BRICKGAME_V2_0_1_SRC_GUI_DESKTOP_BRICK_GAME_MEXT_BRICK_WINDOW_H_

#include <QPainter>
#include <QWidget>

#include "../../../brick_game/tetris/tetris.h"
#include "get_brush.h"
#include "qevent.h"

class NextBrickWidget : public QWidget {
  Q_OBJECT

 public:
  GameInfo *game_info;
  bool istetris = false;

  explicit NextBrickWidget(QWidget *parent = nullptr);

  void paintEvent(QPaintEvent *event) override {
    QPainter painter(this);
    int tetris = false;
    for (int i = 0; i < 4; i++) {
      if (game_info->next_brick.cords[i][0] != 0) tetris = true;
      if (game_info->next_brick.cords[i][0] != 0) tetris = true;
    }
    int cell_size = 40;
    for (int i = 0; i < 4 && tetris && game_info; i++) {
      painter.setBrush(GetBrush(game_info->next_brick.color));
      painter.drawRect(cell_size * game_info->next_brick.cords[i][0],
                       cell_size * game_info->next_brick.cords[i][1], cell_size,
                       cell_size);
      painter.setBrush(GetBrush(0));
    }
  }

 signals:
};

#endif  // NEXT_BRICK_WIDGET_H
