#include "Fool.h"
#include "../abstract/gameelement.h"
#include <QGraphicsItem>

//#define PLAYER_VOLUME_INIT 6


//-----------------------------------------GAME-----------------------------------------
void FOOL_GAME::init(){
    dealer = new DEALER(_36_CARD_DECK);

    pl1 = new FOOL_PLAYER(PLAYER_VOLUME_INIT, "user#1");
    pl1_item = new FOOL_PLAYER_SET_VIEW(QPointF(240, 495), 80 * PLAYER_VOLUME_INIT + 40/*for buttons*/, 145/*116*1.25*/);
    pl1->initSetView(pl1_item);
    //pl1->initSetView(QPointF(240, 495), 80 * PLAYER_VOLUME_INIT + 40/*for buttons*/, 145/*116*1.25*/);
    //pl1->pl_set_view->setPlayer(pl1);
    emit addElem(pl1_item);

    pl2 = new FOOL_PLAYER(PLAYER_VOLUME_INIT, "user#2");
    pl2_item = new FOOL_PLAYER_SET_VIEW(QPointF(240, 0), 80 * PLAYER_VOLUME_INIT + 40, 145);
    pl2->initSetView(pl2_item);
    //pl2->pl_set_view->setPlayer(pl2);
    emit addElem(pl2_item);

    pr = new FOOL_PRICUP(_36_CARD_DECK - PLAYER_VOLUME_INIT - PLAYER_VOLUME_INIT);
    pr_item = new FOOL_PRICUP_SET_VIEW(QPointF(0, 262), 116, 116);
    pr->initSetView(pr_item);
    emit addElem(pr_item);

    field = new FOOL_FIGHT_FIELD();
    f_item = new FOOL_FIGHT_FIELD_SET_VIEW(QPointF(300, 150), 360, 290);
    field->initSetView(f_item);
    emit addElem(f_item);

    beaten = new FOOL_BEATEN();
    b_item = new FOOL_BEATEN_SET_VIEW(QPointF(880, 262), 80, 116);
    beaten->initSetView(b_item);
    emit addElem(b_item);
}
/*
FOOL_GAME::~FOOL_GAME(){
    delete dealer;
    //delete pl1->pl_set_view;
    delete pl1;
    //delete pl2->pl_set_view;
    delete pl2;
    //delete pr->pr_set_view;
    delete pr;
    //delete field->f_f_set_view;
    delete field;
    //delete beaten->b_set_view;
    delete beaten;
}
*/

void FOOL_GAME::fillSetsOfPlayers()
{
    FOOL_PLAYER *first = pl1->state == FOOL_PLAYER::ATTACK || pl1->state == FOOL_PLAYER::ADDING ? pl1 : pl2,
                *last  = pl1->state == FOOL_PLAYER::DEFENCE|| pl1->state == FOOL_PLAYER::TAKING ? pl1 : pl2;

    if (pr->getVolume())
        if (first->getVolume() < first->getInitVolume())
            first->addToSet(
                        pr->giveCard(
                            std::min(
                                first->getInitVolume() - first->getVolume(),
                                pr->getVolume())));

    if (pr->getVolume())
        if (last->getVolume() < last->getInitVolume())
            last->addToSet(
                        pr->giveCard(
                            std::min(
                                last->getInitVolume()  -  last->getVolume(),
                                pr->getVolume())));
    checkGameOver();
}


