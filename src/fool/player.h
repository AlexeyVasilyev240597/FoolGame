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
1. �����: FOOL_PLAYER ����� �������� �� USER � AI,
    ������� ����� ������������� �� PLAYER (�������� ������������);
2. ����� giveCard() � ������ AI ����� �������� switch �� state:
    ����� ����� ����� ����������� ������� � ����� �����,
                                  ��������� �����,
                                  ������ �����;
3. PLAYER ����� ����� ��������� �� RULES �
�������� ����� ���� ����������� ���������� (����� ����, ����� �� �����);
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
    //��������� � RULES
    bool my_move{false};

    FOOL_PLAYER_SET_VIEW *pl_set_view;

    CARD *choosed_card{NULL};

    //��������� � RULES
    enum PLAYER_STATE{ATTACK, DEFENCE, ADDING, TAKING, NO_DEF} state{NO_DEF};

    //���� �� �������� getMinTrump(), ������ ����� ������ �����
    FOOL_PLAYER(size_t iv) : ELEMENT(TO_HOLDER, iv){}

    std::vector<CARD*> giveCard();

    void setTrump(SUIT tr){ trump = tr; }

    void showMinTrump();

    //��������� � FOOL_PLAYER_SET_VIEW
    void initSetView(QPointF, int, int);

    //������ ���������� � my_set,
    //��������� ��������� � FOOL_PLAYER_SET_VIEW
    void addToSet(std::vector<CARD*> cards);

    //��������� � RULES
    void initState(PLAYER_STATE s);

    //��������� � RULES
    void changeState();

    //��������� � FOOL_PLAYER_SET_VIEW � ���������� PLAYER_STATE
    void customizeButtons();


public slots:
    void changeCard(Qt::MouseButton);

    void changeMoveValue();
};

#endif // PLAYER_H
