#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    // fenetre  regle du jeu cree avec qt disign
    this->setFixedHeight(700);
    ui->setupUi(this);

}

Dialog::~Dialog()
{
    delete ui;
}
