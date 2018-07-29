#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <string>
#include <map>

#include "../abstract/CardDeck.h"
#include "../abstract/GameElement.h"
#include "../drawing/GameItems.h"
#include "Table.h"

class FOOL_PLAYER :/*public QObject, */public ELEMENT{
//Q_OBJECT
private:
    //std::vector<CARD*> my_set to std::map<CARD*, BUTTON*> card_button_set
    bool is_user{false};
    SUIT trump;
    CARD *changed_card;
    FOOL_FIGHT_FIELD *field;

    FOOL_PLAYER_SET_VIEW *pl_set_view;
    void sortSet();

    //void fillCardBtns();

//signals:
  void setUpdated();//std::vector<CARD*>);

public:
    //пока не написана getMinTrump(), первым ходит первый игрок
    FOOL_PLAYER(size_t iv,
                FOOL_FIGHT_FIELD* f_f = NULL,
                bool is_u = false) : ELEMENT(TO_HOLDER, iv){
        is_user = is_u;
        field = f_f;
    }

    std::vector<CARD*> giveCard();

    //slote для button[i]->click
    void changeCard(CARD*);

    void setTrump(SUIT tr){ trump = tr; }

    void showMinTrump();

    void initSetView(QPoint, int, int);

    void addToSet(std::vector<CARD*> cards);

    //void drawSet();
};

#endif // PLAYER_H
