#ifndef _MY_ITEM_H
#define _MY_ITEM_H

#include <QObject>
#include <QGraphicsItem>
#include <QString>
#include <QPointF>
#include <QPixmap>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QApplication>
#include "CardDeck.h"

class MY_ITEM : /*public QObject, */public QGraphicsItem
{
public:
  MY_ITEM(QPointF pos, int width = 0, int heigth = 0);

  QRectF boundingRect() const override;

  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

  int mWidth{0};
  int mHeigth{0};
};

/*
 * в paint() drawPixmap исходя из my_card face:
 *  UP or TO_US - лицо, DOWN or FROM_US - рубашка;
 * тогда загружать рубашку в каждую карту
 */
class CARD_ITEM :public MY_ITEM{
public:
    CARD_ITEM(QPointF pos, CARD* c = NULL):MY_ITEM(pos, 0, 0){
        my_card = c;

        QString path = ":/pics/cards_pics/";
        if (c == NULL)
            path += "0/0.png";
        else{
            path += QString::number((int)c->getColor());
            path += '/';
            path += QString::number((int)c->getSuit());
            path += '/';
            path += QString::number((int)c->getRank());
            path += ".png";
        }

        setImage(path);
    }

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
protected:
    QPixmap mPixMap;
    CARD *my_card;

    void setImage(QString aPath){
        mPixMap.load(aPath);
        mWidth  = mPixMap.width();
        mHeigth = mPixMap.height();
    }
};

class BUTTON : public QObject, public MY_ITEM{
Q_OBJECT
public:
    //38x38???
  BUTTON(QPointF pos, const QString text):MY_ITEM(pos, 38, 38){
      my_text = text;
      setAcceptedMouseButtons(Qt::LeftButton);
  }

  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

  void mousePressEvent(QGraphicsSceneMouseEvent *)  override;
  void mouseReleaseEvent(QGraphicsSceneMouseEvent *)override;

signals:
  void buttonClicked(Qt::MouseButton);

private:
  QString my_text;

};


#endif // _MY_ITEM_H
