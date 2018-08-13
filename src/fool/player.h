#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <string>
#include <map>

#include "../abstract/CardDeck.h"
#include "../abstract/GameElement.h"
#include "../drawing/GameItems.h"
//#include "Table.h"
//#include "fool.h"

/*
1. позже: FOOL_PLAYER будет разделен на USER и AI,
    которые будут наследоваться от PLAYER (возможно абстрактного);
2. метод giveCard() у класса AI будет включать switch по state:
    игрок будет иметь возможность сходить с любой карты,
                                  подкинуть карту,
                                  отбить карту;
3. PLAYER будет иметь указатель на RULES и
получать через него необходимую информацию (смена хода, карты на столе);
4. ...
*/
class FOOL_RULES;

class FOOL_PLAYER :public QObject, public ELEMENT{
Q_OBJECT
private:
    //std::vector<CARD*> my_set to std::map<CARD*, BUTTON*> card_button_set
    bool is_user{false};
    SUIT trump{NO_SUIT};

    //FOOL_FIGHT_FIELD *field{NULL};
    //FOOL_RULES rules;

    void sortSet();

    //QPointF getMyPos(size_t index);

    //void itemsUpdate();
signals:
    void chooseIsMade();

    void itIsBeaten();

    void iTakeIt();

    void takeAway();

public:
    //перенести в RULES
    bool my_move{false};

    FOOL_PLAYER_SET_VIEW *pl_set_view;

    CARD *choosed_card{NULL};

    //перенести в RULES
    enum PLAYER_STATE{ATTACK, DEFENCE, ADDING, TAKING, NO_DEF} state{NO_DEF};

    //пока не написана getMinTrump(), первым ходит первый игрок
    FOOL_PLAYER(size_t iv) : ELEMENT(TO_HOLDER, iv){}

    std::vector<CARD*> giveCard();

    void setTrump(SUIT tr){ trump = tr; }

    void showMinTrump();

    //перенести в FOOL_PLAYER_SET_VIEW
    void initSetView(QPointF, int, int);

    //только добавление в my_set,
    //остальное перенести в FOOL_PLAYER_SET_VIEW
    void addToSet(std::vector<CARD*> cards);

    //перенести в RULES
    void initState(PLAYER_STATE s);

    //перенести в RULES
    void changeState();

    //перенести в FOOL_PLAYER_SET_VIEW и передавать PLAYER_STATE
    void customizeButtons();


public slots:
    void changeCard(Qt::MouseButton);

    void changeMoveValue();
};

#endif // PLAYER_H
