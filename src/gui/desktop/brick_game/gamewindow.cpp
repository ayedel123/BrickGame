#include "gamewindow.h"
#include "ui_gamewindow.h"

GameForm::GameForm(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::GameForm)
{
    ui->setupUi(this);
    InitField(&field_, GAME_WINDOW_HEIGHT, GAME_WINDOW_WIDTH);
    ClearField(field_, GAME_WINDOW_HEIGHT, GAME_WINDOW_WIDTH);


}

GameForm::~GameForm()
{
    delete ui;
}



void GameForm::keyPressEvent(QKeyEvent *event){
    Signal signal = GetSignalDesktop(event);
    uint sign = (uint)signal;
    ui->label->setText("sign"+QString::number(sign)+"");



}

void GameForm::StartGame(){
    if(!game_started_){
        game_state_ = kStart;
        if(game_type_==0){
            TetrisUpdateCurrentState(game_info_,&game_state_, kNosig);
        }else if(game_type_==1){
            SnakeUpdateCurrentState(snake_,&game_state_, kNosig);
        }
    }
}

void GameForm::PrintGameName(){
    if(game_type_==0){
        ui->game_name_label->setText("TETRIS");
    }else if(game_type_==1){
        ui->game_name_label->setText("SNAKE");
    }
}

void GameForm::paintEvent(QPaintEvent *event){
    Q_UNUSED(event);
    QPainter painter(this); // Создаём объект отрисовщика
    // Устанавливаем кисть абриса
    painter.setPen(QPen(Qt::white, 1, Qt::SolidLine, Qt::FlatCap));
    painter.setBrush(QBrush(Qt::black, Qt::SolidPattern));
    int start_x = 40;
    int start_y = 40;
    int cell_size = 40;
    if(field_){
        for(int i =0;i<game_info_.win_info.height;i++){
            for(int j=0;j<game_info_.win_info.width;j++){
                if(field_[i][j]==1){
                    painter.setBrush(QBrush(Qt::red, Qt::SolidPattern));
                }else if(field_[i][j]==2){
                    painter.setBrush(QBrush(Qt::green, Qt::SolidPattern));
                }else if(field_[i][j]!=0){
                    painter.setBrush(QBrush(Qt::white, Qt::SolidPattern));
                }


                painter.drawRect(start_x+j*cell_size,start_y+i*cell_size,cell_size,cell_size);
            }
        }
    }

}

void GameForm::SetGameType(int game_type){
    game_type_ = game_type;
}

void GameForm::SetUpSnake(){
    TetrisSetUp(&game_info_, field_);
}

void GameForm::SetUpTetris(){
    snake_ = s21::Snake(&game_info_, field_);
}

