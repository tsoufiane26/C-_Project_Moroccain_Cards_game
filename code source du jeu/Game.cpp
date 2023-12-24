// Game.cpp
#include "Game.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPropertyAnimation>
#include <QPixmap>
#include <QGuiApplication>
#include <QCoreApplication>
#include <QScreen>
#include <QRect>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QGuiApplication>
#include <QPushButton>
#include <QFrame>
#include <algorithm>
#include <random>
#include <gameover.h>

Game::Game(QWidget *parent)
    : QMainWindow(parent)
{
    this->setStyleSheet("background-color :#268335");
    QWidget* Window = new QWidget(this);
    nbrCartePlayer = new QLabel(this);
    nbrCarteIa = new QLabel(this);
    QScreen *Screen = QGuiApplication::primaryScreen();
    QRect  Cadre = Screen->geometry();
    ScreenHeight = Cadre.height();
    ScreenWidth =  Cadre.width();
    QString  ImageBack = QCoreApplication::applicationDirPath() +"/images/back.png";

    QWidget *ScoreBox = new QWidget(Window);
    QHBoxLayout *CentralBox = new QHBoxLayout (Window);
    QHBoxLayout *CardTypeBox = new QHBoxLayout (Window);
    CardStatic = new QFrame;
    CardTypeImage = new QFrame;
    CardMiddleImage = new QFrame;
    CardTypeImage->setStyleSheet("background-color:white");
    CardTypeImage->setFixedSize(50,50);
    CardStatic->setStyleSheet("background-image:url("+ImageBack+");");

    CardMiddleImage->setStyleSheet("background-color:blue");
    CardMiddleImage->setFixedSize(90,135);
    CardStatic->setFixedSize(90,135);




    CentralBox->setAlignment(Qt::AlignCenter);
    CentralBox->addLayout(CardTypeBox,6);
    CardTypeBox->setAlignment(Qt::AlignRight);
    CentralBox->addWidget(CardStatic,4,Qt::AlignCenter);

    CardTypeBox->addWidget(CardTypeImage);
    CardTypeBox->addSpacing(10);
    CardTypeBox->addWidget(CardMiddleImage);




    ScoreBox->setStyleSheet("border:1px solid white;border-radius:20px");
    ScoreBox->setFixedSize(150,30);
    ScoreBanner = new QLabel(ScoreBox);
    ScoreBanner->setStyleSheet("border:none;outline:none;color:white");
    ScoreBanner->move(60,10);
    ScoreBanner->setText("IA " + QString::number(IaScore) + " - " + QString::number(PlayerScore) + " Player");

    int positionBoxScoreX= ScreenWidth/2 - 75;
    ScoreBox->move(QPoint(positionBoxScoreX,10));
    qDebug()<<"longeur de l ecran  : "<<ScreenHeight;
    qDebug()<<"Largeur de l ecan: "<<ScreenWidth;






    SetPosition(true);
    SetPosition(false);
    // definition proprieter des carte nombre de carte Ia et utilisateur

    QFont policeGras;
    policeGras.setBold(true);
    nbrCarteIa->setGeometry(600,220,20,20);
    nbrCarteIa->setAlignment(Qt::AlignCenter);
    nbrCarteIa->setFont(policeGras);
    nbrCarteIa->setStyleSheet("background-color: white;"
                              "color: red;");
    nbrCartePlayer->setGeometry(600,500,20,20);
    nbrCartePlayer->setAlignment(Qt::AlignCenter);
    nbrCartePlayer->setFont(policeGras);
    nbrCartePlayer->setStyleSheet("background-color: white;"
                              "color: red;");

    //initialiser la liste des carte
    InitCard();
    //distribuer les 5 carte a l'ia et a l'utilisateur
    FirstAnimation(true);
    FirstAnimation(false);


    setCentralWidget(Window);


}

