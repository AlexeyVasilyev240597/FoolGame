#ifndef _GAME_ELEMENT_H
#define _GAME_ELEMENT_H

#include <vector>

#include "../abstract/CardDeck.h"
#include "../drawing/GameItems.h"
#include <QDebug>

class ELEMENT{
protected:
    std::vector<CARD*> my_set;
    //лучше просто передать в getOutCards() для каждого элемента,
    //например, map, который генерируется в RULES
    size_t init_volume;

    enum ACCESS{TO_NOONE, TO_HOLDER, TO_ALL} access;

public:
    ELEMENT(ACCESS ac, size_t iv){
        access = ac;
        init_volume = iv;
        set_view = NULL;
    }

    ACCESS getAccess(){ return access; }

    size_t getInitVolume(){ return init_volume; }

    size_t getVolume(){ return my_set.size(); }

    std::vector<CARD*> showSet(){
        std::vector<CARD*> cards(my_set.size());
        if (access == TO_ALL)
            my_set.swap(cards);

        return cards;
    }

    //later it method will be private, access
    virtual void addToSet(std::vector<CARD*> cards){
        for (size_t i = 0; i < cards.size(); i++){
            my_set.push_back(cards[i]);
            //в перегрузке для player по-другому
            my_set.back()->changeFaceState(access != TO_NOONE ? UP : DOWN);
        }
    }

    virtual std::vector<CARD*> giveCard() = 0;

    MY_ITEM *set_view;

    //virtual void initSetView(QPoint pos, int w, int h) = 0   - потом сделай, когда для всех наслеников напишешь
    virtual void initSetView(QPoint, int, int){}

    virtual void drawSet(){}
};

#endif // _GAME_ELEMENT_H
