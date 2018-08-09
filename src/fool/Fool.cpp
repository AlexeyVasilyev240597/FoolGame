#include "Fool.h"
#include "../abstract/gameelement.h"
#include "player.h"
#include "table.h"


//later be in RULES
#define PLAYER_VOLUME_INIT 6

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


void FOOL_GAME::game()
{
    //qDebug() << players.size();
    dealer->getOutCards(pl1);
    dealer->getOutCards(pl2);
    dealer->getOutCards(pr); 

    trump = pr->getTrumpSuit();

    pl1->initState(FOOL_PLAYER::ATTACK);
    pl2->initState(FOOL_PLAYER::DEFENCE);

    QObject::connect(pl1, &FOOL_PLAYER::chooseIsMade,
                     this, &FOOL_GAME::someSetUpdated);

    QObject::connect(pl2, &FOOL_PLAYER::chooseIsMade,
                     this, &FOOL_GAME::someSetUpdated);

    QObject::connect(pl1->pl_set_view->itIsBeaten, &BUTTON::buttonClicked,
                     this, &FOOL_GAME::throwToBeaten);

    QObject::connect(pl2->pl_set_view->itIsBeaten, &BUTTON::buttonClicked,
                     this, &FOOL_GAME::throwToBeaten);
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
    /*
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

void FOOL_GAME::someSetUpdated(){
    if (pl1->changed_card != NULL){
        field->addToSet(pl1->giveCard());
        pl1->changed_card = NULL;
    }
    if (pl2->changed_card != NULL){
        field->addToSet(pl2->giveCard());
        pl2->changed_card = NULL;
    }

}

void FOOL_GAME::throwToBeaten(){
    beaten->addToSet(field->giveCard());

    //this init of first and last remove to FOOL_RULES::howFirstTakeFromPricup(first, last)
    FOOL_PLAYER *first = pl1->state == FOOL_PLAYER::ATTACK  ? pl1 : pl2,
                *last  = pl1->state == FOOL_PLAYER::DEFENCE ? pl1 : pl2;
    //a define of cards number remove to size_t FOOL_RULES::howMuchCardsToTakeFromPricup()
    first->addToSet(pr->giveCard(std::min(first->getInitVolume() - first->getVolume(), pr->getVolume())));
     last->addToSet(pr->giveCard(std::min(last->getInitVolume()  -  last->getVolume(), pr->getVolume())));

   //remove to FOOL_RULES::changeState(pl1)
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