void Game::SetPosition(bool Top ) {
    /* cette fonction sert a definir les positon des carte il y a 11 place de carte disponible pour l'ia et aussi
        11 place de carte possible pour l'utilisateur */
    const int cardWidth = 90;
    const int cardHeight= 90;

    const int cardSpacing = 10;

    int startX = (ScreenWidth - (10 * cardWidth + 9 * cardSpacing)) / 2;



    // Ajoute les positions des cartes
    for (int i = 0; i < 11; ++i) {
        if(Top){
            //calculer la position des cartes en haut de l'ecran
            QPoint cardPositionTop(startX + i * (cardWidth + cardSpacing), 50);  // Ajustez la coordonnée Y selon vos besoins
            cardPositionsTop.push_back(cardPositionTop);
        }else{
            //calculer la position des cartes en bas de l'ecran
            QPoint cardPositionBottom(startX + i * (cardWidth + cardSpacing), ScreenHeight -150 -cardHeight);  // Ajustez la coordonnée Y selon vos besoins
            cardPositionsBottom.push_back(cardPositionBottom);
        }


    }
    qDebug()<<"liste des carte "<<cardPositionsTop;
    qDebug()<<"liste des carte "<<cardPositionsBottom;

}
void Game::FirstAnimation(bool Direction){
    /* Fonction appelée pour effectuer la toute première animation lors du
     * lancement du jeu. Elle distribue 5 cartes à l'IA et 5 cartes à l'utilisateur. */

    Card *Card0 = new Card;
    std::vector<QPoint> PositionList = Direction ? cardPositionsTop :cardPositionsBottom;



    QPropertyAnimation *animation1 = new QPropertyAnimation(Card0,"pos");
    animation1->setDuration(500);
    animation1->setStartValue(CardStatic->pos());
    animation1->setEndValue(QPoint(0,0));
    animation1->start();
    connect(animation1 , &QPropertyAnimation::finished,this,[this,PositionList,Direction]{
        int size = ListOfCard.size();
        QPropertyAnimation *animation1 = new QPropertyAnimation(ListOfCard[size-1],"pos");
        animation1->setDuration(1000);
        animation1->setStartValue(CardStatic->pos());
        animation1->setEndValue(PositionList[5]);
        animation1->start();

        QPropertyAnimation *animation2 = new QPropertyAnimation(ListOfCard[size-2],"pos");
        animation2->setDuration(1000);
        animation2->setStartValue(CardStatic->pos());
        animation2->setEndValue(PositionList[5+1]);
        animation2->start();
        QPropertyAnimation *animation3 = new QPropertyAnimation(ListOfCard[size-3],"pos");
        animation3->setDuration(1000);
        animation3->setStartValue(CardStatic->pos());
        animation3->setEndValue(PositionList[5+2]);
        animation3->start();
        QPropertyAnimation *animation4 = new QPropertyAnimation(ListOfCard[size-4],"pos");
        animation4->setDuration(1000);
        animation4->setStartValue(CardStatic->pos());
        animation4->setEndValue(PositionList[5-1]);

        animation4->start();
        QPropertyAnimation *animation5 = new QPropertyAnimation(ListOfCard[size-5],"pos");
        animation5->setDuration(1000);
        animation5->setStartValue(CardStatic->pos());
        animation5->setEndValue(PositionList[5-2]);

        animation5->start();

        if(Direction){
            int size = ListOfCard.size();
            //cacher la liste de cartes de l'IA
            ListOfCard[size-1]->setStyleSheet("background-image:url("+QGuiApplication::applicationDirPath()+"/images/back.png);");
            ListOfCard[size-2]->setStyleSheet("background-image:url("+QGuiApplication::applicationDirPath()+"/images/back.png);");
            ListOfCard[size-3]->setStyleSheet("background-image:url("+QGuiApplication::applicationDirPath()+"/images/back.png);");
            ListOfCard[size-4]->setStyleSheet("background-image:url("+QGuiApplication::applicationDirPath()+"/images/back.png);");
            ListOfCard[size-5]->setStyleSheet("background-image:url("+QGuiApplication::applicationDirPath()+"/images/back.png);");

            IaCard.push_back(ListOfCard[size-1]);
            IaCard.push_back(ListOfCard[size-2]);
            IaCard.push_back(ListOfCard[size-3]);
            IaCard.push_back(ListOfCard[size-4]);
            IaCard.push_back(ListOfCard[size-5]);
            PositionCompteurIa = 3;
            nbrCarteIa->setText(QString::number(IaCard.size()));

        }else{

            int size = ListOfCard.size();
            UserCard.push_back(ListOfCard[size-1]);
            UserCard.push_back(ListOfCard[size-2]);
            UserCard.push_back(ListOfCard[size-3]);
            UserCard.push_back(ListOfCard[size-4]);
            UserCard.push_back(ListOfCard[size-5]);
            PositionCompteurUser = 3;
            nbrCartePlayer->setText(QString::number(UserCard.size()));
            UserPlayer();


        }
        //on suprime les  carte prise de la liste
        ListOfCard.pop_back();
        ListOfCard.pop_back();
        ListOfCard.pop_back();
        ListOfCard.pop_back();
        ListOfCard.pop_back();

    });


}
void Game ::UserPlayer(){
    /* Fonction qui sert à connecter les clics de l'utilisateur
     * sur les différentes cartes qu'il a. */

    int size = UserCard.size();

    qDebug()<<"la taille est "<<size;
    for(int i = 0 ;i< size;i++){
        connect(UserCard[i], &QPushButton::clicked,this,[this,i]{
          //code a executer lors du click sur une carte
            if(FisrtPlay){
                Animation(UserCard[i] , true,i );}
            else{

                 //code evec un bug  *
                int index = CanUserPlay();
                if(index != -1){
                    std::vector<int> liste = CanUserPlayIndex();
                    qDebug()<<"liste jouable "<<liste;
                    qDebug()<<"index jouer "<<i;
                    int value = liste.size();
                    for(int elt = 0 ; elt<value;elt++){
                        if(liste[elt] == i){
                            Animation(UserCard[i] , true,i );
                        }
                    }
                /*// code sans bug main une seule carte clickable par le jour que le programe determine automatiquement
                int index = CanUserPlay();
                if(index != -1){
                    //verifier si l'index appartient a la liste de carte jouer

                    if(index == i){
                            Animation(UserCard[i] , true,i );
                        }
                }*/

            }



        }});
    }

}
void Game::Player(){
    /* Fonction qui contrôle les actions d'un utilisateur, notamment
     * s'il doit prendre une carte, et aussi pour connecter les nouvelles
     * cartes jouées par l'utilisateur à sa liste de cartes. */


    if(CanUserPlay()!= -1){
      UserPlayer();
    }else{
      TakeCard(true);


    }
}
void Game::Animation(Card *card, bool iaTurn,int index){

    /* Fonction qui sert à effectuer les animations pour les cartes
     * jouées par l'utilisateur ou par l'IA. */
    //sur elevee la carte clicker
    card->raise();
    //changer l'arrier plan de la carte pour les carte de l'ia pour les rendre visible
    card->setStyleSheet("background-image:url("+card->CardImage+");");

    QPropertyAnimation *animation = new QPropertyAnimation(card,"pos");
    animation->setDuration(1500);

    if(FisrtPlay){
        //code pour le premier tour de jeu
        PlayingCardNumber = card->CardNumber;
        PlayingCardType = card->Type;
        FisrtPlay = false;
    }

    CardTypeImage->setStyleSheet("background-image:url("+card->CardTypeImage+");");
    animation->setEndValue(CardMiddleImage->pos());
    QPoint position = card->pos();

    animation->start();

    connect(animation,&QPropertyAnimation::finished,this,[this,iaTurn,card,index,position]{
        PlayingCardNumber = card->CardNumber;
        PlayingCardType = card->Type;
        if(iaTurn){
            RemoveCardAtIndex(UserCard,index,iaTurn);
            UserPlayingLastPoint.push_back(position);
            nbrCartePlayer->setText(QString::number(UserCard.size()));

        }else{
            RemoveCardAtIndex(IaCard,index,iaTurn);
            IaPlayingLastPoint.push_back(position);
            nbrCarteIa->setText(QString::number(IaCard.size()));
            qDebug()<<"Iacard    "<<IaCard.size();
            qDebug()<<"animation   "<<UserPlayingLastPoint;

        }
        if(IaCard.empty() ){
            //l'ia gagne si il na plus de carte
            qDebug()<<"ia a gagner";
            if(LevelChoose == "facile"){
                IaScore++;
            }else{
                IaScore+=2;
            }
            qDebug() << "ia score: " << IaScore << " Player score: " << PlayerScore;
            if(nbrManche > 1){
                //affichage de la manche suivante
                showManche();
            }else{
                //affichage de la fin du jeu
                showEnd();
            }
        }else if(UserCard.empty()){
            //jouer gagne si il na plus de carte
             qDebug()<<"joueur  a gagner";
            PlayerScore++;
             qDebug() << "ia score: " << IaScore << " Player score: " << PlayerScore;
            if(nbrManche > 1){
                showManche();
            }else{
                showEnd();
            }
        }

        if(iaTurn){
            //appeler la fonction de l'ia pour son tour
            IaPlayer();


        }else{
            //appeler la fonction de l'utilisateur (connection des click pour les carte)
           Player();
        }


    });

}
void Game ::IaPlayer(){
    /* Fonction qui contrôle les actions de l'IA, notamment le
     * fait qu'elle prenne une carte ou la sélection automatique
     * des cartes que l'IA doit jouer. */

    int index =CanIaPlay();
    if(index != -1){
        Animation(IaCard[index],false,index);

    }else{
        qDebug()<<"je prend une carte ";
        TakeCard(false);

    }

}

