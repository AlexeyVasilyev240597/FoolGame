#include "Table.h"

//-----------------------------PRICUP-----------------------------
void FOOL_PRICUP::addToSet(std::vector<CARD*> cards){
    for (size_t i = 0; i < cards.size(); i++){
        my_set.push_back(cards[i]);
        my_set.back()->changeFaceState(DOWN);
    }

    my_set.back()->changeFaceState(UP);

    emit getTrumpSuit(my_set.back()->getSuit());
}

void FOOL_PRICUP::setBadge(CARD *tr_badge){
    emit addedToSet(my_set.size(), my_set.back(), tr_badge);
}


std::vector<CARD*> FOOL_PRICUP::giveCard(size_t number){
    std::vector<CARD*> cards;

	//if (number > my_set.size())
        //number = my_set.size();


	for (size_t i = 0; i < number; i++){
        cards.push_back(my_set.front());
		my_set.erase(my_set.begin());
	}

    emit removedFromSet(my_set.size());

    return cards;
}

//-----------------------------FIELD-----------------------------
void FOOL_FIGHT_FIELD::addToSet(std::vector<CARD*> cards, FOOL_PLAYER::PLAYER_STATE s){
    my_set.push_back(cards[0]);
    my_set.back()->changeFaceState(UP);

    size_t index = 0;
    if (s == FOOL_PLAYER::ATTACK || s == FOOL_PLAYER::ADDING){
        counter[FROM_ATTAKING]++;
        index = counter[FROM_ATTAKING];
    }

    if (s == FOOL_PLAYER::DEFENCE || s == FOOL_PLAYER::TAKING){
        counter[FROM_DEFENCING]++;
        index = counter[FROM_DEFENCING];
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

//-----------------------------BEATEN-----------------------------
void FOOL_BEATEN::addToSet(std::vector<CARD*> cards){
    for (size_t i = 0; i < cards.size(); i++){
        if (my_set.empty())
            emit addedToSet();
        my_set.push_back(cards[i]);
        my_set.back()->changeFaceState(DOWN);
    }
}

std::vector<CARD*> FOOL_BEATEN::giveCard(){
    //beaten НЕ ОТДАЕТ карты
    std::vector<CARD*> cards;
    return cards;
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

//в этом месте можно связать сигналы элементов и слоты итомов
/*
void DEALER::exchange(ELEMENT* from, ELEMENT* to){
    //if (rules->isPossible(from, to))
        to->addToSet(from->giveCard());
}
*/

CARD* DEALER::getBadge(SUIT s){
    CARD *badge = deck->suit_badges[s];
    badge->changeFaceState(UP);

    return badge;
}



























