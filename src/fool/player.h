#ifndef PLAYER_H
#define PLAYER_H

#include <QString>
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

class FOOL_PLAYER: public QObject, public ELEMENT{
Q_OBJECT
private:

    //std::vector<CARD*> my_set to std::map<CARD*, BUTTON*> card_button_set
    bool is_user{false};

    SUIT trump{NO_SUIT};

    void sortSet();

    //QPointF getMyPos(size_t index);

    //void itemsUpdate();
public:
        enum PLAYER_STATE{ATTACK, DEFENCE, ADDING, TAKING, NO_DEF} state{NO_DEF};

signals:
    void addedToSet(std::vector<CARD*>&);

    void removedFromSet(std::vector<CARD*>&);

    void chooseIsMade();

    void itIsBeaten();

    void iTakeIt();

    void takeAway();

    void choosedWrongCard(CARD*);

    void customizeButtons(bool cards, bool beaten, bool take, bool take_away);

public:
    //��������� � RULES
    bool my_move{false};

    QString name;

    //FOOL_PLAYER_SET_VIEW *pl_set_view;

    CARD *choosed_card{NULL};       

    //���� �� �������� getMinTrump(), ������ ����� ������ �����
    FOOL_PLAYER(size_t iv, const QString n) : ELEMENT(TO_HOLDER, iv){
        name = n;
        //qDebug() << name;
    }

    std::vector<CARD*> giveCard();

    void setTrump(SUIT tr){ trump = tr; }

    void showMinTrump();

    //��������� � FOOL_PLAYER_SET_VIEW
    void initSetView(FOOL_PLAYER_SET_VIEW*);

    //������ ���������� � my_set,
    //��������� ��������� � FOOL_PLAYER_SET_VIEW
    void addToSet(std::vector<CARD*> cards);

    //��������� � RULES
    void initState(PLAYER_STATE s);

    //��������� � RULES
    void changeState();

    //��������� � FOOL_PLAYER_SET_VIEW � ���������� PLAYER_STATE
    //void customizeButtons();


public slots:
    void changeCard(CARD*);

    void changeMoveValue();

    //����� ������ ����������� ��� ������������ ����������� ������� �� ������!
    //void iMistake();

//friend class FOOL_PLAYER_SET_VIEW;

};

#endif // PLAYER_H
