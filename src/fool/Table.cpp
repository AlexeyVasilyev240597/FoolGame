#include "Table.h"

std::vector<CARD*> FOOL_PRICUP::giveCard(size_t number){
    std::vector<CARD*> cards;

	//if (number > my_set.size())
	//return cards;
	//else cards.reserve(number);

	for (size_t i = 0; i < number; i++){
		cards.push_back(my_set.at(0));
		my_set.erase(my_set.begin());
	}

	return cards;
}

SUIT FOOL_PRICUP::getTrumpSuit(){
    if (!my_set.empty()){
        my_set.back()->changeFaceState(UP);
        addItems();

        return my_set.back()->getSuit();
    }
    return NO_SUIT;
}


void FOOL_PRICUP::initSetView(QPoint pos, int w, int h){
    pr_set_view = new FOOL_PRICUP_SET_VIEW(pos, w, h);
    set_view = pr_set_view;
}
void FOOL_PRICUP::addItems(){
    if(!my_set.empty()){
        QPoint p(18, 0);
        pr_set_view->trumpImg = new CARD_ITEM(p, my_set.back());
        pr_set_view->trumpImg->setParentItem(pr_set_view);
        pr_set_view->trumpImg->setTransformOriginPoint(pr_set_view->trumpImg->mWidth/2, pr_set_view->trumpImg->mHeigth/2);
        pr_set_view->trumpImg->setRotation(90);
        pr_set_view->pileImg->setParentItem(pr_set_view);
    }
}

std::vector<CARD*> FOOL_BEATEN_OFF::giveCard(){
	//beaten_off НЕ ОТДАЕТ карты
    std::vector<CARD*> cards;
	return cards;
}

std::vector<CARD*> FOOL_FIGHT_FIELD::giveCard(){
    std::vector<CARD*> cards(my_set.size());

    my_set.swap(cards);
    my_set.clear();

    return cards;
}

void DEALER::getOutCards(std::vector<ELEMENT*> &elems){
    qDebug() << elems.size();
	for (size_t i = 0; i < elems.size(); i++){
		if (elems[i]->getInitVolume() == 0)
			continue;
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

		for (size_t j = index; j < index + elems[i]->getInitVolume(); j++){
			tmp_set.push_back(&deck->cards[j]);
			deck->cards[j].changeInGameState(true);
		}

		elems[i]->addToSet(tmp_set);
	}
}

void DEALER::exchange(ELEMENT* from, ELEMENT* to){
    //if (rules->isPossible(from, to))
        to->addToSet(from->giveCard());
}

/*
class RULES{
public:
//enum CATEGORY{ TABLE, PLAYERS };
std::map<string, size_t> *my_sets_volume;
size_t max_num_of_players, how_many_cards_to_player;
//switch over my_setS
//virtual size_t howManyCards(CATEGORY cat, int key) = 0;// {
//std::cout << "i'm in base class(((" << std::endl;
//return 0;
//}
RULES(std::map<string, size_t> *s_v, size_t hmctp){
my_sets_volume = s_v;
how_many_cards_to_player = hmctp;
}
};

//template <typename NAMES_OF_FIELDS, size_t num_of_fields, size_t num_of_players>
class GAME{
public:
size_t num_of_players;
GAME(size_t nop){
num_of_players = nop;
}

RULES *rules;
std::map<string, my_set*> table;
std::vector<PLAYER> players;

virtual void my_setRules() = 0;

void initTable();//std::map<NAMES_OF_FIELDS, my_set*> &table);
void initPlayers();//std::vector<PLAYER> &players);

//virtual void toPlay() = 0;
};
*/
