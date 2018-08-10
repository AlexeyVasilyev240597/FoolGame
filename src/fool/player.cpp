#include <QObject>
#include "Player.h"

QPointF FOOL_PLAYER::getMyPos(size_t index){
    qreal x = my_set.size() <= init_volume ?
                80 * (3 - (qreal)my_set.size() / 2 + index) :     //выравнивание по центру
         (qreal)80 * 5 * index / (my_set.size() - 1),             //уплотнение набора
          y = 29 * (my_set.size() >= 36 / 2);                      //второй ряд карт

    QPoint p(x, y);
    return p;
}

void FOOL_PLAYER::addToSet(std::vector<CARD*> cards)
{
    for (size_t i = 0; i < cards.size(); i++){
        my_set.push_back(cards[i]);
        //в перегрузке для player по-другому
        my_set.back()->changeFaceState(UP);//is_user ? UP : DOWN);
    }

    //sortSet();
    //itemsUpdate();
    //qDebug() << state;
    for (size_t i = 0; i < my_set.size(); i++){

        //if my_set[i] is not found
        if (pl_set_view->card_btns.find(my_set[i]) ==
                pl_set_view->card_btns.end()){

            CARD_BTN* c_b = new CARD_BTN(getMyPos(i), my_set[i]);
            pl_set_view->card_btns.insert(std::pair<CARD*, CARD_BTN*>(my_set[i], c_b));

            pl_set_view->card_btns.at(my_set[i])->setParentItem(pl_set_view);
            QObject::connect(pl_set_view->card_btns.at(my_set[i]), &CARD_BTN::cardButtonClicked,
                             this, &FOOL_PLAYER::changeCard);
        }
        else
            pl_set_view->card_btns.at(my_set[i])->setPos(getMyPos(i));

        pl_set_view->card_btns.at(my_set[i])->setZValue(i + 1);
        //qDebug() << my_set[i]->getRank() << my_set[i]->getSuit();
    }

    //emit setUpdated();
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

    delete pl_set_view->card_btns.at(changed_card);
    pl_set_view->card_btns.erase(changed_card);

    size_t index = 0;
    for (std::map<CARD*, CARD_BTN*>::iterator it = pl_set_view->card_btns.begin();
         it != pl_set_view->card_btns.end();
         it++, index++){

        it->second->setPos(getMyPos(index));
        it->second->setZValue(index + 1);
     }

    return cards;
}
/*
void FOOL_PLAYER::itemsUpdate(){
    if (!pl_set_view->card_btns.empty()){

        for (size_t i = 0; i < pl_set_view->card_btns.size(); i++)
            delete pl_set_view->card_btns[i];
        pl_set_view->card_btns.clear();
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
        QObject::connect(pl_set_view->card_btns[i], &CARD_BTN::cardButtonClicked,
                         this, &FOOL_PLAYER::changeCard);
    }
}
*/
void FOOL_PLAYER::changeCard(Qt::MouseButton){
    for (std::map<CARD*, CARD_BTN*>::iterator it = pl_set_view->card_btns.begin(); it != pl_set_view->card_btns.end(); it++)
        if (it->second->isChanged){
            changed_card = it->first;
            break;
        }
    //qDebug() << changed_card->getSuit() << changed_card->getRank();
    emit chooseIsMade();
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
    //pl_set_view->itIsBeaten->setGeometry(QRect(QPoint(80*6,  0), QSize(30, 30)));
    //pl_set_view->itIsBeaten->setGeometry(QRect(QPoint(80*6, 40), QSize(30, 30)));
}

void FOOL_PLAYER::showMinTrump(){

}


void FOOL_PLAYER::customizeButtons(){
    for (std::map<CARD*, CARD_BTN*>::iterator it = pl_set_view->card_btns.begin(); it != pl_set_view->card_btns.end(); it++)
        it->second->canIBeClicked = my_move;

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
For advanced users, there are ways to alter how your items are sorted:

You can call setZValue() on an item to explicitly stack it on top of,
or under, other sibling items. The default Z value for an item is 0.
Items with the same Z value are stacked by insertion order.

You can call stackBefore() to reorder the list of children.
This will directly modify the insertion order.

You can set the ItemStacksBehindParent flag to stack a child item behind its parent.
The stacking order of two sibling items also counts for each item's children
and descendant items. So if one item is on top of another, then all its children
will also be on top of all the other item's children as well.
*/
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
