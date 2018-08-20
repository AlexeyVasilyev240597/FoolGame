#include <QObject>
#include "Player.h"


//------------------------------PLAYER-------------------------------------
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
void USER::iMistake(){
    emit choosedWrongCard(choosed_card);
    choosed_card = NULL;
}
*/

std::vector<CARD*>::iterator AI::getMinCard(CARD* less){
    SUIT s = less == NULL ? NO_SUIT : less->getSuit();
    RANK r = less == NULL ? NO_RANK : less->getRank();
    std::vector<CARD*>::iterator it = my_set.begin();


    return it;
}

void AI::aiChangeMoveValue(){
    my_move = !my_move;

    if (my_move){
        switch (state){
        case ATTACK:{
            if (on_field == NULL){
                choosed_card = my_set.front();
                emit chooseIsMade();
            }

            else
                emit itIsBeaten();
            /*потом нужно выбирать наименьшую некозырную
             * или наименьшую козырную, если этого сделать не удалось*/
            /*
            if (on_field == NULL)
                for (std::vector<CARD*>::iterator it = my_set.begin(); it != my_set.end(); it++)
                    if ((*it)->getSuit() != trump && (*it)->getRank() < choosed_card->getRank())
                        choosed_card = (*it);
            */
            }
            break;

        case DEFENCE:{
           if (on_field->getSuit() == trump)
             for (std::vector<CARD*>::iterator it = my_set.begin(); it != my_set.end(); it++)
                 if((*it)->getSuit() == trump &&
                    (*it)->getRank() > on_field->getRank())
                        choosed_card = (*it);


            else
             for (std::vector<CARD*>::iterator it = my_set.begin(); it != my_set.end(); it++)
                 if (((*it)->getSuit() == on_field->getSuit() &&
                         (*it)->getRank() > on_field->getRank()) ||
                         (*it)->getSuit() == trump)
                        choosed_card = (*it);

            if (choosed_card != NULL)
                emit chooseIsMade();
            else
                emit iTakeIt();
            }
            break;

        case ADDING:
            emit takeAway();
            break;

        }
    }
}

void AI::trownCardToField(CARD* card, bool inAttack, size_t /*index*/){
    if (!my_move && inAttack)
        on_field = card;
        //on_field.push_back(card);
}
