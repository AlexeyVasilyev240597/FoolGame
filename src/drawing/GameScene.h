#ifndef _GAME_SCENE
#define _GAME_SCENE

#include <QGraphicsView>
#include <QGraphicsScene>
#include <vector>

#include "../abstract/MyItem.h"
//#include "../fool/Table.h"
//#include "../fool/Fool.h"
#include <vector>

class   FOOL_GAME;
class SCENE_VIEW : public QGraphicsView
{
public:
  SCENE_VIEW();
  void setItems(std::vector<MY_ITEM*> items);
//public slots:
    //void addItem(MY_ITEM* item);

private:
  //FOOL_GAME *game;
  QGraphicsScene mScene;
  //std::vector<MY_ITEM*> my_items;

  void initGameScene();
};

#endif //_GAME_SCENE
