#include "gameover.h"
#include <QLabel>
#include <QVBoxLayout>
#include<QHBoxLayout>

GameOver::GameOver(QWidget *parent)
    : QMainWindow{parent}
{
    QWidget *window = new QWidget(this);
    QLabel *text = new QLabel("Game Over");
    QVBoxLayout *box = new QVBoxLayout(this);
    text->setStyleSheet("color: black;font-size:20px");
    box->addWidget(text);
    box->setAlignment(Qt::AlignCenter);
    setCentralWidget(window);


}
