#include "gamewindow.h"

#include <QVBoxLayout>

#include "ui_gamewindow.h"

GameForm::GameForm(QWidget *parent) : QWidget(parent), ui_(new Ui::GameForm) {
  ui_->setupUi(this);
  InitField(&field_, GAME_WINDOW_HEIGHT, GAME_WINDOW_WIDTH);
  ClearField(field_, GAME_WINDOW_HEIGHT, GAME_WINDOW_WIDTH);

  NextBrickWidget *myWidget = new NextBrickWidget(this);
  myWidget->game_info = &game_info_;

  ui_->next_brick_layout->addWidget(myWidget);

  game_timer_ = new QTimer(this);
  connect(game_timer_, &QTimer::timeout, this, &GameForm::UpdateCurrentState);
  connect(ui_->exit_button, &QPushButton::clicked, this,
          &GameForm::OnExitButtonClicked);
}

GameForm::~GameForm() { delete ui_; }

void GameForm::ForcedUpdate() {
  UpdateGameState(kNosig);
  if (game_state_ == kStart || game_state_ == kSpawn) {
    while (game_state_ != kMoving) UpdateGameState(kNosig);
  }
}

void GameForm::keyPressEvent(QKeyEvent *event) {
  Signal signal = GetSignalDesktop(event);
  UpdateGameState(signal);
  ForcedUpdate();
  UpdateView();
}

void GameForm::UpdateCurrentState() {
  if (game_started_) {
    if (game_type_ == 0) {
      UpdateGameState(kAction);
    } else if (game_type_ == 1) {
      UpdateGameState(snake_.last_signal);
    }
    ForcedUpdate();
    game_timer_->setInterval(game_info_.speed -
                             game_info_.level * game_info_.acceleration);
  }
  if (game_state_ == kExitState) {
    ExitHandler();
  }
}

void GameForm::UpdateGameState(Signal signal) {
  if (game_type_ == 0) {
    TetrisUpdateCurrentState(&game_info_, &game_state_, signal);
  } else if (game_type_ == 1) {
    SnakeUpdateCurrentState(snake_, &game_state_, signal);
  }
  UpdateView();
}

void GameForm::StartGame() {
  if (!game_started_) {
    game_state_ = kStart;
    UpdateGameState(kStartSig);
    game_timer_->start(game_info_.speed -
                       game_info_.level * game_info_.acceleration);
    game_started_ = true;
    UpdateView();
  }
}

void GameForm::PrintGameName() {
  if (game_type_ == 0) {
    ui_->game_name_label->setText("TETRIS");
  } else if (game_type_ == 1) {
    ui_->game_name_label->setText("SNAKE");
  }
}

void GameForm::UpdateView() {
  ui_->lvl_label->setText(QString::number(game_info_.level) + " lvl");
  ui_->score_label->setText("Your score: " +
                            QString::number(game_info_.points));
  ui_->record_label->setText("Record: " +
                             QString::number(game_info_.high_score));
  update();
}

void GameForm::paintEvent(QPaintEvent *event) {
  Q_UNUSED(event);
  QPainter painter(this);

  painter.setPen(QPen(Qt::white, 1, Qt::SolidLine, Qt::FlatCap));
  painter.setBrush(GetBrush(0));
  int start_x = 40;
  int start_y = 40;
  int cell_size = 40;
  if (field_) {
    for (int i = 0; i < game_info_.win_info.height; i++) {
      for (int j = 0; j < game_info_.win_info.width; j++) {
        painter.setBrush(GetBrush(field_[i][j]));

        painter.drawRect(start_x + j * cell_size, start_y + i * cell_size,
                         cell_size, cell_size);
        painter.setBrush(GetBrush(0));
      }
    }
  }
}

void GameForm::SetGameType(int game_type) { game_type_ = game_type; }

void GameForm::SetUpSnake() {
  snake_ = s21::Snake(&game_info_, field_);
  snake_.Clear();
}

void GameForm::SetUpTetris() { TetrisSetUp(&game_info_, field_); }

void GameForm::ExitHandler() {
  UpdateGameState(kExit);
  game_state_ = kGameOver;
  game_started_ = false;
  this->close();

  emit MainWindow();
}

void GameForm::OnExitButtonClicked() { ExitHandler(); }
