#include "manche.h"
#include "ui_manche.h"

Manche::Manche(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Manche)
{
       // fenetre  de manche  du jeu cree avec qt disign
    this->setFixedSize(500,600);
    ui->setupUi(this);

    if(IaScore < PlayerScore){
        QMovie *gif = new QMovie(":/assets/93dx.gif");
        ui->label->setFixedSize(212,256);
        ui->label->setMovie(gif);
        ui->label->setScaledContents(true);
        ui->label_2->setText("Alors, c'est qui le boss ?\nVous avez gagné la manche");
        ui->label_2->setAlignment(Qt::AlignCenter);
        gif->start();
    }else{
        QMovie *gif = new QMovie(":/assets/93c5.gif");
        ui->label->setFixedSize(212,256);
        ui->label->setMovie(gif);
        ui->label->setScaledContents(true);
        ui->label_2->setText("Oupss Vous avez perdu la manche.\nMais la partie continue");
        ui->label_2->setAlignment(Qt::AlignCenter);
        gif->start();
    }

    connect(ui->pushButton,&QPushButton::clicked,this,[&](){
        if(nbrManche >= 1){
            ShowPage();
        };
        nbrManche--;
    });
}

void Manche::ShowPage(){
    Game *secondGamePage = new Game;
    secondGamePage->showMaximized();
    this->close();
    this->deleteLater();
}

Manche::~Manche()
{
    delete ui;
}
