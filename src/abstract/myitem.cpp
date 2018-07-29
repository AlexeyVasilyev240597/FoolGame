#include "MyItem.h"

#include <QDebug>
#include <QPainter>

MY_ITEM::MY_ITEM(QPointF pos, int width, int heigth)
{
  mWidth = width;
  mHeigth = heigth;
  setPos(pos);
  setAcceptHoverEvents(false);
  setAcceptedMouseButtons(Qt::LeftButton);
}

//------------------------------------------------------------------------------
QRectF MY_ITEM::boundingRect() const
{
  return QRectF(0, 0, mWidth, mHeigth);
}
//------------------------------------------------------------------------------
void MY_ITEM::paint(QPainter *painter,
                   const QStyleOptionGraphicsItem */*option*/,
                   QWidget */*widget*/)
{
  //if(mHover)
    //painter->setPen(QColor(255, 255, 0));

  //painter->drawPixmap(0,0, mWidth, mHeigth, mPixMap);
  painter->drawRoundedRect(0, 0, mWidth, mHeigth, 5, 5);
}

void CARD_ITEM::paint(QPainter *painter,
                   const QStyleOptionGraphicsItem */*option*/,
                   QWidget */*widget*/)
{
  painter->drawPixmap(0,0, mWidth, mHeigth, mPixMap);
  painter->drawRoundedRect(0, 0, mWidth, mHeigth, 5, 5);
}
