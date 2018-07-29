#include <QObject>
#include "Player.h"

void FOOL_PLAYER::addToSet(std::vector<CARD*> cards){
    for (size_t i = 0; i < cards.size(); i++){
        my_set.push_back(cards[i]);
        //в перегрузке для player по-другому
        my_set.back()->changeFaceState(UP);//is_user ? UP : DOWN);
    }

    setUpdated();
}
std::vector<CARD*> FOOL_PLAYER::giveCard(){
    //palyer ходит ПО ОДНОЙ карте
    std::vector<CARD*> cards;

    cards.push_back(changed_card);

    setUpdated();

    return cards;
}

void FOOL_PLAYER::setUpdated(){

if (!pl_set_view->card_btns.empty())
    for (size_t i = 0; i < pl_set_view->card_btns.size(); i++)
        delete pl_set_view->card_btns[i];

for (size_t i = 0; i < my_set.size(); i++){
    QPoint p(80*i, 0);//880/2+(i-my_set.size()/2)*80,440);
    CARD_BTN* c_b = new CARD_BTN(p, my_set[i]);
    pl_set_view->card_btns.push_back(c_b);
}

for (size_t i = 0; i < pl_set_view->card_btns.size(); i++)
    pl_set_view->card_btns[i]->setParentItem(pl_set_view);
}

void FOOL_PLAYER::changeCard(CARD* card){
    changed_card = card;
    /*
    int r, s;
    std::cin >> r >> s;


    for (size_t i = 0; i < my_set.size(); i++){
        if (my_set[i]->getSuit() == (SUIT)s && my_set[i]->getRank() == r){
            cards.push_back(my_set.at(i));
            my_set.erase(my_set.begin() + i);
            return cards;
        }
    }
*/

}
/*
void FOOL_PLAYER::fillCardBtns(){
    for (size_t i = 0; i < my_set.size(); i++){
        CARD_BTN *c_b = new CARD_BTN(my_set[i]);
        set_view->itemVec.push_back(c_b);
    }
}
*/

void FOOL_PLAYER::initSetView(QPoint pos, int w, int h){
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