int Game ::CanIaPlay(){
    /* Fonction qui sert à déterminer si l'IA peut jouer ou non.
     *  Elle renvoie l'index de la carte qui peut être jouée, sinon
     *  elle renvoie -1, ce qui signifie qu'aucune carte n'a été trouvée. */

    int size = IaCard.size();
    for(int i = 0 ;i< size ; i++){
        if(IaCard[i]->Type == PlayingCardType || IaCard[i]->CardNumber == PlayingCardNumber){
            return i;
        }
    }
    return -1;
}
int Game::CanUserPlay(){
    /* Fonction qui sert à déterminer si l'utilisateur  peut jouer ou non.
     *  Elle renvoie l'index de la carte qui peut être jouée, sinon
     *  elle renvoie -1, ce qui signifie qu'aucune carte n'a été trouvée. */

    int size = UserCard.size();
    for(int i = 0 ;i< size ; i++){
        if(UserCard[i]->Type == PlayingCardType || UserCard[i]->CardNumber == PlayingCardNumber){
            return i;
        }
    }
    return -1;
}
std::vector<int> Game::CanUserPlayIndex(){
    /* Fonction qui sert à calculer la liste des index jouable par l'utilisateur
     *  peut jouer ou non.
     *  Elle renvoie une liste d'index des cartes qui peuve être jouée*/
    int size = UserCard.size();
    std::vector<int> liste;
    for(int i = 0 ;i< size ; i++){
        if(UserCard[i]->Type == PlayingCardType || UserCard[i]->CardNumber == PlayingCardNumber){
         liste.push_back(i);
        }
    }
     return liste;

}
void Game::InitCard() {
    /* Fonction qui crée et initialise la liste des 40 cartes. */

    // Liste des numéros de carte
    std::vector<int> cardNumbers = {1, 2, 3, 4, 5, 6, 7, 10, 11, 12};
    std::vector<QString> CardType = {"gold","stick","sword","flat"};

    // Indice pour suivre la position actuelle dans la liste des numéros
    int index = 0;
    int compter = 1 ;

    // Répétition des numéros de carte jusqu'à la fin de la liste des 40 images
    int typeindex = -1 ;
    while (ListOfCard.size() < 40) {
        if((compter- 1) %10 == 0){
            index = 0;
            typeindex++;

        }
        int cardNumber = cardNumbers[index];

        Card* newCard = new Card(this);
        newCard->setFixedSize(90,135);
        newCard->move(-200,-200);
        newCard->CardNumber = cardNumber;
        newCard->CardImage = QCoreApplication::applicationDirPath() + QString("/images/%1.png").arg(compter);

        newCard->CardTypeImage = QCoreApplication::applicationDirPath()+"/images/" + CardType[typeindex] +".png";
        newCard->Type = CardType[typeindex];
        newCard->setStyleSheet("background-image:url("+newCard->CardImage+");");

        ListOfCard.push_back(newCard);

        // Incrémente l'index et réinitialise à 0 s'il atteint la fin de la liste des numéros

        index++;
        compter++;
    }

    for (int i = 0; i < 40; i++) {
        qDebug() << "image " << ListOfCard[i]->Type;
        qDebug() << "number " << ListOfCard[i]->CardNumber;
    }
    //melanger les carte de la liste
    ShuffleCards();
}

