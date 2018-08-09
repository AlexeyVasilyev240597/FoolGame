#ifndef _FOOL_H
#define _FOOL_H

#include <QObject>
#include "../abstract/CardDeck.h"
#include "../abstract/GameElement.h"
#include "../drawing/GameItems.h"
#include "../drawing/GameScene.h"
#include "Table.h"
#include "Player.h"

class   FOOL_RULES{
//Q_OBJECT
protected:
    SUIT trump;
    FOOL_PLAYER* pl1;
    FOOL_PLAYER* pl2;

    FOOL_PRICUP *pr;
    FOOL_FIGHT_FIELD *field;
    FOOL_BEATEN *beaten;

/*
signals:
    void initPlayer(MY_ITEM* item);
    void initTableElem(MY_ITEM* item);
*/
};

//но потом ты напишешь абстрактный класс CARD_GAME
//two players, 36 card deck
class   FOOL_GAME: public QObject, public FOOL_RULES{
Q_OBJECT
private:
    DEALER* dealer;

public: 
    FOOL_GAME();
    void game();
    std::vector<MY_ITEM*> getItems();

public slots:
    void someSetUpdated();
    void throwToBeaten();
/*
signals:
    void initPlayer(MY_ITEM* item);
    void initTableElem(MY_ITEM* item);
*/
};

#endif // _FOOL_H
