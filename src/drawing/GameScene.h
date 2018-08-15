#ifndef _GAME_SCENE
#define _GAME_SCENE

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QVariantMap>
#include <vector>

#include "../abstract/MyItem.h"
#include "../fool/Fool.h"
#include <vector>

class   FOOL_GAME;
class SCENE_VIEW : public QGraphicsView
{
public:
    //будет какой-нибудь connector, чтобы сцена не лазила по внутренностям игры
  SCENE_VIEW(FOOL_GAME *game);
public slots:
    void addItem(MY_ITEM* item);

private:
  QGraphicsScene mScene;
  QVariantMap my_items;

  void initGameScene();
};

#endif //_GAME_SCENE
