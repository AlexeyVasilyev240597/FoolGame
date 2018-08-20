#define _36_CARD_DECK 36
#define _52_CARD_DECK 52
//#define _52_CARD_DECK_PLUS_JOKERS 54

#ifndef _CARD_DESK_H
#define  _CARD_DESK_H

#include <vector>
#include <map>
#include <ctime>
#include <iostream>

enum SUIT{
	NO_SUIT,
	DIAMONDS,
	HEARTS,
	CLUBS,
	SPADES
};

enum COLOR{
	NO_COLOR,
	RED,
	BLACK
};

enum RANK{
	NO_RANK,
    JOKER,
	TWO,
	THREE,
	FOUR,
	FIVE,
	SIX,
	SEVEN,
	EIGHT,
	NINE,
	TEN,
	JACK,
	QUEEN,
	KING,
	ACE
};

enum FACE{
    DOWN,
    UP,
    TO_US,
    FROM_US
};

class CARD{
private:
	SUIT suit;
	RANK rank;
    FACE face{DOWN};
	
	CARD(SUIT s, RANK r){
		suit = s;
		rank = r;
		in_game = false;
	}

public:
	bool in_game;

    inline SUIT getSuit(){ return face != DOWN ? suit : NO_SUIT; }

    inline RANK getRank(){ return face != DOWN ? rank : NO_RANK; }

	void changeFaceState(FACE f){ face = f; }

	void changeInGameState(bool gs){ in_game = gs; }

	inline COLOR getColor(){
		COLOR c = NO_COLOR;
        if (face == DOWN)
			return c;

        if (suit == DIAMONDS || suit == HEARTS)
			c = RED;
        else if (suit == CLUBS || suit == SPADES)
			c = BLACK;
        //JOKER
		//else c = ;
		return c;
	}

	friend class DECK;
};

class DECK{
//private:
public:
    size_t volume;

    std::vector<CARD> cards;//, suit_badges;
    std::map<SUIT, CARD*> suit_badges;

	void toMix(){
		//when RELEASE
        srand(time(0));
		for (size_t i = 0; i < volume; i++)
			std::swap(cards[i], cards[rand() % volume]);
	}


    DECK(size_t v = _52_CARD_DECK){
		volume = v;

        for (int s = DIAMONDS; s <= SPADES; s++){
            for (int r = ((volume == _52_CARD_DECK /*|| volume == _52_CARD_DECK_PLUS_JOKERS*/) ? TWO : SIX);
				r <= ACE;
                r++)
                cards.push_back(CARD((SUIT)s, (RANK)r));

            //suit_badges.push_back(CARD((SUIT)s, NO_RANK));
            CARD *badge = new CARD((SUIT)s, NO_RANK);
            suit_badges.insert(std::pair<SUIT, CARD*>((SUIT)s, badge));
        }

        toMix();
	}
};

#endif //_CARD_DESK_H
