#include <QObject>
#include "Player.h"

void FOOL_PLAYER::addToSet(std::vector<CARD*> cards)
{
    for (size_t i = 0; i < cards.size(); i++){
        my_set.push_back(cards[i]);
        //можно искать место для вставки здесь
        //и не использовать сложную сортировку
        my_set.back()->changeFaceState(UP);//is_user ? UP : DOWN);
    }

    emit addedToSet(my_set);
}

void FOOL_PLAYER::initSetView(FOOL_PLAYER_SET_VIEW *pl_set_view){

QObject::connect(this, &FOOL_PLAYER::addedToSet,
                 pl_set_view, &FOOL_PLAYER_SET_VIEW::addToMap);

QObject::connect(this, &FOOL_PLAYER::removedFromSet,
                 pl_set_view, &FOOL_PLAYER_SET_VIEW::removeFromMap);


QObject::connect(pl_set_view, &FOOL_PLAYER_SET_VIEW::choosedCard,
                 this, &FOOL_PLAYER::changeCard);

QObject::connect(pl_set_view->itIsBeaten, &BUTTON::buttonClicked,
                 this, &FOOL_PLAYER::itIsBeaten);

QObject::connect(pl_set_view->iTake, &BUTTON::buttonClicked,
                 this, &FOOL_PLAYER::iTakeIt);

QObject::connect(pl_set_view->takeAway, &BUTTON::buttonClicked,
                 this, &FOOL_PLAYER::takeAway);

/*потом конект понадобится для графического отображения сигнала об ошибке!
QObject::connect(this, &FOOL_PLAYER::choosedWrongCard,
                 pl_set_view, &FOOL_PLAYER_SET_VIEW::changeCardState);
*/

QObject::connect(this, &FOOL_PLAYER::customizeButtons,
                 pl_set_view, &FOOL_PLAYER_SET_VIEW::customizeButtons);
}

std::vector<CARD*> FOOL_PLAYER::giveCard(){
    //palyer ходит ПО ОДНОЙ карте
    std::vector<CARD*> cards;

    cards.push_back(choosed_card);
    for (size_t i = 0; i < my_set.size(); i++)
        if (my_set[i] == choosed_card){
            std::swap(my_set[i], my_set[0]);
            my_set.erase(my_set.begin());
            break;
        }

    choosed_card = NULL;

    emit removedFromSet(cards);

    return cards;
}

void FOOL_PLAYER::changeCard(CARD* card){
    choosed_card = card;
    //qDebug() << changed_card->getSuit() << changed_card->getRank();
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
    //=== state = state == ATTACK || state == TAKING ? DEFENCE : ATTACK;
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
/*
void FOOL_PLAYER::sortSet(){
    for (size_t i = 0; i < my_set.size() - 1; i++)
        for (size_t j = i + 1; j < my_set.size(); j++){
            int s[2] = {my_set[i]->getSuit() == trump ? (int)my_set[i]->getSuit() + 5 : (int)my_set[i]->getSuit(),
                        my_set[j]->getSuit() == trump ? (int)my_set[j]->getSuit() + 5 : (int)my_set[j]->getSuit()};
            if (s[0] > s[1])
                std::swap(my_set[i], my_set[j]);
        }

    size_t i = 0;
    for (int s = DIAMONDS; s <= SPADES; s++){
        for (; my_set[i]->getSuit() == s && i < my_set.size(); i++)
            for (size_t j = i; my_set[j]->getSuit() == s && j < my_set.size(); j++)
                if ((int)my_set[i]->getRank() > (int)my_set[j]->getRank())
                    std::swap(my_set[i], my_set[j]);
        qDebug() << my_set[i]->getRank() << my_set[i]->getSuit();
    }
}
*/
