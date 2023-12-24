#ifndef ENDGAME_H
#define ENDGAME_H

#include <QWidget>
#include "utils.h"
#include "level.h"
namespace Ui {
class EndGame;
}

class EndGame : public QWidget
{
    Q_OBJECT

public:
    explicit EndGame(QWidget *parent = nullptr);
    void ShowPage();
    ~EndGame();

private:
    Ui::EndGame *ui;
};

#endif // ENDGAME_H
