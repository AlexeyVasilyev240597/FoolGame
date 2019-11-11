#include "set.h"

void SET::addCard(CARD card)
{
    /// ADD MESSAGE!
    if (m_size + 1 > m_max_size)
        return;

    m_cards[m_size++] = card;
}

void SET::removeByVal(CARD card)
{
    for (uint i = 0; i < m_size; i++)
    {
        if (isEqual(m_cards[i], card))
            removeByIndex(i);
    }
}

void SET::removeByIndex(uint indx)
{
    /// ADD MESSAGE!
    if (indx >= m_max_size || indx >= m_size || m_size == 0)
        return;

    for (uint i = indx; i < m_size-1; i++)
        m_cards[i] = m_cards[i+1];
    m_size--;
}

void SET::copySet(SET* other_set)
{
    /// ADD MESSAGE!
    if (m_size > other_set->getMaxSize() || other_set == nullptr)
        return;
    for (uint i = 0; i < m_size; i++)
        other_set->addCard(m_cards[i]);
}

/*
void moveCardTo(SET* sink, CARD card)
{
    if (sink == NULL || !doContain(card))
        return;
    sink->add(card);
    removeByVal(card);
}

void moveCardFrom(SET* source, CARD card)
{

}
*/
CARD SET::getLast()
{
    if (m_size > 0)
        return m_cards[m_size-1];
    /// unexpected behaviour!
    else
        return CARD();
}

CARD SET::getByIndex(uint indx)
{
    /// ADD MESSAGE!
    if (indx >= m_max_size || indx >= m_size)
        return CARD();
    return m_cards[indx];
}

SET SET::getBySuit(SUIT s)
{
    SET new_set(m_max_size);
    CARD card(s, NO_RANK);
    for (uint i = 0; i < m_size; i++)
        if (isEqual(m_cards[i], card, bySuit))
            new_set.addCard(m_cards[i]);
    return new_set;
}

SET SET::getByRank(RANK r)
{
    SET new_set(m_max_size);
    CARD card(NO_SUIT, r);
    for (uint i = 0; i < m_size; i++)
        if (isEqual(m_cards[i], card, byRank))
            new_set.addCard(m_cards[i]);
    return new_set;
}

SET SET::getByColor(COLOR c)
{
    SET new_set(m_max_size);
    CARD card(NO_SUIT, NO_RANK, c);
    for (uint i = 0; i < m_size; i++)
        if (isEqual(m_cards[i], card, byColor))
            new_set.addCard(m_cards[i]);
    return new_set;
}

SET SET::unionsWith(SET s)
{
    SET res = SET(m_max_size + s.getMaxSize());
    CARD tmp_card;

    for (uint i = 0; i < m_size; i++)
    {
        res.addCard(m_cards[i]);
        for (uint j = 0; j < s.getSize(); j++)
        {
            tmp_card = s.getByIndex(j);
            if (!isEqual(m_cards[i], tmp_card))
                res.addCard(tmp_card);
        }
    }
    return res;
}

SET SET::intersectionWith(SET s)
{
    // max_size of res is the maximum of m_max_size and max_size of s
    SET res = SET(m_max_size > s.getMaxSize() ? m_max_size : s.getMaxSize());
    CARD tmp_card;

    for (uint i = 0; i < s.getSize(); i++)
    {
        tmp_card = s.getByIndex(i);
        if (doIContain(tmp_card))
            res.addCard(tmp_card);
    }
    return res;
}
/*
SET SET::complement()
{
    // again magic constant 54!
    if (m_size == 54)
        return SET(0);
    SET res = SET(54 - m_size);
    CARD tmp_card;

    for (uint s = (uint)DIAMONDS; s < (uint)END_SUIT; s++)
        for (uint r = (uint)TWO; r < (uint)END_RANK; r++)
        {
            tmp_card = CARD((SUIT)s, (RANK)r);
            if (!doIContain(tmp_card))
                res.addCard(tmp_card);
        }

    return res;
}
*/
bool SET::doIContain(CARD card)
{
    for (uint i = 0; i < m_size; i++)
        if (isEqual(m_cards[i], card))
            return true;
    return false;
}

bool SET::isEqual(const CARD& l, const CARD& r, COMPARE comp)
{
    switch (comp)
    {
    case bySuit:
        return l.getSuit() == r.getSuit();
    case byRank:
        return l.getRank() == r.getRank();
    case byColor:
        return l.getColor() == r.getColor();
    case byAll:
        return l.getSuit()  == r.getSuit() &&\
               l.getRank()  == r.getRank() &&\
               l.getColor() == r.getColor();
    }
    // MESSAGE: unknown comp
    return false;
}

bool SET::isGreater(const CARD& l, const CARD& r, bool same_suit)
{
    if (same_suit && l.getSuit() != r.getSuit())
        return false;
    else // doesn't matter
        return l.getRank() > r.getRank();
}
