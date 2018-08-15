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

signals:
    void getTrumpSuit(SUIT);

    void addedToSet(CARD*);

    void removedFromSet(size_t);

public slots:
    void dealerGaveOut();
};



class FOOL_FIGHT_FIELD : public QObject, public ELEMENT{
Q_OBJECT
public:
    enum CARD_STATE_ON_FIELD{FROM_ATTAKING, FROM_DEFENCING};
    std::map<CARD_STATE_ON_FIELD, size_t> counter;

    //enum FIELD_STATE{PLAYING, BEATEN_OFF, PICK_UP} state{PLAYING};

    FOOL_FIGHT_FIELD() :ELEMENT(TO_ALL, 0){
        counter.insert(std::pair<CARD_STATE_ON_FIELD, size_t>(FROM_ATTAKING,  0));
        counter.insert(std::pair<CARD_STATE_ON_FIELD, size_t>(FROM_DEFENCING, 0));
    }

    std::vector<CARD*> giveCard();

    void addToSet(std::vector<CARD*> cards, FOOL_PLAYER::PLAYER_STATE s);

    //void itemsUpdate();

signals:
    void addedToSet(CARD*, bool, size_t);

    void removedFromSet();
};


class FOOL_BEATEN : public QObject, public ELEMENT{
Q_OBJECT
public:
    FOOL_BEATEN():ELEMENT(TO_NOONE, 0){}

    std::vector<CARD*> giveCard();

    //void initSetView(QPointF pos, int w, int h);

    void addToSet(std::vector<CARD*> cards);

signals:
    void addedToSet();
};

/*
������, ������ ����:
1. ����� ������ ������� �������� ����� - �������, � �� ���������,
��� ����� ������������, ����� ����� �� ������ ��������� ������-������ ��������� �����,
������� � ���� ����;

2. ���� ����� ��� �������� ����������� ����� explicit;

3. � showSet() � showLastCard() � �������� ����� ���������� const &CARD - ���� �����������,
�� � ������ ������� ����� ����� ����� �����

4. ��� ����� �������� �������, ������� ������� ������� �� card-items(��� �������� gui-deck?),
� ������������ � �� ���� �� �������������� item-�� ���������
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
