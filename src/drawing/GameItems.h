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
  void cardButtonClicked(CARD*);

protected:
  //bool mIsMoving{false};

  bool mHover{false};

public:
  //QPointF mStartMovePos;
};

//-----------------------------PLAYER'S ITEM-----------------------------
class FOOL_PLAYER_SET_VIEW : public QObject, public MY_ITEM
{
Q_OBJECT
public:
    FOOL_PLAYER_SET_VIEW(QPointF pos, int w, int h):MY_ITEM(pos, w, h){
        itIsBeaten = new BUTTON(QPointF(80*6, 0), "beaten");
        itIsBeaten->setParentItem(this);

        iTake = new BUTTON(QPointF(80*6, 39), "take");
        iTake->setParentItem(this);

        takeAway = new BUTTON(QPointF(80*6, 78), "take\n away");
        takeAway->setParentItem(this);
    }

    BUTTON *itIsBeaten, *iTake, *takeAway;
    std::map<CARD*, CARD_BTN*> card_btns;

    QPointF getMyPos(size_t index, size_t n);

signals:
    void choosedCard(CARD*);

public slots:
    void addToMap(std::vector<CARD*>&);

    void removeFromMap(std::vector<CARD*>&);

    void clickedCard(CARD*);

    void customizeButtons(bool cards, bool beaten, bool take, bool take_away);

    //потом слот понадобится для графического отображения сигнала об ошибке!
    //void changeCardState(CARD*);
};

//-----------------------------PRICUP'S ITEM-----------------------------
class FOOL_PRICUP_SET_VIEW: public QObject, public MY_ITEM
{
Q_OBJECT
public:
    FOOL_PRICUP_SET_VIEW(QPointF pos, int w, int h):MY_ITEM(pos, w, h){}

    CARD_ITEM *pileImg, *trumpImg;

public slots:
    void gaveOut(CARD*);

    void removeFromPile(size_t);
};

//-----------------------------FIELD'S ITEM-----------------------------
class FOOL_FIGHT_FIELD_SET_VIEW : public QObject, public MY_ITEM
{
Q_OBJECT
public:
    FOOL_FIGHT_FIELD_SET_VIEW(QPointF pos, int w, int h):MY_ITEM(pos, w, h){}

    //std::map<CARD*, CARD_BTN*> my_map;
    std::vector<CARD_ITEM*> cards_in_fight;
    QString text;
    void paint(QPainter*, const QStyleOptionGraphicsItem*, QWidget*) override;

    QPointF getMyPos(bool, size_t);

public slots:
    void addCardItem(CARD*, bool, size_t);

    void removeAllItems();
};


//-----------------------------BEATEN'S ITEM-----------------------------
class FOOL_BEATEN_SET_VIEW:public QObject, public MY_ITEM
{
Q_OBJECT
public:
    FOOL_BEATEN_SET_VIEW(QPointF pos, int w, int h):MY_ITEM(pos, w, h){}

    CARD_ITEM *pileImg;

public slots:
    void firstAdded();
};
#endif // BUTTON_HPP
