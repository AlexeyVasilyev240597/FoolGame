#include "Table.h"

//-----------------------------PRICUP-----------------------------
std::vector<CARD*> FOOL_PRICUP::giveCard(size_t number){
    std::vector<CARD*> cards;

	//if (number > my_set.size())
	//return cards;
	//else cards.reserve(number);

    //bool have_last_close_card = my_set.size() >= 2;

	for (size_t i = 0; i < number; i++){
		cards.push_back(my_set.at(0));
		my_set.erase(my_set.begin());
	}

    if (my_set.size() <= 1)
        pr_set_view->pileImg->setVisible(false);
    //if (have_last_close_card && my_set.size() <= 1)
        //delete pr_set_view->pileImg;

    if (my_set.empty())
        pr_set_view->trumpImg->setVisible(false);
        //delete pr_set_view->trumpImg;

    //qDebug() << "in Pricup " << this->getVolume() <<"cards";

	return cards;
}

void FOOL_PRICUP::dealerGetOut(){
    if (!my_set.empty()){
        my_set.back()->changeFaceState(UP);

        pr_set_view->trumpImg = new CARD_ITEM(QPointF(18, 0), my_set.back());
        pr_set_view->trumpImg->setParentItem(pr_set_view);
        pr_set_view->trumpImg->setTransformOriginPoint(pr_set_view->trumpImg->mWidth/2,
                                                       pr_set_view->trumpImg->mHeigth/2);
        pr_set_view->trumpImg->setRotation(90);

        pr_set_view->pileImg->setParentItem(pr_set_view);

        emit getTrumpSuit(my_set.back()->getSuit());
    }
}

/*
void FOOL_PRICUP::initSetView(QPointF pos, int w, int h){
    pr_set_view = new FOOL_PRICUP_SET_VIEW(pos, w, h);
}
*/

//-----------------------------BEATEN-----------------------------
void FOOL_BEATEN::addToSet(std::vector<CARD*> cards){
    for (size_t i = 0; i < cards.size(); i++){
        my_set.push_back(cards[i]);
        my_set.back()->changeFaceState(DOWN);
    }

    if (b_set_view->childItems().empty())
        b_set_view->pileImg->setParentItem(b_set_view);

    //qDebug() << "in Beaten " << this->getVolume() <<"cards";
}

std::vector<CARD*> FOOL_BEATEN::giveCard(){
    //beaten НЕ ОТДАЕТ карты
    std::vector<CARD*> cards;
	return cards;
}
/*
void FOOL_BEATEN::initSetView(QPointF pos, int w, int h){
    b_set_view = new FOOL_BEATEN_SET_VIEW(pos, w, h);
}
*/
//-----------------------------FIELD-----------------------------
void FOOL_FIGHT_FIELD::addToSet(std::vector<CARD*> cards, FOOL_PLAYER::PLAYER_STATE s){
    my_set.push_back(cards[0]);
    my_set.back()->changeFaceState(UP);
    //size_t index = my_set.size()-1;
    qreal x(0), y(0);

    if (s == FOOL_PLAYER::ATTACK || s == FOOL_PLAYER::ADDING){
        card_count_from_attacking++;
        x = 80 * 1.5 * ((card_count_from_attacking - 1) % 3);
        y = 116 * 1.25 * (card_count_from_attacking > 3);
    }

    if (s == FOOL_PLAYER::DEFENCE || s == FOOL_PLAYER::TAKING){
        card_count_from_defencing++;
        x = 80 / 2 + 80 * 1.5 * ((card_count_from_defencing-1) % 3);
        y = 116 * 0.25 + 116 * 1.25 * (card_count_from_defencing > 3);
    }

    //for (size_t i = 0; i < cards.size(); i++){
//       double x = 80 / 2 * (index % 6 % 2) + 80 * 1.5 * (index % 6 / 2),
//              y = 116 * 1.25 * (index > 5) + 116 * 0.25 * (index % 2);

       CARD_ITEM* c = new CARD_ITEM(QPoint(x, y), my_set.back());
       f_f_set_view->cards_in_fight.push_back(c);
       f_f_set_view->cards_in_fight.back()->setParentItem(f_f_set_view);

       //6 * 2 )))
       //if (my_set.size() == 6 * 2)
        //emit iFilled();
    //}

   emit setUpdated();
}

std::vector<CARD*> FOOL_FIGHT_FIELD::giveCard(){
    std::vector<CARD*> cards(my_set.size());

    my_set.swap(cards);
    my_set.clear();

    for (size_t i = 0; i < f_f_set_view->cards_in_fight.size(); i++)
        delete f_f_set_view->cards_in_fight[i];
    f_f_set_view->cards_in_fight.clear();
    card_count_from_attacking = card_count_from_defencing = 0;

    emit setUpdated();

    return cards;
}
/*
void FOOL_FIGHT_FIELD::initSetView(QPointF pos, int w, int h){
    f_f_set_view = new FOOL_FIGHT_FIELD_SET_VIEW(pos, w, h);
}
*/
//-----------------------------DEALER-----------------------------
void DEALER::getOutCards(ELEMENT* elem){

    if (elem->getInitVolume() == 0)
        return;
    std::vector<CARD*> tmp_set;
    //или ты доверяешь RULES и расчитываешь, что запрашиваемые размеры не больше объема колоды,
    //или ты проверяешь это здесь,
    //или ты создаешь класс, который это проверяет
    //if (deck->volume - deck->in_game_count < num){
    //std::cout << "cannot get so many cards(" << num << ')' << std::endl;
    //}
    int index;
    for (size_t j = 0; j < deck->cards.size(); j++){
        if (!deck->cards[j].in_game){
            index = j;
            break;
        }
    }

    for (size_t j = index; j < index + elem->getInitVolume(); j++){
        tmp_set.push_back(&deck->cards[j]);
        deck->cards[j].changeInGameState(true);
    }

    elem->addToSet(tmp_set);
}
/*
void DEALER::exchange(ELEMENT* from, ELEMENT* to){
    //if (rules->isPossible(from, to))
        to->addToSet(from->giveCard());
}
*/
