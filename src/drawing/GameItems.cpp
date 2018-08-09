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
    if (canIBeClicked){
       // qDebug() << "enter";
      mHover = true;
      QGraphicsItem::update();
    }
}

void CARD_BTN::hoverLeaveEvent(QGraphicsSceneHoverEvent*)
{
    if (canIBeClicked){
      //  qDebug() << "leave";
      mHover = false;
      QGraphicsItem::update();
    }
}


void CARD_BTN::mouseReleaseEvent(QGraphicsSceneMouseEvent *apEvent)
{
  //if(!mIsMoving)
    //qWarning() << "release" << apEvent->button();
    //qDebug() << "it's click";
    if (canIBeClicked){
        isChanged = !isChanged;
        emit cardButtonClicked(apEvent->button());
    }
}
