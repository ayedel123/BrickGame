#include "mainwindow.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui_(new Ui::MainWindow) {
  ui_->setupUi(this);
  game_form_ = new GameForm();
  connect(game_form_, &GameForm::MainWindow, this, &MainWindow::show);
  connect(ui_->play_tetris_button, &QPushButton::clicked, this,
          &MainWindow::OnPlayTetrisButtonClicked);
  connect(ui_->play_snake_button, &QPushButton::clicked, this,
          &MainWindow::OnPlaySnakeButtonClicked);
  connect(ui_->exit_button, &QPushButton::clicked, this,
          &MainWindow::OnExitButtoClicked);

  QPixmap pm(":/images/res/2.png");

  ui_->img_label->setPixmap(pm);
  ui_->img_label->setScaledContents(true);
}

MainWindow::~MainWindow() { delete ui_; }

void MainWindow::OnPlayTetrisButtonClicked() {
  this->hide();
  game_form_->show();
  game_form_->SetGameType(0);
  game_form_->PrintGameName();
  game_form_->SetUpTetris();
  game_form_->StartGame();
}

void MainWindow::OnPlaySnakeButtonClicked() {
  this->hide();
  game_form_->show();
  game_form_->SetGameType(1);
  game_form_->PrintGameName();
  game_form_->SetUpSnake();
  game_form_->StartGame();
}

void MainWindow::OnExitButtoClicked() { close(); }
