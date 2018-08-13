#include "MyItem.h"

#include <QDebug>
#include <QPainter>
//----------------------------------MY_ITEM----------------------------------
MY_ITEM::MY_ITEM(QPointF pos, int width, int heigth)
{
  mWidth = width;
  mHeigth = heigth;
  setPos(pos);
  setAcceptHoverEvents(false);
  setAcceptedMouseButtons(Qt::LeftButton);
}

QRectF MY_ITEM::boundingRect() const
{
  return QRectF(0, 0, mWidth, mHeigth);
}

void MY_ITEM::paint(QPainter *painter,
                   const QStyleOptionGraphicsItem */*option*/,
                   QWidget */*widget*/)
{
  painter->drawRoundedRect(0, 0, mWidth, mHeigth, 5, 5);
}

//----------------------------------CARD_ITEM----------------------------------
void CARD_ITEM::paint(QPainter *painter,
                   const QStyleOptionGraphicsItem */*option*/,
                   QWidget */*widget*/)
{
  painter->drawPixmap(0,0, mWidth, mHeigth, mPixMap);
  painter->drawRoundedRect(0, 0, mWidth, mHeigth, 5, 5);
}

//----------------------------------BUTTON----------------------------------
void BUTTON::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    painter->drawText(QRectF(0, 0, mWidth, mHeigth), Qt::AlignCenter, my_text);
    painter->drawRoundedRect(0, 0, mWidth, mHeigth, 5, 5);
}

void BUTTON::mousePressEvent(QGraphicsSceneMouseEvent *aEvent){}

void BUTTON::mouseReleaseEvent(QGraphicsSceneMouseEvent *apEvent)
{
    //qDebug() << "buttonClicked";
    emit buttonClicked(apEvent->button());
}
