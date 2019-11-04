#ifndef CARD_H_INCLUDED
#define CARD_H_INCLUDED

//#include <QMetaType>
//for Debug
//#include <QString>

enum SUIT{
    NO_SUIT,
    DIAMONDS,
    HEARTS,
    CLUBS,
    SPADES,
    END_SUIT
};

constexpr char const * const SUIT_NAMES[END_SUIT] ={
    "NOT",
    "D",
    "H",
    "C",
    "S"
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
    ACE,
    END_RANK
};

constexpr char const * const RANK_NAMES[END_RANK] ={
    "NOT",
    "JO",
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
    "A"
};

enum COLOR{
    NO_COLOR,
    RED,
    BLACK,
    END_COLOR
};

constexpr char const * const COLOR_NAMES[END_COLOR] ={
    "NOT",
    "RED",
    "BLACK"
};

enum SIDE{
    FACE,
    BACK
};

class CARD{
public:
    // closed card
    CARD():m_suit(NO_SUIT),
           m_rank(NO_RANK),
           m_color(NO_COLOR),
           m_side(BACK){}

    /**
        Constructor of CARD is very useful and flexible,
        it gives a possibility to create a CARD which you know about just color
        or just rank etc. Even you can Think about red spades (like in "Interstate 60"),
        but you should remember about it when you will use your creation!
    */
    // open card
    CARD(SUIT s, RANK r, COLOR c = NO_COLOR):m_suit(s),
                                             m_rank(r),
                                             m_color(c),
                                             m_side(FACE){}

    enum COMPARE{
        bySuit,
        byRank,
        byColor,
        byAll
    };

    bool isEqual(const CARD& l, const CARD& r, COMPARE comp = byAll) const
    {
        switch (comp)
        {
        case bySuit:
            return l.m_suit == r.m_suit;
        case byRank:
            return l.m_rank == r.m_rank;
        case byColor:
            return l.m_color == r.m_color;
        case byAll:
            return l.m_suit == r.m_suit && l.m_rank == r.m_rank;
        }
    }

    SUIT getSuit(){return m_suit;}
    RANK getRank(){return m_rank;}
    COLOR getColor(){return m_color;}
    SIDE getSide(){return m_side;}

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
    ~CARD(){}

private:
    const SUIT m_suit;
    const RANK m_rank;
    const COLOR m_color;
    const SIDE m_side;
};

// transfer to DECK_H
/// relationship between SUIT-RANK-COLOR:
//const bool relSRC[END_SUIT][END_RANK][END_COLOR]


#endif // CARD_H_INCLUDED
