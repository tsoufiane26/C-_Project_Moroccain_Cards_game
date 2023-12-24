#ifndef GAME_H
#define GAME_H

#include "utils.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPropertyAnimation>
#include <QPixmap>
#include <QMainWindow>
#include <Qpoint>
#include <QLabel>
#include <Card.h>
#include <QFrame>
#include "endgame.h"
#include "manche.h"

class Game : public QMainWindow
{
    Q_OBJECT
public:
    Game(QWidget *parent = nullptr);
    void SetPosition(bool Top);
    void FirstAnimation();
    void InitCard();
    void FirstAnimation(bool Direction);
    void UserPlayer();
    void IaPlayer();
    void Animation(Card *card, bool iaTurn,int index);
    void  ShuffleCards();
    int CanUserPlay();
    int CanIaPlay();
    void RemoveCardAtIndex(std::vector<Card*>& cardVector, int index,bool IsUser);
    void TakeCard(bool IsUser);
    void moveCardToAI(Card *card,bool moveia);
    void moveCardToUser(Card *card,bool moveia);
    void animateCardMovement(Card *card, const QPointF &startPos, const QPointF &endPos,bool moveia);
    void CardActivation(bool activation);
    void  Player();
    std::vector<int> CanUserPlayIndex();
    void showEnd();
    void showManche();
    ~Game();

private:
    int ScreenHeight ;
    int ScreenWidth ;
    std::vector<QPoint> cardPositionsTop;//attribut contenant les coordonne pour la position des carte en haut de l'ecran
    std::vector<QPoint> cardPositionsBottom;//attribut contenant les coordonne pour la position des carte en bas de l'ecran
    std::vector<Card*> UserCard;//liste des carte de l'utilisateur
    std::vector<Card*> IaCard;//liste des carte de L'Ia
    std::vector<Card*> ListOfCard;//liste des 40 carte du jeu
    // definition de frame (image )de l ecran
    QFrame *CardStatic;
    QFrame *CardTypeImage ;
    QFrame *CardMiddleImage ;
    int PlayingCardNumber;//numero de la carte actuelle jouer  par  l'utilisateur
    QString PlayingCardType;//type de la carte jouer par l'utilisateur
    bool FisrtPlay =  true;// verifier si c'est la premier carte jouer
    std::vector<QPoint> IaPlayingLastPoint;//liste des position des carte deja jouer par l'IA
    bool MoveCardToUserLeft = true;//bouger la carte a gauche pour les nouvelle carte distribuer
    bool MoveCardToIaLeft = true;
    std::vector<QPoint> UserPlayingLastPoint;
    bool GameTurnCompteur = true;//compteur de tour du jeu
    int PositionCompteurIa;
    int PositionCompteurUser;
    //text a l'ecran
    QLabel *nbrCartePlayer;
    QLabel *nbrCarteIa;
    QLabel *ScoreBanner;
    //EndGame *EndPage;

};

#endif // GAME_H
