#ifndef LEVEL_H
#define LEVEL_H

#include <QWidget>
#include "Game.h"
#include "utils.h"

namespace Ui {
class Level;
}

class Level : public QWidget
{
    Q_OBJECT
public:
    explicit Level(QWidget *parent = nullptr);
    void ShowGame();
    ~Level();
private:
    Ui::Level *ui;
};
#endif // LEVEL_H
