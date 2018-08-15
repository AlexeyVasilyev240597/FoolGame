#ifndef PLAYER_H
#define PLAYER_H

#include <QString>
#include <vector>
#include <string>
#include <map>

#include "../abstract/CardDeck.h"
#include "../abstract/GameElement.h"
#include "../drawing/GameItems.h"

/*
1. �����: FOOL_PLAYER ����� �������� �� USER � AI,
    ������� ����� ������������� �� PLAYER (�������� ������������);
2. ����� giveCard() � ������ AI ����� �������� switch �� state:
    ����� ����� ����� ����������� ������� � ����� �����,
                                  ��������� �����,
                                  ������ �����;
                                  (�������?)))))
3. ...
*/

class FOOL_PLAYER: public QObject, public ELEMENT{
Q_OBJECT
private:
    //bool is_user{false};

    SUIT trump{NO_SUIT};

    //void sortSet();
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
    bool my_move{false};

    QString name;

    CARD *choosed_card{NULL};       

    //���� �� �������� getMinTrump(), ������ ����� ������ �����
    FOOL_PLAYER(size_t iv, const QString n) : ELEMENT(TO_HOLDER, iv){name = n;}

    std::vector<CARD*> giveCard();

    void setTrump(SUIT tr){ trump = tr; }

    void showMinTrump();

    //������ ���������� � my_set,
    void addToSet(std::vector<CARD*> cards);

    void initState(PLAYER_STATE s);

    //��������� � RULES
    void changeState(); 

public slots:
    void changeCard(CARD*);

    void changeMoveValue();

    //����� ������ ����������� ��� ������������ ����������� ������� �� ������!
    //void iMistake();
};

#endif // PLAYER_H
