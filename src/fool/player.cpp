#include <QObject>
#include "Player.h"

inline size_t getWeight(CARD *c, SUIT trump){
    return (int)ACE * (c->getSuit() == trump) + c->getRank();
}

void FOOL_PLAYER::addToSet(std::vector<CARD*> cards)
{
    for (size_t i = 0; i < cards.size(); i++){
        cards[i]->changeFaceState(TO_US);

        size_t insert_card_weight = getWeight(cards[i], trump);
        bool card_was_inserted = false;
        for (std::vector<CARD*>::iterator it = my_set.begin(); it != my_set.end(); it++){
            size_t cur_card_weigth = getWeight((*it), trump);
            if (insert_card_weight <= cur_card_weigth){
                my_set.insert(it, cards[i]);
                card_was_inserted = true;
                break;
            }
        }
        if (!card_was_inserted)
            my_set.push_back(cards[i]);
    }

    emit addedToSet(my_set);
}

std::vector<CARD*> FOOL_PLAYER::giveCard(){
    //palyer ходит ПО ОДНОЙ карте
    std::vector<CARD*> cards;

    cards.push_back(choosed_card);
    for (std::vector<CARD*>::iterator it = my_set.begin(); it != my_set.end(); it++)
        if ((*it) == choosed_card){
            my_set.erase(it);
            break;
        }
    choosed_card = NULL;

    emit removedFromSet(my_set, cards);

    return cards;
}

void FOOL_PLAYER::changeCard(CARD* card){
    choosed_card = card;

    emit chooseIsMade();
}

void FOOL_PLAYER::showMinTrump(){

}


void FOOL_PLAYER::initState(PLAYER_STATE s){
    state = s;
    my_move = state == ATTACK;

    emit customizeButtons(my_move,
                          my_move && state == FOOL_PLAYER::ATTACK,
                          my_move && state == FOOL_PLAYER::DEFENCE,
                          state == FOOL_PLAYER::ADDING);
}

void FOOL_PLAYER::changeState(){
    switch (state){
    case ATTACK:
        state = DEFENCE;
        break;
    case DEFENCE:
        state = ATTACK;
        break;
    case ADDING:
        state = ATTACK;
        break;
    case TAKING:
        state = DEFENCE;
        break;
    case NO_DEF:
        state = NO_DEF;
        break;
    }

    emit customizeButtons(my_move,
                          my_move && state == FOOL_PLAYER::ATTACK,
                          my_move && state == FOOL_PLAYER::DEFENCE,
                                     state == FOOL_PLAYER::ADDING);
}

void FOOL_PLAYER::changeMoveValue(){
    my_move = !my_move;

    emit customizeButtons(my_move,
                          my_move && state == FOOL_PLAYER::ATTACK,
                          my_move && state == FOOL_PLAYER::DEFENCE,
                                     state == FOOL_PLAYER::ADDING);
}
/*
void FOOL_PLAYER::iMistake(){
    emit choosedWrongCard(choosed_card);
    choosed_card = NULL;
}
*/
