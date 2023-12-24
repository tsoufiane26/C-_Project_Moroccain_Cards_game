#include "endgame.h"
#include "ui_endgame.h"

EndGame::EndGame(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EndGame)
{
       // fenetre  fin du jeu cree avec qt disign
    ui->setupUi(this);
    if(PlayerScore > IaScore){
        QPixmap awardPixmap(":/assets/award.png");
        ui->label->setPixmap(awardPixmap.scaled(ui->label->size(), Qt::KeepAspectRatio));
        ui->label_2->setText("Félicitations, Vous avez gagné la partie !");
    }else{
        QPixmap iconPixmap(":/assets/icons8.png");
        ui->label->setPixmap(iconPixmap.scaled(ui->label->size(), Qt::KeepAspectRatio));
        ui->label_2->setText("Bien tenté, mais vous avez perdu !");
    }
    connect(ui->pushButton,&QPushButton::clicked,this,[&](){
        ShowPage();
    });

    connect(ui->pushButton_2,&QPushButton::clicked,this,[&](){
        this->close();
    });

}

void EndGame::ShowPage(){
    Level *newGame = new Level;
    newGame->show();
    this->close();
    IaScore = 0;
    PlayerScore = 0;
    LevelChoose = "";
    nbrManche = 3;
}

EndGame::~EndGame()
{
    delete ui;
}