void Game::animateCardMovement(Card *card, const QPointF &startPos, const QPointF &endPos,bool moveia) {

    /* Fonction qui sert à distribuer les cartes à l'utilisateur ou à l'IA
     *  lorsqu'ils sont dans l'incapacité de jouer. */

    QPropertyAnimation *animation = new QPropertyAnimation(card, "pos");
    animation->setDuration(1500);
    card->raise();
    animation->setStartValue(startPos);
    animation->setEndValue(endPos);
    animation->start();
    connect(animation,&QPropertyAnimation::finished,this,[this,moveia]{
        //fin de la prise de carte
        if(moveia){
            //dire a l'utilisateur  de jouer
            Player();
        }else{
            //dire a l'ia de jouer
            IaPlayer();
        }
    });
}

void Game::moveCardToUser(Card *card,bool moveia) {
    /* Fonction qui sert à distribuer les cartes à l'utilisateur  lorsqu'il
     * ne peut pas jouer. Elle calcule également la position adaptée pour
     * placer la carte distribuée. */
      //si la liste des ancien point (position des carte devant l'utilisateur) jouer par L'Ia n'est vide
    if (!UserPlayingLastPoint.empty()) {
        int size = UserPlayingLastPoint.size() ;
        animateCardMovement(card, CardStatic->pos(), UserPlayingLastPoint[size-1],moveia);
        UserPlayingLastPoint.pop_back();
    } else if (PositionCompteurUser <= 5) {
        // Sinon, on vérifie la position à l'extérieur (car il y a des cartes dans l'espace entre 5 + PositionCompteurIa et 5 - PositionCompteurIa).

        QPointF endPos = MoveCardToUserLeft ? cardPositionsBottom[5 + PositionCompteurUser]
                                            : cardPositionsBottom[5 - PositionCompteurUser];
        animateCardMovement(card, CardStatic->pos(), endPos,moveia);


        if(!MoveCardToUserLeft){
            //augmenter le compterur des position car la position a ete occuper par une carte
            PositionCompteurUser++;
        }  // distribuer dans l'autre cote pour la prochaine fois
            MoveCardToUserLeft = !MoveCardToUserLeft;
    }
       //ajouter la nouvelle carte au carte de l'Ia
    UserCard.push_back(card);
    //mise a jour du click
    UserPlayer();
}

