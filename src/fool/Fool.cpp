#include "Fool.h"
#include "../abstract/gameelement.h"
#include "player.h"
#include "table.h"
#include <QGraphicsItem>

//later be in RULES
#define PLAYER_VOLUME_INIT 6

//-----------------------------------------RULES-----------------------------------------
bool FOOL_RULES::isCorrectChoose(FOOL_PLAYER *player)
{
    //FOOL_PLAYER *active =  pl1->my_move ? pl1 : pl2;

    //зашли в функцию не из playerChoosedCard
    if (!player->choosed_card)
        return false;

    switch(player->state){
        case FOOL_PLAYER::ADDING:

        case FOOL_PLAYER::ATTACK:{
            //атакующий бросил свою первую карту => карта может быть любая
            if (field->getVolume() == 0)
                return true;

            //на поле уже есть карты
            else{
                std::vector<CARD*> on_field = field->showSet();

                //если карта с таким достоинством есть на поле
                for (size_t i = 0; i < on_field.size(); i++)
                    if (on_field[i]->getRank() == player->choosed_card->getRank())
                        return true;

                return false;
            }
        }
            break;

        case FOOL_PLAYER::DEFENCE:{
            CARD *battered = field->showLastCard();

            if (battered->getSuit() == trump){
                if(player->choosed_card->getRank() > battered->getRank())
                    return true;
                else
                    return false;
            }
            else if (player->choosed_card->getSuit() == battered->getSuit() &&
                     player->choosed_card->getRank() > battered->getRank() ||
                     player->choosed_card->getSuit() == trump)
                return true;
            else
                return false;
        }
            break;

        default:
            return false;
    }
}

void FOOL_RULES::fillSetsOfPlayers()
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

   //is it game over?
   if (pl1->getVolume() == 0 && pl2->getVolume() == 0){
       //qDebug() << "game  over: dead heat";
       field->f_f_set_view->text = "game  over:\n dead heat";
       field->f_f_set_view->update();
   }

   if (pl1->getVolume() == 0){
       //qDebug() << "game  over: player 1 wins";
       field->f_f_set_view->text = "game  over:\n player 1 wins";
       field->f_f_set_view->update();
   }

   if (pl2->getVolume() == 0){
       //qDebug() << "game  over: player 2 wins";
       field->f_f_set_view->text ="game  over:\n player 2 wins";
       field->f_f_set_view->update();
   }
}

FOOL_RULES::END_LOCAL_STATE FOOL_RULES::isEndLocal(){
    FOOL_PLAYER *active =  pl1->my_move ? pl1 : pl2,
               *passive = !pl1->my_move ? pl1 : pl2;

    //if (active->state == FOOL_PLAYER::ATTACK &&
    //    active->getVolume() == 0 &&
    //    pr->getVolume() == 0)
    //gameOver();

    if (active->state == FOOL_PLAYER::ADDING &&
       (field->card_count_from_attacking - field->card_count_from_defencing) == passive->getVolume())
        return GIVE_AWAY;

    if (active->state == FOOL_PLAYER::TAKING &&
       (field->card_count_from_attacking - field->card_count_from_defencing) == active->getVolume())
        return GIVE_AWAY;

    if (active->state == FOOL_PLAYER::DEFENCE &&
              (field->getVolume() == active->getInitVolume() * 2 ||
               active->getVolume() == 0 || passive->getVolume() == 0))
           return BEATEN_OFF;

    return NOT_END;
}


//-----------------------------------------GAME-----------------------------------------
FOOL_GAME::FOOL_GAME(){
    dealer = new DEALER(_36_CARD_DECK);

    pl1 = new FOOL_PLAYER(PLAYER_VOLUME_INIT);
    pl2 = new FOOL_PLAYER(PLAYER_VOLUME_INIT);    
    pl1->initSetView(QPointF(240, 495), 80 * PLAYER_VOLUME_INIT + 40/*for buttons*/, 145/*116*1.25*/);
    pl2->initSetView(QPointF(240, 0), 80 * PLAYER_VOLUME_INIT + 40, 145);


    pr = new FOOL_PRICUP(_36_CARD_DECK - PLAYER_VOLUME_INIT - PLAYER_VOLUME_INIT);
    pr->initSetView(QPointF(0, 262), 116, 116);

    field = new FOOL_FIGHT_FIELD();
    field->initSetView(QPointF(300, 150), 360, 290);

    beaten = new FOOL_BEATEN();
    beaten->initSetView(QPointF(880, 262), 80, 116);

}

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

