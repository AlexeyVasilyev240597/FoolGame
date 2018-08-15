#ifndef _FOOL_H
#define _FOOL_H

#include <QObject>
#include "rules.h"

//но потом ты напишешь абстрактный класс CARD_GAME
//two players, 36 card deck
class   FOOL_GAME:public FOOL_RULES{
Q_OBJECT
private:
    DEALER* dealer;

    //items
    FOOL_PLAYER_SET_VIEW *pl1_item, *pl2_item;
    FOOL_PRICUP_SET_VIEW *pr_item;
    FOOL_FIGHT_FIELD_SET_VIEW *f_item;
    FOOL_BEATEN_SET_VIEW *b_item;

public: 
    //FOOL_GAME();
    //~FOOL_GAME();

    void init();
    void game();
    std::vector<MY_ITEM*> getItems();
    void endLocalFight();
    void fillSetsOfPlayers();

public slots:
    void playerChoosedCard();

    void finishHim();

    void throwToBeaten();

    void giveToPlayer();

signals:
    void addElem(MY_ITEM* item);

    //потом сигнал понадобится для графического отображения сигнала об ошибке!
    //void wrongMove();
};

#endif // _FOOL_H
