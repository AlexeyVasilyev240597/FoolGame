#ifndef CARD_H_INCLUDED
#define CARD_H_INCLUDED

//#include <QMetaType>
//for Debug
//#include <QString>

enum SUIT{
	UNKNOWN_SUIT,
    NO_SUIT,
    DIAMONDS,
    HEARTS,
    CLUBS,
    SPADES,
    END_SUIT
};

constexpr char const * const SUIT_NAMES[END_SUIT] ={
	"UNK",
    "NOT",
    "D",
    "H",
    "C",
    "S"
};

enum RANK{
	UNKNOWN_RANK,
    NO_RANK,
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
    ACE,
	JOKER,
    END_RANK
};

constexpr char const * const RANK_NAMES[END_RANK] ={
	"UNK",
    "NOT",
    "2",
    "3",
    "4",
    "5",
    "6",
    "7",
    "8",
    "9",
    "10",
    "J",
    "Q",
    "K",
    "A",
	"JO"
};

enum COLOR{
	UNKNOWN_COLOR,
    NO_COLOR,
    RED,
    BLACK,
    END_COLOR
};

constexpr char const * const COLOR_NAMES[END_COLOR] ={
	"UNK",
    "NOT",
    "RED",
    "BLACK"
};

class CARD{
public:
    // closed card
    CARD():m_suit(UNKNOWN_SUIT),
           m_rank(UNKNOWN_RANK),
           m_color(UNKNOWN_COLOR){}

    /**
        Constructor of CARD is very useful and flexible,
        it gives a possibility to create a CARD which you know about just color
        or just rank etc.
    */
    // open card
    CARD(SUIT s, RANK r, COLOR c = NO_COLOR):m_suit(s),
                                             m_rank(r)
    {
        switch(s)
        {
            case DIAMONDS:
            case HEARTS:
                m_color = RED;
                break;
            case CLUBS:
            case SPADES:
                m_color = BLACK;
            case NO_SUIT:
                m_color = c;
                break;
            default:// UNKNOWN_SUIT:
                m_color = UNKNOWN_COLOR;
        }
    }

    SUIT getSuit() const { return m_suit; }
    RANK getRank() const { return m_rank; }
    COLOR getColor() const { return m_color; }

    //for Debug
    /*
    QString getInfo() const
    {
        QString str;
        if (m_rank < END_RANK && m_suit < END_SUIT)
            str = (QString)SUIT_NAMES[m_suit] + QString('-') + (QString)RANK_NAMES[m_rank];
        return str;
    }
    */
    CARD& operator= (const CARD& card)
    {
         m_suit = card.getSuit();
         m_rank = card.getRank();
         m_color = card.getColor();

         return *this;
    }

    ~CARD(){}

private:
    SUIT m_suit;
    RANK m_rank;
    COLOR m_color;
};

// transfer to DECK_H
/// relationship between SUIT-RANK-COLOR:
//const bool relSRC[END_SUIT][END_RANK][END_COLOR]


#endif // CARD_H_INCLUDED
