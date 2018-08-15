#ifndef _TABLE_H
#define _TABLE_H

#include <QObject>
#include <vector>
#include <string>
#include <map>

#include "../abstract/CardDeck.h"
#include "../abstract/myitem.h"
#include "../drawing/GameItems.h"
#include "../abstract/GameElement.h"
#include "Player.h"
#include <QDebug>

class FOOL_PRICUP: public QObject, public ELEMENT{
Q_OBJECT
private:
    SUIT trump;

public:
    FOOL_PRICUP_SET_VIEW *pr_set_view;

	FOOL_PRICUP(size_t iv):ELEMENT(TO_NOONE, iv){}

    std::vector<CARD*> giveCard(){
        std::vector<CARD*> cards;
        cards.push_back(my_set.at(0));
        my_set.erase(my_set.begin());

        return cards;
    }
    std::vector<CARD*> giveCard(size_t number);		

    //void initSetView(QPointF pos, int w, int h);

    void addItems();

signals:
    void getTrumpSuit(SUIT);

public slots:
    void dealerGetOut();
};


class FOOL_BEATEN : public ELEMENT{
public:
    FOOL_BEATEN():ELEMENT(TO_NOONE, 0){}

    FOOL_BEATEN_SET_VIEW *b_set_view;

    std::vector<CARD*> giveCard();

    //void initSetView(QPointF pos, int w, int h);

    void addToSet(std::vector<CARD*> cards);
};


class FOOL_FIGHT_FIELD : public QObject, public ELEMENT{
Q_OBJECT
public:
    FOOL_FIGHT_FIELD_SET_VIEW *f_f_set_view;

    size_t card_count_from_attacking{0},
           card_count_from_defencing{0};

    //enum FIELD_STATE{PLAYING, BEATEN_OFF, PICK_UP} state{PLAYING};

    FOOL_FIGHT_FIELD() :ELEMENT(TO_ALL, 0){}

    std::vector<CARD*> giveCard();

    //void initSetView(QPointF pos, int w, int h);

    void addToSet(std::vector<CARD*> cards, FOOL_PLAYER::PLAYER_STATE s);

    //void itemsUpdate();

signals:
    void setUpdated();
    //void iFilled();
};

/*
аааааа, короче идея:
1. пусть дилер раздает натоящие карты - объекты, а не указатели,
это будет естественней, тогда никто не сможет присвоить какому-нибудь указателю карту,
которая у него есть;

2. надо будет еще замутить конструктор карты explicit;

3. и showSet() и showLastCard() у элемента будут возвращать const &CARD - тоже естественно,
да и уровни доступа будут иметь смысл тогда

 */
class DEALER: public QObject{
Q_OBJECT
private:
    DECK *deck;
//RULES *rules;
public:

    DEALER(size_t deck_vlm){
        deck = new DECK(deck_vlm);
    //rules = r;
    //players.reserve(num_of_players);
    }

    void getOutCards(ELEMENT* elem);

    void exchange(ELEMENT* from, ELEMENT* to);

signals:
    void iGetOut();

};


/*
class RULES{
public:
	//enum CATEGORY{ TABLE, PLAYERS };
	std::map<string, size_t> *my_sets_volume;
	size_t max_num_of_players, how_many_cards_to_player;
	//switch over my_setS
	//virtual size_t howManyCards(CATEGORY cat, int key) = 0;// {
	//std::cout << "i'm in base class(((" << std::endl;
	//return 0; 
	//}
	RULES(std::map<string, size_t> *s_v, size_t hmctp){
		my_sets_volume = s_v;
		how_many_cards_to_player = hmctp;
	}
};
*/

/*
class GAME{
public:
	size_t num_of_players;
    size_t dek_volume;
    GAME(){}
    GAME(size_t nop, size_t dv){
		num_of_players = nop;
        deck_volume = dv;
	}

	RULES *rules;
	std::map<string, my_set*> table;
    std::vector<PLAYER> players;

	virtual void my_setRules() = 0;

	void initTable();//std::map<NAMES_OF_FIELDS, my_set*> &table);
    void initPlayers();//std::vector<PLAYER> &players);

	//virtual void toPlay() = 0;
};
*/

#endif//_TABLE_H
