#include <QApplication>
//#include <QObject>
#include <QDebug>
#include "src/drawing/GameScene.h"
#include "src/fool/Fool.h"

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);

  FOOL_GAME fool;
  FOOL_ITEM_MANAGER manager;
  SCENE_VIEW game_scene(&manager);

  fool.init(&manager);
  fool.game();
  game_scene.show();  

  return a.exec();
}
