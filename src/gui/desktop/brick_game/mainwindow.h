#ifndef CPP3_BRICKGAME_V2_0_1_SRC_GUI_DESKTOP_BRICK_GAME_MAIN_WINDOW_H_
#define CPP3_BRICKGAME_V2_0_1_SRC_GUI_DESKTOP_BRICK_GAME_MAIN_WINDOW_H_

#include <QMainWindow>
#include <QPixmap>

#include "gamewindow.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private slots:

  void on_playTetrisButton_clicked();

  void on_playSnakeButton_clicked();

  void on_exitButto_clicked();

 private:
  Ui::MainWindow *ui;
  GameForm *game_form;
};
#endif  // MAINWINDOW_H
