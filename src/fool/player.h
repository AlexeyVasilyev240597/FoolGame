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
private:
    //bool is_user{false};

    SUIT trump{NO_SUIT};

    //void sortSet();
public:
        enum PLAYER_STATE{ATTACK, DEFENCE, ADDING, TAKING, NO_DEF} state{NO_DEF};

signals:
    void addedToSet(std::vector<CARD*>& set);

    void removedFromSet(std::vector<CARD*>& set, std::vector<CARD*>& cards_to_remove);

    void chooseIsMade();

    void itIsBeaten();

    void iTakeIt();

    void takeAway();

    //потом сигнал понадобится для графического отображения сигнала об ошибке!
    //void choosedWrongCard(CARD*);

    void customizeButtons(bool cards, bool beaten, bool take, bool take_away);

public:
    bool my_move{false};

    QString name;

    CARD *choosed_card{NULL};       

    FOOL_PLAYER(size_t iv, const QString n) : ELEMENT(TO_HOLDER, iv){name = n;}

    std::vector<CARD*> giveCard();

    void setTrump(SUIT tr){ trump = tr; }

    void showMinTrump();

    void addToSet(std::vector<CARD*> cards);

    void initState(PLAYER_STATE s);

    //перенести в RULES
    void changeState(); 

public slots:
    void changeCard(CARD*);

    void changeMoveValue();

    //потом сигнал понадобится для графического отображения сигнала об ошибке!
    //void iMistake();
};

#endif // PLAYER_H