void FOOL_GAME::game()
{
    QObject::connect(dealer, &DEALER::iGaveOut,
                     pr, &FOOL_PRICUP::dealerGaveOut);

    QObject::connect(pr, &FOOL_PRICUP::getTrumpSuit,
                     this, &FOOL_GAME::setTrump);

    dealer->giveOutCards(pl1);
    dealer->giveOutCards(pl2);
    dealer->giveOutCards(pr);
    emit dealer->iGaveOut();

    //pl1->setTrump(trump);
    //pl2->setTrump(trump);

    pl1->initState(FOOL_PLAYER::ATTACK);
    //active = pl1;
    pl2->initState(FOOL_PLAYER::DEFENCE);
    //passive = pl2;

    //перешел ход
    QObject::connect(this, &FOOL_GAME::transferMove,
                     pl1, &FOOL_PLAYER::changeMoveValue);

    QObject::connect(this, &FOOL_GAME::transferMove,
                     pl2, &FOOL_PLAYER::changeMoveValue);

    //игрок выбрал карту
    QObject::connect(pl1, &FOOL_PLAYER::chooseIsMade,
                     this, &FOOL_GAME::playerChoosedCard);

    QObject::connect(pl2, &FOOL_PLAYER::chooseIsMade,
                     this, &FOOL_GAME::playerChoosedCard);

    //игрок сказал "бито"  => бросаем карты с поля в биту
    QObject::connect(pl1, &FOOL_PLAYER::itIsBeaten,
                     this, &FOOL_GAME::throwToBeaten);

    QObject::connect(pl2, &FOOL_PLAYER::itIsBeaten,
                     this, &FOOL_GAME::throwToBeaten);

    //игрок сказал "беру" => даем возможность атакующему "прикончить" противника
    QObject::connect(pl1, &FOOL_PLAYER::iTakeIt,
                     this, &FOOL_GAME::finishHim);

    QObject::connect(pl2, &FOOL_PLAYER::iTakeIt,
                     this, &FOOL_GAME::finishHim);

    //игрок сказал "забирай" => отдаем карты берущему
    QObject::connect(pl1, &FOOL_PLAYER::takeAway,
                     this, &FOOL_GAME::giveToPlayer);

    QObject::connect(pl2, &FOOL_PLAYER::takeAway,
                     this, &FOOL_GAME::giveToPlayer);

/*потом конект понадобится для графического отображения сигнала об ошибке!
    //игрок сделал неверный ход
    QObject::connect(this, &FOOL_GAME::wrongMove,
                     pl1, &FOOL_PLAYER::iMistake);

    QObject::connect(this, &FOOL_GAME::wrongMove,
                     pl2, &FOOL_PLAYER::iMistake);
*/
}

void FOOL_GAME::playerChoosedCard(){
    FOOL_PLAYER *active = pl1->my_move ? pl1 : pl2;

    if (isCorrectChoose(active)){
        field->addToSet(active->giveCard(), active->state);

        switch (isEndLocal()){
        case GIVE_AWAY:
            giveToPlayer();
            break;

        case BEATEN_OFF:
            throwToBeaten();
            break;

        default://case NOT_END:
            if (active->state != FOOL_PLAYER::ADDING)
                emit transferMove();
            break;
        }
    }
/*потом это место понадобится для графического отображения сигнала об ошибке!
    else{
        emit wrongMove();
    }
*/

}

void FOOL_GAME::finishHim(){
    FOOL_PLAYER *domina = pl1->state == FOOL_PLAYER::ATTACK  ? pl1 : pl2,
            *submission = pl1->state == FOOL_PLAYER::DEFENCE ? pl1 : pl2;

    submission->state = FOOL_PLAYER::TAKING;
    domina->state = FOOL_PLAYER::ADDING;

    emit transferMove();

    if (isEndLocal() == GIVE_AWAY)
        giveToPlayer();
}

void FOOL_GAME::throwToBeaten(){
    if (field->getVolume()){
        beaten->addToSet(field->giveCard());

        endLocalFight();
        emit transferMove();
    }
}

void FOOL_GAME::giveToPlayer(){
    FOOL_PLAYER *recipient = pl1->state == FOOL_PLAYER::DEFENCE ||
                             pl1->state == FOOL_PLAYER::TAKING ? pl1 : pl2;

    recipient->addToSet(field->giveCard());

    endLocalFight();
    //emit transferMove();
}

void FOOL_GAME::endLocalFight(){
    fillSetsOfPlayers();
    pl1->changeState();
    pl2->changeState();
}
/*
std::vector<MY_ITEM*> FOOL_GAME:: getItems(){
    std::vector<MY_ITEM*> items;

    items.push_back(pl1->pl_set_view);
    items.push_back(pl2->pl_set_view);
    items.push_back(pr->pr_set_view);
    items.push_back(field->f_f_set_view);
    items.push_back(beaten->b_set_view);

    return items;
}
*/
