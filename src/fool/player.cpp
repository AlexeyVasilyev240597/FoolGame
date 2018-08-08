#include <QObject>
#include "Player.h"

void FOOL_PLAYER::addToSet(std::vector<CARD*> cards){
    for (size_t i = 0; i < cards.size(); i++){
        my_set.push_back(cards[i]);
        //в перегрузке для player по-другому
        my_set.back()->changeFaceState(UP);//is_user ? UP : DOWN);
    }

    //sortSet();
    itemsUpdate();

    emit setUpdated();
}
std::vector<CARD*> FOOL_PLAYER::giveCard(){
    //palyer ходит ПО ОДНОЙ карте
    std::vector<CARD*> cards;

    cards.push_back(changed_card);
    for (size_t i = 0; i < my_set.size(); i++)
        if (my_set[i] == changed_card){
            std::swap(my_set[i], my_set[0]);
            my_set.erase(my_set.begin());
            break;
        }


    itemsUpdate();

    emit setUpdated();

    return cards;
}

void FOOL_PLAYER::itemsUpdate(){
    if (!pl_set_view->card_btns.empty()){

        for (size_t i = 0; i < pl_set_view->card_btns.size(); i++)
            delete pl_set_view->card_btns[i];
    }

    for (size_t i = 0; i < my_set.size(); i++){
        double x = my_set.size() <= 6 ?
                    80*(3 - (double)my_set.size()/2 + i) ://выравнивание по центру
            (double)80*5*i/(my_set.size()-1);             //уплотнение набора
        QPoint p(x, 0);
        CARD_BTN* c_b = new CARD_BTN(p, my_set[i]);
        pl_set_view->card_btns.push_back(c_b);
    }


    for (size_t i = 0; i < pl_set_view->card_btns.size(); i++){
        pl_set_view->card_btns[i]->setParentItem(pl_set_view);
        QObject::connect(pl_set_view->card_btns[i], &CARD_BTN::btnMouseReleaseEvent,
                         this, &FOOL_PLAYER::changeCard);
    }
}

void FOOL_PLAYER::changeCard(Qt::MouseButton){
    for (size_t i = 0; i < pl_set_view->card_btns.size(); i++)
        if (pl_set_view->card_btns[i]->isChanged){
            changed_card = my_set[i];
            break;
        }
    qDebug() << changed_card->getSuit() << changed_card->getRank();
}

/*
void FOOL_PLAYER::fillCardBtns(){
    for (size_t i = 0; i < my_set.size(); i++){
        CARD_BTN *c_b = new CARD_BTN(my_set[i]);
        set_view->itemVec.push_back(c_b);
    }
}
*/

void FOOL_PLAYER::initSetView(QPointF pos, int w, int h){
    pl_set_view = new FOOL_PLAYER_SET_VIEW(pos, w, h);
    set_view = pl_set_view;
    //if (!my_set.empty())
      //  fillCardBtns();
}

void FOOL_PLAYER::showMinTrump(){

}

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
        for (; my_set[i]->getSuit() != s; i++)
            for (size_t j = i; my_set[j]->getSuit() != s; j++)
                if ((int)my_set[i]->getRank() > (int)my_set[j]->getRank())
                    std::swap(my_set[i], my_set[j]);
    }
}
