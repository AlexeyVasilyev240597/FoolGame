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
    //перенести в RULES
    bool my_move{false};

    QString name;

    //FOOL_PLAYER_SET_VIEW *pl_set_view;

    CARD *choosed_card{NULL};       

    //пока не написана getMinTrump(), первым ходит первый игрок
    FOOL_PLAYER(size_t iv, const QString n) : ELEMENT(TO_HOLDER, iv){
        name = n;
        //qDebug() << name;
    }

    std::vector<CARD*> giveCard();

    void setTrump(SUIT tr){ trump = tr; }

    void showMinTrump();

    //перенести в FOOL_PLAYER_SET_VIEW
    void initSetView(FOOL_PLAYER_SET_VIEW*);

    //только добавление в my_set,
    //остальное перенести в FOOL_PLAYER_SET_VIEW
    void addToSet(std::vector<CARD*> cards);

    //перенести в RULES
    void initState(PLAYER_STATE s);

    //перенести в RULES
    void changeState();

    //перенести в FOOL_PLAYER_SET_VIEW и передавать PLAYER_STATE
    //void customizeButtons();


public slots:
    void changeCard(CARD*);

    void changeMoveValue();

    //потом сигнал понадобится для графического отображения сигнала об ошибке!
    //void iMistake();

//friend class FOOL_PLAYER_SET_VIEW;

};

#endif // PLAYER_H
