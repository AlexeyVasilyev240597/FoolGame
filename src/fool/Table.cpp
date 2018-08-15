#include "Table.h"

//-----------------------------PRICUP-----------------------------
std::vector<CARD*> FOOL_PRICUP::giveCard(size_t number){
    std::vector<CARD*> cards;

	//if (number > my_set.size())
        //number = my_set.size();


	for (size_t i = 0; i < number; i++){
        cards.push_back(my_set.front());
		my_set.erase(my_set.begin());
	}

    emit removedFromSet(my_set.size());
    //qDebug() << "in Pricup " << this->getVolume() <<"cards";

	return cards;
}

void FOOL_PRICUP::dealerGaveOut(){
    if (!my_set.empty())
    {
        my_set.back()->changeFaceState(UP);        
        emit addedToSet(my_set.back());
        emit getTrumpSuit(my_set.back()->getSuit());
    }
}


void FOOL_PRICUP::initSetView(FOOL_PRICUP_SET_VIEW* pr_set_view){
    //pr_set_view = new FOOL_PRICUP_SET_VIEW(pos, w, h);

    QObject::connect(this, &FOOL_PRICUP::addedToSet,
                     pr_set_view, &FOOL_PRICUP_SET_VIEW::gaveOut);


    QObject::connect(this, &FOOL_PRICUP::removedFromSet,
                     pr_set_view, &FOOL_PRICUP_SET_VIEW::removeFromPile);

}


//-----------------------------BEATEN-----------------------------
void FOOL_BEATEN::addToSet(std::vector<CARD*> cards){
    for (size_t i = 0; i < cards.size(); i++){
        if (my_set.empty())
            emit addedToSet();
        my_set.push_back(cards[i]);
        my_set.back()->changeFaceState(DOWN);        
    }

    //qDebug() << "in Beaten " << this->getVolume() <<"cards";
}

std::vector<CARD*> FOOL_BEATEN::giveCard(){
    //beaten НЕ ОТДАЕТ карты
    std::vector<CARD*> cards;
	return cards;
}

void FOOL_BEATEN::initSetView(FOOL_BEATEN_SET_VIEW *b_set_view){
    QObject::connect(this, &FOOL_BEATEN::addedToSet,
                     b_set_view, &FOOL_BEATEN_SET_VIEW::firstAdded);
}

//-----------------------------FIELD-----------------------------
void FOOL_FIGHT_FIELD::addToSet(std::vector<CARD*> cards, FOOL_PLAYER::PLAYER_STATE s){
    my_set.push_back(cards[0]);
    my_set.back()->changeFaceState(UP);

    size_t index = 0;
    if (s == FOOL_PLAYER::ATTACK || s == FOOL_PLAYER::ADDING){
        counter[FROM_ATTAKING]++;
        index = counter[FROM_ATTAKING];
        //x = 80 * 1.5 * ((index - 1) % 3);
        //y = 116 * 1.25 * (index > 3);
    }

    if (s == FOOL_PLAYER::DEFENCE || s == FOOL_PLAYER::TAKING){
        counter[FROM_DEFENCING]++;
        index = counter[FROM_DEFENCING];
        //x = 80 / 2 + 80 * 1.5 * ((index - 1) % 3);
        //y = 116 * 0.25 + 116 * 1.25 * (index > 3);
    }

    emit addedToSet(my_set.back(),
                    s == FOOL_PLAYER::ATTACK || s == FOOL_PLAYER::ADDING,
                    index);
}

std::vector<CARD*> FOOL_FIGHT_FIELD::giveCard(){
    std::vector<CARD*> cards(my_set.size());

    my_set.swap(cards);
    my_set.clear();

    counter[FROM_ATTAKING] = 0;
    counter[FROM_DEFENCING] = 0;

    emit removedFromSet();

    return cards;
}

void FOOL_FIGHT_FIELD::initSetView(FOOL_FIGHT_FIELD_SET_VIEW *f_f_set_view){
    QObject::connect(this, &FOOL_FIGHT_FIELD::addedToSet,
                     f_f_set_view, &FOOL_FIGHT_FIELD_SET_VIEW::addCardItem);

    QObject::connect(this, &FOOL_FIGHT_FIELD::removedFromSet,
                     f_f_set_view, &FOOL_FIGHT_FIELD_SET_VIEW::removeAllItems);
}

//-----------------------------DEALER-----------------------------
void DEALER::giveOutCards(ELEMENT* elem){

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
