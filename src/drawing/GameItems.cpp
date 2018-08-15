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


void CARD_BTN::mouseReleaseEvent(QGraphicsSceneMouseEvent *apEvent)
{
    //isChanged = true;
    emit cardButtonClicked(my_card);
}

//-----------------------------FIGHT-FIELD-----------------------------

void FOOL_FIGHT_FIELD_SET_VIEW::paint(QPainter *painter,
                                      const QStyleOptionGraphicsItem* /*option*/,
                                      QWidget* /*widget*/){
  if (!text.isEmpty()){
      QFont font = painter->font();
      font.setPointSize(font.pointSize() * 5);
      painter->setFont(font);
      painter->drawText(QRectF(0, 0, mWidth, mHeigth), Qt::AlignCenter, text);
  }

  painter->drawRoundedRect(0, 0, mWidth, mHeigth, 5, 5);
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
            card_btns.insert(std::pair<CARD*, CARD_BTN*>(set[i], c_b));

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

void FOOL_PLAYER_SET_VIEW::removeFromMap(std::vector<CARD*> &cards)
{
    for (size_t i = 0; i < cards.size(); i++){
        delete card_btns.at(cards[i]);
        card_btns.erase(cards[i]);
    }

    size_t index = 0;
    for (std::map<CARD*, CARD_BTN*>::iterator it = card_btns.begin();
         it != card_btns.end();
         it++, index++){

        it->second->setPos(getMyPos(index, card_btns.size()));
        it->second->setZValue(index + 1);
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
