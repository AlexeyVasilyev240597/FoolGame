#include "rules.h"

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
                if(player->choosed_card->getSuit() == trump &&
                   player->choosed_card->getRank() > battered->getRank())
                    return true;
                else
                    return false;
            }

            else if ((player->choosed_card->getSuit() == battered->getSuit() &&
                      player->choosed_card->getRank() > battered->getRank()) ||
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

void FOOL_RULES::checkGameOver(){
    FOOL_PLAYER *active =  pl1->my_move ? pl1 : pl2,
               *passive = !pl1->my_move ? pl1 : pl2;
    QString message;

    if (active->getVolume() == 0 && passive->getVolume() == 0)
        message = "dead heat";

    else if (active->getVolume() == 0){
        message = active->name;
        message += " wins";
    }

    else if (passive->getVolume() == 0){
        message = active->name;
        message += " wins";
    }


    else
        return;

    field->f_f_set_view->text = "game  over:\n";
    field->f_f_set_view->text += message;
    field->f_f_set_view->update();
}
