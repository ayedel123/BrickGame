#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QWidget>
#include <QKeyEvent>
#include <QPainter>
#include "../get_signal_desctop/get_signal_desktop.h"
#include "../../../brick_game/tetris/tetris.h"
#include  "../../../brick_game/snake/snake.h"
#include  "../../../brick_game/snake/snake_game_loop.h"


namespace Ui {
class GameForm;
}

class GameForm : public QWidget
{
    Q_OBJECT

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

private:
    Ui::GameForm *ui;
    int game_type_ = 0;
    bool game_started_ = false;
    GameInfo game_info_;
    s21::Snake snake_;
    int **field_;
    GameState game_state_=kStart;



};

#endif // GAMEWINDOW_H
