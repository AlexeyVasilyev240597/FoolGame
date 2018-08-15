#ifndef _GAME_SCENE
#define _GAME_SCENE

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QVariantMap>
#include <vector>

#include "../abstract/MyItem.h"
//#include "../fool/Table.h"
#include "../fool/Fool.h"
#include <vector>

class   FOOL_GAME;
class SCENE_VIEW : public QGraphicsView
{
public:
  SCENE_VIEW(FOOL_GAME *game);
  //void setItems(std::vector<MY_ITEM*> items);
public slots:
    void addItem(MY_ITEM* item);

private:
  //FOOL_GAME *game;
  QGraphicsScene mScene;
  QVariantMap my_items;

  void initGameScene();
};

#endif //_GAME_SCENE
