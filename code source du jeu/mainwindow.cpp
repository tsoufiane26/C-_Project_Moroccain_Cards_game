#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include<QPushButton>
#include<QInputDialog>
#include <QCheckBox>
#include <QMessageBox>
#include <Game.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)

{
         this->setStyleSheet("background-color :#268335");
         QWidget *MyWindow = new QWidget (this);
         rulePage = new Dialog;
         levelPage = new Level;
         QVBoxLayout *Container = new QVBoxLayout(MyWindow);
         QHBoxLayout *ButtunBox = new QHBoxLayout(MyWindow);
         QFrame *Branding = new QFrame ;
         QFrame *BrandingCard = new QFrame;
         QPushButton *Rules = new QPushButton("Regle");
         QPushButton *level = new QPushButton("Jouer");
         QLabel *NameDos = new QLabel ("Dos");
         NameDos->setStyleSheet("color:white;font-size:40px");
         Container->addWidget(Branding,0,Qt::AlignCenter);
         Container->addWidget(NameDos,0,Qt::AlignCenter);

         Container->addWidget(BrandingCard,0,Qt::AlignCenter);
         Container->addSpacing(20);
         Container->addLayout(ButtunBox);
         ButtunBox->setAlignment(Qt::AlignCenter);
         ButtunBox->addWidget(Rules);
         ButtunBox->addSpacing(40);
         ButtunBox->addWidget(level);
         QString BrandingPath = QCoreApplication::applicationDirPath() +"/images/branding.png";
         QString BrandingCardPath = QCoreApplication::applicationDirPath() +"/images/dos.png";
         Branding->setStyleSheet("background-image:url("+BrandingPath+");");
         BrandingCard->setStyleSheet("background-image:url("+BrandingCardPath+");");

         Branding->setFixedSize(366,100);
         BrandingCard->setFixedSize(586,330);
         Rules->setFixedSize(150 ,50);
         level->setFixedSize(150,50);
         Rules->setStyleSheet("QPushButton {"
                              "    background-color: white;"
                              "    color: black;"
                              "    border-radius: 15px;"
                              "    border: none;"
                              "}"

                               "QPushButton:hover {"
                              "    background-color: #F0ED4F;"

                              "}"

                              );
         level->setStyleSheet("QPushButton {"
                                 "    background-color: white;"
                                 "    color: black;"
                                 "    border-radius: 15px;"
                                 "    border: none;"
                                 "}"

                                  "QPushButton:hover {"
                                 "    background-color: #F0ED4F;"

                                 "}"

                                 );

         connect(level, &QPushButton::clicked, this,[=](){
             levelPage->show();
             this->close();
         });
         connect(Rules, &QPushButton::clicked, this, [&](){
             rulePage->show();
         });

         setCentralWidget(MyWindow);
}

MainWindow::~MainWindow()
{
         delete levelPage;
         delete rulePage;
}

