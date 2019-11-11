#ifndef MAT_CARD_H_INCLUDED
#define MAT_CARD_H_INCLUDED

#include "../thinkable/card.h"

class DECK;

class MAT_CARD{
public:
    // class MAT_CARD absolutely trust to MAT_SET class (except creating exemplars)
    // which also absolutely trust to HOLDER class
    CARD getMyFace(){ return m_face; }
    CARD getMyBack(){ return m_back; }

private:
    MAT_CARD(SUIT s, RANK r, COLOR c):m_face(s, r, c),
                                      m_back(UNKNOWN_SUIT, UNKNOWN_RANK, UNKNOWN_COLOR){}

    const CARD m_face;
    const CARD m_back;

    friend DECK;
};

#endif // MAT_CARD_H_INCLUDED
