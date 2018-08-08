#include "GameItems.h"
#include <QDebug>

/*
BUTTON::BUTTON()
{
  setAcceptHoverEvents(true);
  setAcceptedMouseButtons(Qt::LeftButton);
}
*/
/*
//------------------------------------------------------------------------------
QRectF BUTTON::boundingRect() const
{
  return QRectF(0, 0, mWidth, mHeigth);
}
*/
//------------------------------------------------------------------------------
void CARD_BTN::paint(QPainter *painter,
                   const QStyleOptionGraphicsItem */*option*/,
                   QWidget */*widget*/)
{
  if(mHover)
    painter->setPen(QColor(255, 255, 0));

  painter->drawPixmap(0,0, mWidth, mHeigth, mPixMap);
  painter->drawRoundedRect(0, 0, mWidth, mHeigth, 5, 5);
}
/*
//------------------------------------------------------------------------------
void BUTTON::setGeometry(int aWidth, int aHeight)
{
  mWidth  = aWidth;
  mHeigth = aHeight;
}
*/
//------------------------------------------------------------------------------
/*
void CARD_BTN::setImage(QString aPath)
{
  mBtnImg.load(aPath);
  mWidth  = mBtnImg.width();
  mHeigth = mBtnImg.height();
}
*/
//------------------------------------------------------------------------------
void CARD_BTN::hoverEnterEvent(QGraphicsSceneHoverEvent*)
{
  //qWarning() << "Enter";
  mHover = true;
  QGraphicsItem::update();
}
//------------------------------------------------------------------------------
void CARD_BTN::hoverLeaveEvent(QGraphicsSceneHoverEvent*)
{
  //qWarning() << "Leave";
  mHover = false;
  QGraphicsItem::update();
}

//------------------------------------------------------------------------------
void CARD_BTN::mousePressEvent(QGraphicsSceneMouseEvent *aEvent)
{
   //qWarning() << "press" << aEvent->BUTTON();
  //mStartMovePos = aEvent->pos();
  //mIsMoving = false;
}

/*
//------------------------------------------------------------------------------
void BUTTON::mouseMoveEvent(QGraphicsSceneMouseEvent *aEvent)
{
  int distance = ((aEvent->pos() - mStartMovePos)).manhattanLength();
  if(distance > QApplication::startDragDistance())
  {
    QPointF np = mapToScene(aEvent->pos() - mStartMovePos);

    if( (np.x() < 0) || (np.y() < 0) )
      return;
    if( (np.x() > 800) || (np.y() > 800) )
      return;

    mIsMoving = true;
    this->setPos(np);
  }
}
*/
/*
//------------------------------------------------------------------------------
void BUTTON::moveEvent(QPointF np)
{
    this->setPos(np);
}
*/
//------------------------------------------------------------------------------
void CARD_BTN::mouseReleaseEvent(QGraphicsSceneMouseEvent *apEvent)
{
  //if(!mIsMoving)
    qWarning() << "release" << apEvent->button();
    qDebug() << "it's click";
    isChanged = !isChanged;
    emit btnMouseReleaseEvent(apEvent->button());
}
/*
void FOOL_PLAYER_SET_VIEW::setUpdate(std::vector<CARD*> set){
    std::map<CARD*, CARD_BTN*>::iterator it_m;
    for(size_t i = 0; i < set.size(); i++){
        it_m = my_map.find(set[i]);
        if (it == my_map.end()){
            CARD_BTN c_b = new CARD_BTN(set[i]);
            my_map.insert(std::pair<CARD*, CARD_BTN*>(set[i], c_b));
        }
    }

    if (!card_btns.empty())
        for (size_t i = 0; i < card_btns.size(); i++)
            delete card_btns[i];

    for (size_t i = 0; i < set.size(); i++){
        QPoint p(880/2-set.size()/2*80*i,440);
        CARD_BTN* c_b = new CARD_BTN(set[i], p);
        card_btns.push_back(c_b);
    }

    for (size_t i = 0; i < card_btns.size(); i++)
        card_btns[i]->setParentItem(this);
}
*/
