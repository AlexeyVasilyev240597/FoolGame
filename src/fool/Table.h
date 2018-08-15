#ifndef _TABLE_H
#define _TABLE_H

#include <QObject>
#include <vector>
#include <string>
#include <map>

#include "../abstract/CardDeck.h"
//#include "../abstract/myitem.h"
#include "../drawing/GameItems.h"
#include "../abstract/GameElement.h"
#include "Player.h"
#include <QDebug>

class FOOL_PRICUP: public QObject, public ELEMENT{
Q_OBJECT
private:
    SUIT trump;

public:
	FOOL_PRICUP(size_t iv):ELEMENT(TO_NOONE, iv){}

    std::vector<CARD*> giveCard(size_t number);

    void initSetView(FOOL_PRICUP_SET_VIEW*);

signals:
    void getTrumpSuit(SUIT);

    void addedToSet(CARD*);

    void removedFromSet(size_t);

public slots:
    void dealerGaveOut();
};


class FOOL_BEATEN : public QObject, public ELEMENT{
Q_OBJECT
public:
    FOOL_BEATEN():ELEMENT(TO_NOONE, 0){}

    FOOL_BEATEN_SET_VIEW *b_set_view;

    std::vector<CARD*> giveCard();

    //void initSetView(QPointF pos, int w, int h);

    void addToSet(std::vector<CARD*> cards);

    void initSetView(FOOL_BEATEN_SET_VIEW*);

signals:
    void addedToSet();
};


class FOOL_FIGHT_FIELD : public QObject, public ELEMENT{
Q_OBJECT
public:
    FOOL_FIGHT_FIELD_SET_VIEW *f_f_set_view;

    enum CARD_STATE_ON_FIELD{FROM_ATTAKING, FROM_DEFENCING};
    std::map<CARD_STATE_ON_FIELD, size_t> counter;

    //enum FIELD_STATE{PLAYING, BEATEN_OFF, PICK_UP} state{PLAYING};

    FOOL_FIGHT_FIELD() :ELEMENT(TO_ALL, 0){
        counter.insert(std::pair<CARD_STATE_ON_FIELD, size_t>(FROM_ATTAKING,  0));
        counter.insert(std::pair<CARD_STATE_ON_FIELD, size_t>(FROM_DEFENCING, 0));
    }

    std::vector<CARD*> giveCard();

    void initSetView(FOOL_FIGHT_FIELD_SET_VIEW*);

    void addToSet(std::vector<CARD*> cards, FOOL_PLAYER::PLAYER_STATE s);

    //void itemsUpdate();

signals:    
    void addedToSet(CARD*, bool, size_t);

    void removedFromSet();
};

/*
аааааа, короче идея:
1. пусть диллер раздает натоящие карты - объекты, а не указатели,
это будет естественней, тогда никто не сможет присвоить какому-нибудь указателю карту,
которая у него есть;

2. надо будет еще замутить конструктор карты explicit;

3. и showSet() и showLastCard() у элемента будут возвращать const &CARD - тоже естественно,
да и уровни доступа будут иметь смысл тогда

4. еще нужно написать диллера, который создает столько же card-items(или написать gui-deck?),
и распределяет и их тоже по соответстующим item-ам элементов
 */
class DEALER: public QObject{
Q_OBJECT
private:
    DECK *deck;
public:

    DEALER(size_t deck_vlm){
        deck = new DECK(deck_vlm);
    }

    void giveOutCards(ELEMENT* elem);

    void exchange(ELEMENT* from, ELEMENT* to);

signals:
    void iGaveOut();

};

#endif//_TABLE_H
