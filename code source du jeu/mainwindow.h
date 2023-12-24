#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "dialog.h"
#include "level.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /*void showGame();
    void ShowRules();
    void ShowLevel();*/
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    Level *levelPage;
    Dialog *rulePage;

};
#endif // MAINWINDOW_H
