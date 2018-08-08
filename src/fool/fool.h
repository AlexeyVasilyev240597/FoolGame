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
public:
    std::vector<ELEMENT*> players;
    std::vector<ELEMENT*> table;

protected:
    SUIT trump;
    FOOL_PLAYER* pl1;
    FOOL_PLAYER* pl2;

    FOOL_PRICUP *pr;
    FOOL_FIGHT_FIELD *field;

    FOOL_RULES(){//size_t pl_num, size_t tbl_num, size_t deck_vlm = _36_CARD_DECK){
        players.reserve(2);
        table.reserve(3);
    }
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
    //вместо этих векторов написать:
    //vector<MY_ITEM*> getItems();
    //std::vector<ELEMENT*> players;
    //std::vector<ELEMENT*> table;
    //FOOL_PRICUP *pr;

    FOOL_GAME();
    void game();

public slots:
    void someSetUpdated();
/*
signals:
    void initPlayer(MY_ITEM* item);
    void initTableElem(MY_ITEM* item);
*/
};

#endif // _FOOL_H