void FOOL_GAME::game()
{
    dealer->getOutCards(pl1);
    dealer->getOutCards(pl2);
    dealer->getOutCards(pr); 

    trump = pr->getTrumpSuit();
    //pl1->setTrump(trump);
    //pl2->setTrump(trump);

    pl1->initState(FOOL_PLAYER::ATTACK);
    pl2->initState(FOOL_PLAYER::DEFENCE);

    //на игровом поле 6 пар карт => бросаем их в биту
    //QObject::connect(field, &FOOL_FIGHT_FIELD::iFilled,
      //               this, &FOOL_GAME::throwToBeaten);
    //перешел ход
    QObject::connect(this, &FOOL_GAME::transferMove,
                     pl1, &FOOL_PLAYER::changeMoveValue);
    //перешел ход
    QObject::connect(this, &FOOL_GAME::transferMove,
                     pl2, &FOOL_PLAYER::changeMoveValue);

    //игрок выбрал карту
    QObject::connect(pl1, &FOOL_PLAYER::chooseIsMade,
                     this, &FOOL_GAME::playerChoosedCard);
    //игрок выбрал карту
    QObject::connect(pl2, &FOOL_PLAYER::chooseIsMade,
                     this, &FOOL_GAME::playerChoosedCard);

    //игрок сказал "бито"  => бросаем карты с поля в биту
    QObject::connect(pl1->pl_set_view->itIsBeaten, &BUTTON::buttonClicked,
                     this, &FOOL_GAME::throwToBeaten);
    //игрок сказал "бито"  => бросаем карты с поля в биту
    QObject::connect(pl2->pl_set_view->itIsBeaten, &BUTTON::buttonClicked,
                     this, &FOOL_GAME::throwToBeaten);

    //игрок сказал "беру" => даем возможность атакующему "прикончить" противника
    QObject::connect(pl1->pl_set_view->iTake, &BUTTON::buttonClicked,
                     this, &FOOL_GAME::finishHim);
    //игрок сказал "беру" => даем возможность атакующему "прикончить" противника
    QObject::connect(pl2->pl_set_view->iTake, &BUTTON::buttonClicked,
                     this, &FOOL_GAME::finishHim);

    //игрок сказал "забирай" => отдаем карты берущему
    QObject::connect(pl1->pl_set_view->takeAway, &BUTTON::buttonClicked,
                     this, &FOOL_GAME::giveToPlayer);
    //игрок сказал "забирай" => отдаем карты берущему
    QObject::connect(pl2->pl_set_view->takeAway, &BUTTON::buttonClicked,
                     this, &FOOL_GAME::giveToPlayer);
/*
    //players[0]->drawSet();
    //players[1]->drawSet();

    //dealer.getOutCards(table);


    //connect(player_1, &FOOL_PLAYER::setUpdated,
    //(FOOL_PLAYER_SET_VIEW*)player_1->setView, &FOOL_PLAYER_SET_VIEW::mapUpdate);

   // player_1->setView->runSetView();
    //player_2->setView->runSetView();

    //player_1->changeFightState(ATTACK);
    //player_1->changeFightState(DEFENSE);
    //trump = pr->getTrumpSuit();

    ---later:
        dealer->connect(player_1, f_f);
        if (player_2->getDecision() == PICK_UP)
            dealer->connect(f_f, player_2);
        else if (player_2->getDecision() == BEAT_OFF)


    f_f->addToSet(player_1->giveCard());

    std::vector<CARD*> c = f_f->giveCard();
    if (c.empty())
        cout << "empty std::vector" << endl;
    else
        cout << c[0]->getRank() << c[0]->getSuit() << endl;
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

    else
        active->pl_set_view->card_btns.at(active->choosed_card)->isChanged = false;

    active->choosed_card = NULL;

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

std::vector<MY_ITEM*> FOOL_GAME:: getItems(){
    std::vector<MY_ITEM*> items;

    items.push_back(pl1->pl_set_view);
    items.push_back(pl2->pl_set_view);
    items.push_back(pr->pr_set_view);
    items.push_back(field->f_f_set_view);
    items.push_back(beaten->b_set_view);

    return items;
}
