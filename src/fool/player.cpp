#include <QObject>
#include "Player.h"

void FOOL_PLAYER::addToSet(std::vector<CARD*> cards)
{
    for (size_t i = 0; i < cards.size(); i++){
        my_set.push_back(cards[i]);
        //в перегрузке для player по-другому
        my_set.back()->changeFaceState(UP);//is_user ? UP : DOWN);
    }

    for (size_t i = 0; i < my_set.size(); i++){

        //if my_set[i] is not found
        if (pl_set_view->card_btns.find(my_set[i]) ==
                pl_set_view->card_btns.end()){

            CARD_BTN* c_b = new CARD_BTN(pl_set_view->getMyPos(i, my_set.size()), my_set[i]);
            pl_set_view->card_btns.insert(std::pair<CARD*, CARD_BTN*>(my_set[i], c_b));

            pl_set_view->card_btns.at(my_set[i])->setParentItem(pl_set_view);
            QObject::connect(pl_set_view->card_btns.at(my_set[i]), &CARD_BTN::cardButtonClicked,
                             this, &FOOL_PLAYER::changeCard);
        }
        else
            pl_set_view->card_btns.at(my_set[i])->setPos(pl_set_view->getMyPos(i, my_set.size()));

        pl_set_view->card_btns.at(my_set[i])->setZValue(i + 1);
        //qDebug() << my_set[i]->getRank() << my_set[i]->getSuit();
    }
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

    delete pl_set_view->card_btns.at(choosed_card);
    pl_set_view->card_btns.erase(choosed_card);

    size_t index = 0;
    for (std::map<CARD*, CARD_BTN*>::iterator it = pl_set_view->card_btns.begin();
         it != pl_set_view->card_btns.end();
         it++, index++){

        it->second->setPos(pl_set_view->getMyPos(index, my_set.size()));
        it->second->setZValue(index + 1);
     }

    return cards;
}

void FOOL_PLAYER::changeCard(Qt::MouseButton){
    for (std::map<CARD*, CARD_BTN*>::iterator it = pl_set_view->card_btns.begin(); it != pl_set_view->card_btns.end(); it++)
        if (it->second->isChanged){
            choosed_card = it->first;
            break;
        }
    //qDebug() << changed_card->getSuit() << changed_card->getRank();
    emit chooseIsMade();
}

void FOOL_PLAYER::initSetView(QPointF pos, int w, int h){
    pl_set_view = new FOOL_PLAYER_SET_VIEW(pos, w, h);
    //pl_set_view->itIsBeaten->setGeometry(QRect(QPoint(80*6,  0), QSize(30, 30)));
    //pl_set_view->itIsBeaten->setGeometry(QRect(QPoint(80*6, 40), QSize(30, 30)));
}

void FOOL_PLAYER::showMinTrump(){

}


void FOOL_PLAYER::customizeButtons(){
    for (std::map<CARD*, CARD_BTN*>::iterator it = pl_set_view->card_btns.begin(); it != pl_set_view->card_btns.end(); it++)
        it->second->setEnabled(my_move);

    pl_set_view->iTake->setVisible(my_move && state == DEFENCE);
    pl_set_view->itIsBeaten->setVisible(my_move && state == ATTACK);
    pl_set_view->takeAway->setVisible(state == ADDING);
}

void FOOL_PLAYER::initState(PLAYER_STATE s){
    state = s;
    my_move = state == ATTACK;
    customizeButtons();
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

    customizeButtons();
}

void FOOL_PLAYER::changeMoveValue(){
    my_move = !my_move;
    customizeButtons();
}
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
