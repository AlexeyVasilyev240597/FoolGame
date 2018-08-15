#include <QDebug>
#include "GameScene.h"
#include "../abstract/MyItem.h"
#include "../fool/Table.h"
#include <QObject>

SCENE_VIEW::SCENE_VIEW(FOOL_GAME *game)
{
    QObject::connect(game, &FOOL_GAME::addElem,
                     this, &SCENE_VIEW::addItem);

   //пройдись по ним и посмотри, что убрать
  setRenderHint(QPainter::Antialiasing);

  setCacheMode(QGraphicsView::CacheNone);

  setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);


  setWindowTitle("FOOL");

  setFrameStyle(0);
  setSceneRect(0, 0, 960, 640);
  setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
  setFixedSize(960, 640);

  mScene.setItemIndexMethod(QGraphicsScene::NoIndex);

  //connect(game, &FOOL_GAME::initPlayer,
          //this, &SCENE_VIEW::addItem);

  //game = new FOOL_GAME();

  setScene(&mScene);
  //initGameScene();
}
/*
void SCENE_VIEW::initGameScene(){
    //connect(game, &FOOL_GAME::initTableElem,
      //      this, &SCENE_VIEW::addItem);

   for (size_t i = 0; i < my_items.size(); i++)
            mScene.addItem(my_items[i]);

   game->game();

   for (size_t i = 0; i < table.size(); i++)
            mScene.addItem(table[i]);

   qWarning() << "i am in initGameScene";
}
*/
void SCENE_VIEW::addItem(MY_ITEM* item){
        mScene.addItem(item);
}
/*
//------------------------------------------------------------------------------
void FOOL_PLAYER_SET_VIEW::runSetView()
{
    for (int i = 0; i < itemVec.size(); i++){
        itemVec[i]->setPos(50 + 100*i, 50 + 100*i);
        //card_btns[i].setImage(":/pics/cards_pics/0/1/6.png");
        connect(itemVec[i], &BUTTON::btnMouseReleaseEvent,
                this, &SET_VIEW::btn_Card_clicked);

        //в этой последовательности они "накладываются" друг на друга
        mScene.addItem(itemVec[i]);
    }
}
*/
/*
//------------------------------------------------------------------------------
void SET_VIEW::btn_B_clicked(Qt::MouseBUTTON aBtn)
{
  qWarning() << "B clicked " << aBtn;
}
//------------------------------------------------------------------------------
void SET_VIEW::btn_C_clicked(Qt::MouseBUTTON aBtn)
{
  qWarning() << "C clicked " << aBtn;
}

//------------------------------------------------------------------------------
void SET_VIEW::btn_Card1_clicked(Qt::MouseBUTTON aBtn)
{
  qWarning() << "Card clicked 1";
  mBtnCard1.setPos(200, 200);
}
void SET_VIEW::btn_Card2_clicked(Qt::MouseBUTTON aBtn)
{
  qWarning() << "Card clicked 2";
  mBtnCard2.setPos(400, 200);

}
void SET_VIEW::btn_Card3_clicked(Qt::MouseBUTTON aBtn)
{
  qWarning() << "Card clicked 3";
  mBtnCard3.setPos(600, 200);
}
*/
/*
void SET_VIEW::btn_Card_clicked(Qt::MouseButton aBtn)
{
  qWarning() << "some Card clicked";
  //mBtnCard3.setPos(600, 200);
}
*/
