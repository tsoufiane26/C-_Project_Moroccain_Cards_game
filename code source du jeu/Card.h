#ifndef CARD_H
#define CARD_H

#include <QPushButton>
#include <QWidget>
class Card :public QPushButton
{
    public:
        Card(QWidget *parent = nullptr);
        int CardNumber ;
        QString CardImage;
        QString CardTypeImage;
        QString Type;


};

#endif // CARD_H
