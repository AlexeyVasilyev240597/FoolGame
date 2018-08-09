#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <QObject>
#include <QPointF>
#include <QPixmap>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QApplication>
#include <map>
#include <QDebug>

#include "../abstract/CardDeck.h"
#include "../abstract/MyItem.h"

//-----------------------------CARD_BUTTON-----------------------------
class CARD_BTN : public QObject, public CARD_ITEM{
Q_OBJECT
public:
  CARD_BTN(QPointF pos, CARD* c): CARD_ITEM(pos, c){setAcceptHoverEvents(true);}

  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

  void mousePressEvent(QGraphicsSceneMouseEvent *)  override;
  //void mouseMoveEvent(QGraphicsSceneMouseEvent *)   override;
  void mouseReleaseEvent(QGraphicsSceneMouseEvent *)override;

  //void moveEvent(QPointF);

  void hoverEnterEvent(QGraphicsSceneHoverEvent*)   override;
  void hoverLeaveEvent(QGraphicsSceneHoverEvent*)   override;

signals:
  void cardButtonClicked(Qt::MouseButton);

protected:
  //bool mIsMoving{false};

  bool mHover{false};

public:
  bool isChanged{false};

  //QPointF mStartMovePos;
};

//-----------------------------PLAYER'S ITEM-----------------------------
class FOOL_PLAYER_SET_VIEW : public MY_ITEM
{
public:
    FOOL_PLAYER_SET_VIEW(QPointF pos, int w, int h):MY_ITEM(pos, w, h){
        itIsBeaten = new BUTTON(QPointF(80*6, 0), "beaten");
        itIsBeaten->setParentItem(this);
        iTake = new BUTTON(QPointF(80*6, 50), "take");
        iTake->setParentItem(this);
    }

    BUTTON *itIsBeaten, *iTake;
    //если есть возможность менять очередность добавления карт в набор,
    //то имеет смысл делать map и вызывать updateSet() не так часто
    //std::map<CARD*, CARD_BTN*> my_map;
    std::vector<CARD_BTN*> card_btns;

};

//-----------------------------PRICUP'S ITEM-----------------------------
class FOOL_PRICUP_SET_VIEW : public MY_ITEM
{
public:
    FOOL_PRICUP_SET_VIEW(QPointF pos, int w, int h):MY_ITEM(pos, w, h){        
        pileImg = new CARD_ITEM(QPointF(0, 0));
    }

    CARD_ITEM *pileImg, *trumpImg;

    //std::map<CARD*, CARD_BTN*> my_map;
    //std::vector<CARD_BTN*> card_btns;
//public slots:
    //void setUpdate(std::vector<CARD*>);

//private:
    //void drawSetView();

};

//-----------------------------FIELD'S ITEM-----------------------------
class FOOL_FIGHT_FIELD_SET_VIEW : public MY_ITEM
{
public:
    FOOL_FIGHT_FIELD_SET_VIEW(QPointF pos, int w, int h):MY_ITEM(pos, w, h){}

    //std::map<CARD*, CARD_BTN*> my_map;
    std::vector<CARD_ITEM*> cards_in_fight;
//public slots:
    //void setUpdate(std::vector<CARD*>);

//private:
    //void drawSetView();

};


//-----------------------------BEATEN'S ITEM-----------------------------
class FOOL_BEATEN_SET_VIEW: public MY_ITEM
{
public:
    FOOL_BEATEN_SET_VIEW(QPointF pos, int w, int h):MY_ITEM(pos, w, h){
        pileImg = new CARD_ITEM(QPointF(0, 0));
    }

    CARD_ITEM *pileImg;

};
#endif // BUTTON_HPP