void Game::moveCardToAI(Card *card,bool moveia) {
    /* Fonction qui sert à distribuer les cartes à l'Ia lorsqu'il
     * ne peut pas jouer. Elle calcule également la position adaptée pour
     * placer la carte distribuée. */

    //rendre les carte de l'ia visible lorsqu'il joue une carte
    card->setStyleSheet("background-image:url("+QGuiApplication::applicationDirPath()+"/images/back.png);");
   //si la liste des ancien point (position des carte devant l'IA)jouer par L'Ia n'est vide
    if (!IaPlayingLastPoint.empty()) {
        int size = IaPlayingLastPoint.size() ;
        animateCardMovement(card, CardStatic->pos(), IaPlayingLastPoint[size-1],moveia);
        IaPlayingLastPoint.pop_back();
    } else if (PositionCompteurIa <= 5) {
    // Sinon, on vérifie la position à l'extérieur (car il y a des cartes dans l'espace entre 5 + PositionCompteurIa et 5 - PositionCompteurIa).
        QPointF endPos = MoveCardToIaLeft ? cardPositionsTop[5 + PositionCompteurIa]
                                          : cardPositionsTop[5 - PositionCompteurIa];
        animateCardMovement(card, CardStatic->pos(), endPos,moveia);



        if(!MoveCardToIaLeft){
            //augmenter le compterur des position car la position a ete occuper par une carte
            PositionCompteurIa++;
        }
        //bouger la carte a la vers l'autre coter lors du prochain appel de la fonction
            MoveCardToIaLeft = !MoveCardToIaLeft;
    }
    //ajouter la nouvelle carte au carte de l'Ia
    IaCard.push_back(card);
}

