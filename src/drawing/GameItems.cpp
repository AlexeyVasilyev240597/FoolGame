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
    isChanged = true;
    emit cardButtonClicked(apEvent->button());
}

void FOOL_FIGHT_FIELD_SET_VIEW::paint(QPainter *painter,
                                      const QStyleOptionGraphicsItem* /*option*/,
                                      QWidget* /*widget*/){
  if (!text.isEmpty())
      painter->drawText(QRectF(0, 0, mWidth, mHeigth), Qt::AlignCenter, text);

  painter->drawRoundedRect(0, 0, mWidth, mHeigth, 5, 5);
}


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
