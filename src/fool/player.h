#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <string>
#include <map>

#include "../abstract/CardDeck.h"
#include "../abstract/GameElement.h"
#include "../drawing/GameItems.h"
//#include "Table.h"

class FOOL_PLAYER :public QObject, public ELEMENT{
Q_OBJECT
private:
    //std::vector<CARD*> my_set to std::map<CARD*, BUTTON*> card_button_set
    bool is_user{false};
    SUIT trump;

    //FOOL_FIGHT_FIELD *field{NULL};

    void sortSet();

    QPointF getMyPos(size_t index);

    void itemsUpdate();
signals:
    void chooseIsMade();

public:
    bool my_move{false};

    FOOL_PLAYER_SET_VIEW *pl_set_view;    

    CARD *changed_card{NULL};

    enum PLAYER_STATE{ATTACK, DEFENCE, ADDING, TAKING, NO_DEF} state{NO_DEF};

    //пока не написана getMinTrump(), первым ходит первый игрок
    FOOL_PLAYER(size_t iv) : ELEMENT(TO_HOLDER, iv){}

    std::vector<CARD*> giveCard();

    void setTrump(SUIT tr){ trump = tr; }

    void showMinTrump();

    void initSetView(QPointF, int, int);

    void addToSet(std::vector<CARD*> cards);

    void initState(PLAYER_STATE s);

    void changeState();

    void customizeButtons();

    //void drawSet();

public slots:
    void changeCard(Qt::MouseButton);
    void changeMoveValue();
};

#endif // PLAYER_H
