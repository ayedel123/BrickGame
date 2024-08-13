#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    game_form = new GameForm();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_playTetrisButton_clicked()
{
    this->hide();
    game_form->show();
    game_form->SetGameType(0);
    game_form->PrintGameName();
    game_form->SetUpTetris();
}


void MainWindow::on_playSnakeButton_clicked()
{
    this->hide();
    game_form->show();
    game_form->SetGameType(1);
    game_form->PrintGameName();
    game_form->SetUpSnake();

}

