#define _36_CARD_DECK 36
#define _52_CARD_DECK 52
#define _52_CARD_DECK_PLUS_JOCKERS 54

#ifndef _CARD_DESK_H
#define  _CARD_DESK_H

#include <vector>
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
	JOCKER,
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
    UP
};

class CARD{
private:
	SUIT suit;
	RANK rank;
	FACE face;
	
	CARD(SUIT s, RANK r){
		suit = s;
		rank = r;
        face = DOWN;
		in_game = false;
	}

public:
	bool in_game;

    inline SUIT getSuit(){ return face == UP ? suit : NO_SUIT; }

    inline RANK getRank(){ return face == UP ? rank : NO_RANK; }

	void changeFaceState(FACE f){ face = f; }

	void changeInGameState(bool gs){ in_game = gs; }

	inline COLOR getColor(){
		COLOR c = NO_COLOR;
        if (face == DOWN)
			return c;

		if (this->suit == DIAMONDS || this->suit == HEARTS)
			c = RED;
		else if (this->suit == CLUBS || this->suit == SPADES)
			c = BLACK;
		//JOCKER
		//else c = ;
		return c;
	}

	friend class DECK;
};

class DECK{
//private:
public:
    size_t volume;

    std::vector<CARD> cards;

	void toMix(){
		//when RELEASE
		//srand(time(0));
		for (size_t i = 0; i < volume; i++)
			std::swap(cards[i], cards[rand() % volume]);
	}


	DECK(int v = _52_CARD_DECK){
		volume = v;
		for (int s = DIAMONDS; s <= SPADES; s++)
			for (int r = ((volume == _52_CARD_DECK || volume == _52_CARD_DECK_PLUS_JOCKERS) ? TWO : SIX);
				r <= ACE;
				r++){
				CARD c((SUIT)s, (RANK)r);
				cards.push_back(c);
			}
        toMix();
	}
/*
	void showDeck(){
        for (size_t i = 0; i < cards.size(); i++){
            if (cards[i].rank <= 10)
                std::cout << cards[i].rank;
            else switch(cards[i].rank){
			case JACK:
				std::cout << 'J';
				break;
			case QUEEN:
				std::cout << 'Q';
				break;
			case KING:
				std::cout << 'K';
				break;
			case ACE:
				std::cout << 'A';
				break;
			}

            switch (cards[i].suit){
			case DIAMONDS:
				std::cout << 'D';//'♦';
				break;
			case HEARTS:
				std::cout << 'H';//'♥';
				break;
			case CLUBS:
				std::cout << 'C';//'♣';
				break;
			case SPADES:
				std::cout << 'S';// '♠';
				break;
			}
			std::cout << std::endl;			
		}
	}
*/
	//friend class MANAGER;
};

#endif //_CARD_DESK_H
