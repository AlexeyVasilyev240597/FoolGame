#include "Fool.h"
#include "../abstract/gameelement.h"


//later be in RULES
#define PLAYER_VOLUME_INIT 6

void FOOL_GAME::setElems(){
    //for (size_t i = 0; i < 2; i++){
        FOOL_PLAYER* pl1 = new FOOL_PLAYER(PLAYER_VOLUME_INIT);
        FOOL_PLAYER* pl2 = new FOOL_PLAYER(PLAYER_VOLUME_INIT);
        players.push_back(pl1);
        players.push_back(pl2);
        QPoint p1(240, 440);
        players[0]->initSetView(p1, 80 * PLAYER_VOLUME_INIT, 116);
        QPoint p2(240, 0);
        players[1]->initSetView(p2, 80 * PLAYER_VOLUME_INIT, 116);

        pr = new FOOL_PRICUP(_36_CARD_DECK - PLAYER_VOLUME_INIT - PLAYER_VOLUME_INIT);
        table.push_back(pr);
        QPoint p(0, 252);
        table[0]->initSetView(p, 116, 116);


        //emit initPlayer(players[i]->set_view);
    //}

    //FOOL_PRICUP *pr = new FOOL_PRICUP(_36_CARD_DECK - PLAYER_VOLUME_INIT - PLAYER_VOLUME_INIT);
    //FOOL_BEATEN_OFF *b_off = new FOOL_BEATEN_OFF();
    //FOOL_FIGHT_FIELD *f_f = new FOOL_FIGHT_FIELD();

    //table = {pr, b_off, f_f};

}

void FOOL_GAME::game()
{
    qDebug() << players.size();
    dealer->getOutCards(players);

    dealer->getOutCards(table);
    trump = pr->getTrumpSuit();
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
