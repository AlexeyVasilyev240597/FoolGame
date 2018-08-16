#include "GameItems.h"
#include <QDebug>

//-----------------------------CARD_BUTTON-----------------------------
void CARD_BTN::paint(QPainter *painter,
                   const QStyleOptionGraphicsItem */*option*/,
                   QWidget */*widget*/)
{
  if(mHover)
    painter->setPen(QColor(255, 255, 0));

  painter->drawPixmap(0,0, mWidth, mHeigth, mPixMap);
  painter->drawRoundedRect(0, 0, mWidth, mHeigth, 5, 5);
}

void CARD_BTN::mousePressEvent(QGraphicsSceneMouseEvent *){}

void CARD_BTN::hoverEnterEvent(QGraphicsSceneHoverEvent*)
{
  mHover = true;
  QGraphicsItem::update();
}

void CARD_BTN::hoverLeaveEvent(QGraphicsSceneHoverEvent*)
{
  mHover = false;
  QGraphicsItem::update();
}


void CARD_BTN::mouseReleaseEvent(QGraphicsSceneMouseEvent */*apEvent*/)
{
    //isChanged = true;
    emit cardButtonClicked(my_card);
}

//-----------------------------PLAYER-----------------------------
QPointF FOOL_PLAYER_SET_VIEW::getMyPos(size_t index, size_t n){
    qreal x, y;
    if (n < 19){
        x = n <= 6 ?
                    80 * (3 - (qreal)n / 2 + index) :    //выравнивание по центру
             (qreal)80 * 5 * index / (n - 1);            //уплотнение набора
    }

    else{
        if (index < 19)
            x = (qreal)80 * 5 * index / (18 - 1);

        else
            x = n % 19 <= 6 ?
                        80 * (3 - (qreal)(n % 19) / 2 + index % 19) :
                 (qreal)80 * 5 * (index % 19) / (n % 19 - 1);
     }

    y =  116 / 4 * (index >= _36_CARD_DECK / 2);                       //второй ряд карт

    return QPoint(x, y);
}


void FOOL_PLAYER_SET_VIEW::addToMap(std::vector<CARD*> &set)
{
    for (size_t i = 0; i < set.size(); i++){
        //if my_set[i] is not found
        if (card_btns.find(set[i]) ==
                card_btns.end()){

            CARD_BTN* c_b = new CARD_BTN(getMyPos(i, set.size()), set[i]);
            card_btns.insert(card_btns.end(), std::pair<CARD*, CARD_BTN*>(set[i], c_b));

            card_btns.at(set[i])->setParentItem(this);
            QObject::connect(card_btns.at(set[i]), &CARD_BTN::cardButtonClicked,
                             this, FOOL_PLAYER_SET_VIEW::clickedCard);
        }
        else
            card_btns.at(set[i])->setPos(getMyPos(i, set.size()));

        card_btns.at(set[i])->setZValue(i + 1);
        //qDebug() << my_set[i]->getRank() << my_set[i]->getSuit();
    }
}

void FOOL_PLAYER_SET_VIEW::removeFromMap(std::vector<CARD*>& set, std::vector<CARD*>& cards_to_remove)
{
    for (size_t i = 0; i < cards_to_remove.size(); i++){
        delete card_btns.at(cards_to_remove[i]);
        card_btns.erase(cards_to_remove[i]);
    }

    for (size_t i = 0; i < set.size(); i++){
       card_btns.at(set[i])->setPos(getMyPos(i, set.size()));
       card_btns.at(set[i])->setZValue(i + 1);
    }
}

void FOOL_PLAYER_SET_VIEW::clickedCard(CARD* card)
{
    emit choosedCard(card);
}

void FOOL_PLAYER_SET_VIEW::customizeButtons(bool cards, bool beaten, bool take, bool take_away){
    for (std::map<CARD*, CARD_BTN*>::iterator it = card_btns.begin();
         it != card_btns.end();
         it++)
        it->second->setEnabled(cards);

    itIsBeaten->setVisible(beaten);
    iTake->setVisible(take);
    takeAway->setVisible(take_away);
}
/*
void FOOL_PLAYER_SET_VIEW::changeCardState(CARD *card){
    //card_btns.at(card)->isChanged = false;
    qDebug() << "i in fool player set view change card state";
}
*/

//-----------------------------PRICUP-----------------------------
void FOOL_PRICUP_SET_VIEW::gaveOut(CARD* last_card){
    trumpImg = new CARD_ITEM(QPointF(18, 0), last_card);
    trumpImg->setParentItem(this);
    trumpImg->setTransformOriginPoint(trumpImg->mWidth/2, trumpImg->mHeigth/2);
    trumpImg->setRotation(90);

    pileImg = new CARD_ITEM(QPointF(0, 0));
    pileImg->setParentItem(this);
}

void FOOL_PRICUP_SET_VIEW::removeFromPile(size_t size){
    if (size <= 1)
        pileImg->setVisible(false);

    if (size == 0)
        trumpImg->setVisible(false);
}

//-----------------------------BEATEN-----------------------------
void FOOL_BEATEN_SET_VIEW::firstAdded(){
    //if (childItems().empty())
    pileImg = new CARD_ITEM(QPointF(0, 0));
    pileImg->setParentItem(this);
}

//-----------------------------FIELD-----------------------------
void FOOL_FIGHT_FIELD_SET_VIEW::paint(QPainter *painter,
                                      const QStyleOptionGraphicsItem* /*option*/,
                                      QWidget* /*widget*/){
  if (!text.isEmpty()){
      QFont font = painter->font();
      font.setPointSize(font.pointSize() * 3);
      painter->setFont(font);
      painter->drawText(QRectF(0, 0, mWidth, mHeigth), Qt::AlignCenter, text);
  }

  painter->drawRoundedRect(0, 0, mWidth, mHeigth, 5, 5);
}


QPointF FOOL_FIGHT_FIELD_SET_VIEW::getMyPos(bool inAttack, size_t index){
    qreal x, y;

    //if (s == FOOL_PLAYER::ATTACK || s == FOOL_PLAYER::ADDING){
    if (inAttack){
        //counter[FROM_ATTAKING]++;
        //size_t index = counter[FROM_ATTAKING];
        x = 80 * 1.5 * ((index - 1) % 3);
        y = 116 * 1.25 * (index > 3);
    }

    //if (s == FOOL_PLAYER::DEFENCE || s == FOOL_PLAYER::TAKING){
    else{
        //counter[FROM_DEFENCING]++;
        //size_t index = counter[FROM_DEFENCING];
        //card_count_from_defencing++;
        x = 80 / 2 + 80 * 1.5 * ((index - 1) % 3);
        y = 116 * 0.25 + 116 * 1.25 * (index > 3);
    }

    return QPointF(x, y);
}

void FOOL_FIGHT_FIELD_SET_VIEW::addCardItem(CARD* card, bool inAttack, size_t index){

    CARD_ITEM* c_i = new CARD_ITEM(getMyPos(inAttack, index), card);
    cards_in_fight.push_back(c_i);
    cards_in_fight.back()->setParentItem(this);
}


void FOOL_FIGHT_FIELD_SET_VIEW::removeAllItems(){
    for (size_t i = 0; i < cards_in_fight.size(); i++)
        delete cards_in_fight[i];

    cards_in_fight.clear();
}

void FOOL_FIGHT_FIELD_SET_VIEW::drawMessage(QString message){
    text = message;
    update();
}
