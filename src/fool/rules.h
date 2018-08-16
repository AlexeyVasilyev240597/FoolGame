#ifndef RULES_H
#define RULES_H
#include <QObject>
#include "../abstract/CardDeck.h"
//#include "../abstract/GameElement.h"
#include "../drawing/GameItems.h"
#include "Table.h"
#include "Player.h"

//later will be in RULES
//#define PLAYER_VOLUME_INIT 6

//template<size_t deck_volume, size_t players_number>
class   FOOL_RULES: public QObject{
Q_OBJECT
protected:
    FOOL_RULES(){}

    enum INIT_VOLUMES{PL_V = 6, PR_V = _36_CARD_DECK - 6 * 2/*deck_volume - 6 * players_number*/};

    SUIT trump;

    //FOOL_PLAYER *active, *passive;
    //elements
    FOOL_PLAYER *pl1, *pl2;

    FOOL_PRICUP *pr;
    FOOL_FIGHT_FIELD *field;
    FOOL_BEATEN *beaten;

    enum END_LOCAL_STATE{ NOT_END, GIVE_AWAY, BEATEN_OFF };
    END_LOCAL_STATE isEndLocal();

    bool isCorrectChoose(FOOL_PLAYER*);

    //enum HOW_IS_WINNER{NOBODY, PLAYER_1, PLAYER_2, DEAD_HEAD};
    void checkGameOver();

    //PLAYER_STATE getMyState();

signals:
    void transferMove();
    void gameOver(QString message);

public slots:
    void setTrump(SUIT t){trump = t;}
};

#endif // RULES_H