void Game::TakeCard(bool IsUser) {
    /*fonction pour donne une nouvelle carte a l'utilisateur ou a l'IA*/
    int size = ListOfCard.size();
    //verifier si la liste des 40 carte est vide si c'est le cas le jeu est terminer
    if(size != 0){
        Card *card = ListOfCard[size - 1];
        ListOfCard.pop_back();

        if (IsUser) {
            qDebug()<<"je prend une carte IA ";
            moveCardToUser(card,false);
            //mise a jour nombre de carte
            nbrCartePlayer->setText(QString::number(UserCard.size()));

        } else {
            qDebug()<<"je prend une carte User  ";

            moveCardToAI(card,true);
            nbrCarteIa->setText(QString::number(IaCard.size()));
        }
    }else{
        int scoreIa = IaCard.size();
        int scoreUser = UserCard.size();
        if(scoreIa > scoreUser){
            qDebug()<<"ia a gagner la manche";
        }else if(scoreIa == scoreUser){
            qDebug()<<"match null";
        }else{
            qDebug()<<"joueur a gagner la partie";
        }
    }

}

void Game::RemoveCardAtIndex(std::vector<Card*>& cardVector, int index,bool IsUser) {
    /*fonction qui supprime un elemet de la liste de carte de l'utilisateur ou de l'ia*/

    int size = cardVector.size();
    if (index >= 0 && index < size) {

        cardVector.erase(cardVector.begin() + index);
        if (IsUser){
            //mise a jour des connections des clik de l'utilisateur
            UserPlayer();
        }

    } else {
        // Gérez le cas où l'index est invalide (en dehors des limites du vecteur)
        qDebug() << "L'index spécifié n'est pas valide.";
    }
}
void Game::ShuffleCards() {
    // Utilisez un moteur de nombre aléatoire pour le mélange
    std::random_device rd;
    std::default_random_engine rng(rd());

    // Utilisez std::shuffle pour mélanger la liste des cartes
    std::shuffle(ListOfCard.begin(), ListOfCard.end(), rng);

    // Affichez la nouvelle séquence après le mélange
    qDebug() << "Après le mélange :";
    for (int i = 0; i < 40; i++) {
        qDebug() << "image " << ListOfCard[i]->Type;
        qDebug() << "number " << ListOfCard[i]->CardNumber;
    }
}

void Game::CardActivation(bool activation){
    /* Fonction pour désactiver et activer  les cartes de l'utilisateur,
     * notamment lors que l'IA joue. L'utilisateur ne doit pas
     * avoir la possibilité de jouer. */

    int size = UserCard.size();
    for(int i = 0 ; i<size ; i++){
        UserCard[i]->setEnabled(activation);
    }

}

void Game::showEnd()
{
    // fonction pour afficher la fenetre de fin du jeu (cree par QT disign)
    EndGame *EndPage = new EndGame;
    EndPage->show();
    this->close();
    this->deleteLater();
}

void Game::showManche(){
    // fonction pour afficher la fenetre de Manche du jeu (cree par QT disign)
    Manche *manchePage = new Manche;
    manchePage->show();
    this->close();
    this->deleteLater();
}

Game::~Game(){
    // Supprimer les éléments alloués dynamiquement.
    delete nbrCarteIa;
    delete nbrCartePlayer;
    delete ScoreBanner;
}


