#ifndef _FOOL_H
#define _FOOL_H

#include <QObject>
#include "rules.h"

class FOOL_ITEM_MANAGER: public QObject{
Q_OBJECT
public:
    FOOL_PLAYER_SET_VIEW *pl1_item, *pl2_item;
    FOOL_PRICUP_SET_VIEW *pr_item;
    FOOL_FIGHT_FIELD_SET_VIEW *f_item;
    FOOL_BEATEN_SET_VIEW *b_item;

    void createItem(FOOL_PLAYER*, size_t);
    void createItem(FOOL_PRICUP*);
    void createItem(FOOL_FIGHT_FIELD*);
    void createItem(FOOL_BEATEN*);

signals:
    void addElem(MY_ITEM*);

};

//но потом ты напишешь абстрактный класс CARD_GAME
//two players, 36 card deck
class   FOOL_GAME: public FOOL_RULES{
Q_OBJECT
private:
    DEALER* dealer;

public:
    //FOOL_GAME();
    //~FOOL_GAME();

    void init(FOOL_ITEM_MANAGER*);
    void game();
    //std::vector<MY_ITEM*> getItems();
    void endLocalFight();
    void fillSetsOfPlayers();

public slots:
    void playerChoosedCard();

    void finishHim();

    void throwToBeaten();

    void giveToPlayer();

//signals:
    //потом сигнал понадобится для графического отображения сигнала об ошибке!
    //void wrongMove();
};

#endif // _FOOL_H
