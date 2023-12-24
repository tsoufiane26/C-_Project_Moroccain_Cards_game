#include "level.h"
#include "ui_level.h"

Level::Level(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Level)
{
       // fenetre  de niveau du jeu cree avec qt disign
    setFixedSize(380,239);
    ui->setupUi(this);
    connect(ui->facile_btn, &QPushButton::clicked,this,[&](){
        LevelChoose = "facile";
        ShowGame();
        qDebug() << LevelChoose;
    });

    connect(ui->dif_btn, &QPushButton::clicked,this,[&](){
        LevelChoose = "difficile";
        ShowGame();
        qDebug() << LevelChoose;
    });

}

void Level::ShowGame(){
    Game *gamePage = new Game;
    gamePage->showMaximized();
    this->close();
}

Level::~Level()
{
    delete ui;
}


