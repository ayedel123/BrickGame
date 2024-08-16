#ifndef CPP3_BRICKGAME_V2_0_1_SRC_GUI_DESKTOP_BRICK_GAME_GAME_WINDOW_H_
#define CPP3_BRICKGAME_V2_0_1_SRC_GUI_DESKTOP_BRICK_GAME_GAME_WINDOW_H_

#include <QKeyEvent>
#include <QPainter>
#include <QTimer>
#include <QWidget>

#include "../../../brick_game/snake/snake.h"
#include "../../../brick_game/snake/snake_game_loop.h"
#include "../../../brick_game/tetris/tetris.h"
#include "../get_signal_desctop/get_signal_desktop.h"
#include "get_brush.h"
#include "next_brick_widget.h"

namespace Ui {
class GameForm;
}

class GameForm : public QWidget {
  Q_OBJECT

 signals:
  void MainWindow();
 private slots:
  void UpdateCurrentState();

 public:
  explicit GameForm(QWidget *parent = nullptr);
  ~GameForm();
  void SetGameType(int game_type);
  void PrintGameName();
  void SetUpSnake();
  void SetUpTetris();
  void StartGame();

 protected:
  void keyPressEvent(QKeyEvent *event) override;
  void paintEvent(QPaintEvent *event) override;
  void ForcedUpdate();
  void UpdateView();
  void ExitHandler();

 private slots:
  void OnExitButtonClicked();

 private:
  QTimer *game_timer_;
  void UpdateGameState(Signal signal);
  Ui::GameForm *ui_;
  int game_type_ = 0;
  bool game_started_ = false;
  GameInfo game_info_;
  s21::Snake snake_;
  int **field_;
  GameState game_state_ = kStart;
  int time_ = 0;
};

#endif  // GAMEWINDOW_H
