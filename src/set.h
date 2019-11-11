#ifndef SET_H_INCLUDED
#define SET_H_INCLUDED

#include "../card/thinkable/card.h"

typedef unsigned short int uint;

class HOLDER;

// NOTES: volume is a bed term
//template <uint DeckVolume>
class SET{
public:
    SET(uint max_size = 54)
    {
        m_size = 0;
        m_max_size = max_size;
        m_cards = new CARD[m_max_size];
    }

    void addCard(CARD card);

    void removeByVal(CARD card);

    void removeByIndex(uint indx);

    // copy data, not pointer!
    void copySet(SET* other_set);

    // i am a source
    ////void moveCardTo(SET* sink, CARD card);

    // i am a sink
    //void moveCardFrom(SET* source, CARD card);

    CARD getLast();

    CARD getByIndex(uint indx);

    SET getBySuit(SUIT s);

    SET getByRank(RANK r);

    SET getByColor(COLOR c);

    bool doIContain(CARD card);

    enum COMPARE{
        bySuit,
        byRank,
        byColor,
        byAll
    };

    static bool isEqual(const CARD& l, const CARD& r, COMPARE comp = byAll);

    static bool isGreater(const CARD& l, const CARD& r, bool same_suit = true);


    /// ADD METHODS: SET operations, first argument is (*this)
    // s | (*this)
    SET unionsWith(SET s);
    // s & (*this)
    SET intersectionWith(SET s);
    // all deck set \ (*this)
    SET complement();
    // set (*this) \ s
    //SET difference(SET s);



    uint getMaxSize(){ return m_max_size; }

    uint getSize(){ return m_size; }

    ~SET()
    {
        delete [] m_cards;
    }

private:
    CARD* m_cards;
    uint m_max_size;
    uint m_size;
};

#endif // SET_H_INCLUDED
