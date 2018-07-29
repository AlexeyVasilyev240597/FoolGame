#ifndef FOOL_H
#define FOOL_H
#include <QObject>
#include "../abstract/CardDeck.h"
#include "../abstract/GameElement.h"
#include "../drawing/GameItems.h"
#include "../drawing/GameScene.h"
#include "Table.h"
#include "Player.h"

//но потом ты напишешь абстрактный класс CARD_GAME
//two players, 36 card deck
class   FOOL_GAME{
//Q_OBJECT
private:
    DEALER* dealer;
    SUIT trump;

public:
    std::vector<ELEMENT*> players;
    std::vector<ELEMENT*> table;
    FOOL_PRICUP *pr;

    FOOL_GAME(){//size_t pl_num, size_t tbl_num, size_t deck_vlm = _36_CARD_DECK){
        players.reserve(2);
        table.reserve(3);

        dealer = new DEALER(_36_CARD_DECK);
        setElems();
    }

    void setElems();
    void game();
/*
signals:
    void initPlayer(MY_ITEM* item);
    void initTableElem(MY_ITEM* item);
*/
};

#endif // FOOL_H
