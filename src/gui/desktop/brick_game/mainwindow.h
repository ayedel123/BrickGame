#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "gamewindow.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_playTetrisButton_clicked();

    void on_playSnakeButton_clicked();

private:
    Ui::MainWindow *ui;
    GameForm *game_form;
};
#endif // MAINWINDOW_H
