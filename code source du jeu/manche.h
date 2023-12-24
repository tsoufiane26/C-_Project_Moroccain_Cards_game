#ifndef MANCHE_H
#define MANCHE_H

#include <QWidget>
#include <QMovie>
#include "Game.h"

namespace Ui {
class Manche;
}

class Manche : public QWidget
{
    Q_OBJECT

public:
    explicit Manche(QWidget *parent = nullptr);
    void ShowPage();
    ~Manche();

private:
    Ui::Manche *ui;
};

#endif // MANCHE_H
