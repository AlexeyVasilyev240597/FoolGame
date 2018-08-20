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
1. позже: FOOL_PLAYER будет разделен на USER и AI,
    которые будут наследоваться от PLAYER (возможно абстрактного);
2. метод giveCard() у класса AI будет включать switch по state:
    игрок будет иметь возможность сходить с любой карты,
                                  подкинуть карту,
                                  отбить карту;
                                  (думаешь?)))))
3. ...
*/

class FOOL_PLAYER: public QObject, public ELEMENT{
Q_OBJECT
signals:
    void chooseIsMade();

    void itIsBeaten();

    void iTakeIt();

    void takeAway();

    void addedToSet(std::vector<CARD*>& set);

    void removedFromSet(std::vector<CARD*>& set, std::vector<CARD*>& cards_to_remove);

    void customizeButtons(bool cards, bool beaten, bool take, bool take_away);

    //потом сигнал понадобится для графического отображения сигнала об ошибке!
    //void choosedWrongCard(CARD*);

public:
    enum PLAYER_STATE{ATTACK, DEFENCE, ADDING, TAKING, NO_DEF} state{NO_DEF};

    SUIT trump{NO_SUIT};

    bool my_move{false};

    QString name;

    CARD *choosed_card{NULL};

    void addToSet(std::vector<CARD*> cards);

    FOOL_PLAYER(size_t iv, const QString n) : ELEMENT(TO_HOLDER, iv){name = n;}

    std::vector<CARD*> giveCard();

    void setTrump(SUIT tr){ trump = tr; }

    virtual void showMinTrump();

    void initState(PLAYER_STATE s);

    //перенести в RULES
    void changeState(); 

public slots:
    void changeCard(CARD*);

    void changeMoveValue();

    //потом сигнал понадобится для графического отображения сигнала об ошибке!
    //void iMistake();
};
/*
class USER: public QObject, public FOOL_PLAYER{
Q_OBJECT
signals:
    void addedToSet(std::vector<CARD*>& set);

    void removedFromSet(std::vector<CARD*>& set, std::vector<CARD*>& cards_to_remove);

    void customizeButtons(bool cards, bool beaten, bool take, bool take_away);

public:
    void addToSet(std::vector<CARD*> cards);

public slots:
    void changeCard(CARD*);

    void changeMoveValue();
};
*/

class AI: public FOOL_PLAYER{
Q_OBJECT
private:
    //std::vector<CARD*> on_field;
    CARD* on_field{NULL};

    size_t opponent_cards_counter{0};

    std::vector<CARD*>::iterator getMinCard(CARD* less = NULL);

public:
    AI(size_t i_v, QString name):FOOL_PLAYER(i_v, name){}

public slots:
    void aiChangeMoveValue();

    void trownCardToField(CARD* card, bool inAttack, size_t index);
};
#endif // PLAYER_H
