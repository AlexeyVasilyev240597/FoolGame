#include "Fool.h"
#include "../abstract/gameelement.h"
#include <QGraphicsItem>

//-----------------------------------------GAME-----------------------------------------
void FOOL_GAME::init(FOOL_ITEM_MANAGER *manager){

    dealer = new DEALER(_36_CARD_DECK);

    pl1 = new FOOL_PLAYER(PL_V, "user#1");
    manager->createItem(pl1, 1);

    pl2 = new FOOL_PLAYER(PL_V, "user#2");
    manager->createItem(pl2, 2);

    pr = new FOOL_PRICUP(PR_V);
    manager->createItem(pr);

    field = new FOOL_FIGHT_FIELD();
    manager->createItem(field);

    beaten = new FOOL_BEATEN();
    manager->createItem(beaten);

    QObject::connect(this, &FOOL_GAME::gameOver,
                     manager->f_item, &FOOL_FIGHT_FIELD_SET_VIEW::drawMessage);
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
        if (first->getVolume() < PL_V)
            first->addToSet(
                        pr->giveCard(
                            std::min(
                                first->getInitVolume() - first->getVolume(),
                                pr->getVolume())));

    if (pr->getVolume())
        if (last->getVolume() < PL_V)
            last->addToSet(
                        pr->giveCard(
                            std::min(
                                last->getInitVolume()  -  last->getVolume(),
                                pr->getVolume())));
    checkGameOver();
}

void FOOL_GAME::game()
{
    QObject::connect(pr, &FOOL_PRICUP::getTrumpSuit,
                     this, &FOOL_GAME::setTrump);

    dealer->giveOutCards(pr);   


    pr->setBadge(dealer->getBadge(trump));

    pl1->setTrump(trump);
    pl2->setTrump(trump);

    dealer->giveOutCards(pl1);
    dealer->giveOutCards(pl2);

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
/*потом это место понадобится для графического отображения сигнала об ошибке!*/
    else{
        qDebug() << "player " << active->name << " thrown wrong card";
        //emit wrongMove();
    }


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
}

void FOOL_GAME::endLocalFight(){
    fillSetsOfPlayers();
    pl1->changeState();
    pl2->changeState();
}

//-----------------------------------------ITEM_MANAGER-----------------------------------------
void FOOL_ITEM_MANAGER::createItem(FOOL_PLAYER *player, size_t num){
    FOOL_PLAYER_SET_VIEW *pl_item = new FOOL_PLAYER_SET_VIEW(QPointF(240, 495 * !(num - 1)),
                                                             80 * player->getInitVolume() + 40/*for buttons*/,
                                                             145/*116*1.25*/);

    QObject::connect(player, &FOOL_PLAYER::addedToSet,
                     pl_item, &FOOL_PLAYER_SET_VIEW::addToMap);

    QObject::connect(player, &FOOL_PLAYER::removedFromSet,
                     pl_item, &FOOL_PLAYER_SET_VIEW::removeFromMap);


    QObject::connect(pl_item, &FOOL_PLAYER_SET_VIEW::choosedCard,
                     player, &FOOL_PLAYER::changeCard);

    QObject::connect(pl_item->itIsBeaten, &BUTTON::buttonClicked,
                     player, &FOOL_PLAYER::itIsBeaten);

    QObject::connect(pl_item->iTake, &BUTTON::buttonClicked,
                     player, &FOOL_PLAYER::iTakeIt);

    QObject::connect(pl_item->takeAway, &BUTTON::buttonClicked,
                     player, &FOOL_PLAYER::takeAway);

    /*потом конект понадобится для графического отображения сигнала об ошибке!
    QObject::connect(player, &FOOL_PLAYER::choosedWrongCard,
                     pl_item, &FOOL_PLAYER_SET_VIEW::changeCardState);
    */

    QObject::connect(player, &FOOL_PLAYER::customizeButtons,
                     pl_item, &FOOL_PLAYER_SET_VIEW::customizeButtons);

    emit addElem(pl_item);

    if (num == 1)
        pl1_item = pl_item;

    else if (num == 2)
        pl2_item = pl_item;
}

void FOOL_ITEM_MANAGER::createItem(FOOL_PRICUP *pricup){
    pr_item = new FOOL_PRICUP_SET_VIEW(QPointF(0, 262), 116, 116);

    QObject::connect(pricup, &FOOL_PRICUP::addedToSet,
                     pr_item, &FOOL_PRICUP_SET_VIEW::gaveOut);


    QObject::connect(pricup, &FOOL_PRICUP::removedFromSet,
                     pr_item, &FOOL_PRICUP_SET_VIEW::removeFromPile);

    emit addElem(pr_item);

}

void FOOL_ITEM_MANAGER::createItem(FOOL_FIGHT_FIELD *field){
    f_item = new FOOL_FIGHT_FIELD_SET_VIEW(QPointF(300, 150), 360, 290);

    QObject::connect(field, &FOOL_FIGHT_FIELD::addedToSet,
                     f_item, &FOOL_FIGHT_FIELD_SET_VIEW::addCardItem);

    QObject::connect(field, &FOOL_FIGHT_FIELD::removedFromSet,
                     f_item, &FOOL_FIGHT_FIELD_SET_VIEW::removeAllItems);

    emit addElem(f_item);
}

void FOOL_ITEM_MANAGER::createItem(FOOL_BEATEN *beaten){
    b_item = new FOOL_BEATEN_SET_VIEW(QPointF(880, 262), 80, 116);

    QObject::connect(beaten, &FOOL_BEATEN::addedToSet,
                     b_item, &FOOL_BEATEN_SET_VIEW::firstAdded);

    emit addElem(b_item);
}
