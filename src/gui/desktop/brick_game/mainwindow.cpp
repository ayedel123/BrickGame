#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    game_form = new GameForm();
    connect(game_form, &GameForm::MainWindow, this, &MainWindow::show);
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
    game_form->StartGame();
}


void MainWindow::on_playSnakeButton_clicked()
{
    this->hide();
    game_form->show();
    game_form->SetGameType(1);
    game_form->PrintGameName();
    game_form->SetUpSnake();
    game_form->StartGame();

}

