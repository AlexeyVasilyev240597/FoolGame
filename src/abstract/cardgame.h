#ifndef CARDGAME_H
#define CARDGAME_H

#include <QObject>
#include "CardDeck.h"
#include "gameelement.h"


class DEALER{
private:
    DECK *deck;
//RULES *rules;
public:

    DEALER(size_t deck_vlm){
        deck = new DECK(deck_vlm);
    //rules = r;
    //players.reserve(num_of_players);
    }

    void getOutCards(std::vector<ELEMENT*> elems);

    void exchange(ELEMENT* from, ELEMENT* to);
};


#endif // CARDGAME_H
