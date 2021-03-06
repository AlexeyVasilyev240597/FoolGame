#include "rules.h"

//-----------------------------------------RULES-----------------------------------------
bool FOOL_RULES::isCorrectChoose(FOOL_PLAYER *player)
{
    //FOOL_PLAYER *active =  pl1->my_move ? pl1 : pl2;

    //����� � ������� �� �� playerChoosedCard
    if (!player->choosed_card)
        return false;

    switch(player->state){
        case FOOL_PLAYER::ADDING:

        case FOOL_PLAYER::ATTACK:{
            //��������� ������ ���� ������ ����� => ����� ����� ���� �����
            if (field->getVolume() == 0)
                return true;

            //�� ���� ��� ���� �����
            else{
                std::vector<CARD*> on_field = field->showSet();

                //���� ����� � ����� ������������ ���� �� ����
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
       (field->counter[FOOL_FIGHT_FIELD::FROM_ATTAKING] -
        field->counter[FOOL_FIGHT_FIELD::FROM_DEFENCING]) == passive->getVolume())
        return GIVE_AWAY;

    if (active->state == FOOL_PLAYER::TAKING &&
        (field->counter[FOOL_FIGHT_FIELD::FROM_ATTAKING] -
         field->counter[FOOL_FIGHT_FIELD::FROM_DEFENCING]) == active->getVolume())
        return GIVE_AWAY;

    if (active->state == FOOL_PLAYER::DEFENCE &&
              (field->getVolume() == /*active->getInitVolume()*/PL_V * 2 ||
               active->getVolume() == 0 || passive->getVolume() == 0))
           return BEATEN_OFF;

    return NOT_END;
}

void FOOL_RULES::checkGameOver(){
    FOOL_PLAYER *active =  pl1->my_move ? pl1 : pl2,
               *passive = !pl1->my_move ? pl1 : pl2;
    QString message = "game over:\n";

    if (active->getVolume() == 0 && passive->getVolume() == 0)
        message += "dead heat";

    else if (active->getVolume() == 0){
        message += active->name;
        message += " wins";
    }

    else if (passive->getVolume() == 0){
        message += active->name;
        message += " wins";
    }

    else
        return;

    emit gameOver(message);
}
