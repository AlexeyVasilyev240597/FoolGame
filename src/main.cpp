#include <QApplication>
//#include <QObject>
#include <QDebug>
#include "src/drawing/GameScene.h"
#include "src/fool/Fool.h"

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);

  SCENE_VIEW game_scene;
  FOOL_GAME fool;
  game_scene.setItems(fool.getItems());
  fool.game();
  game_scene.show();  

  return a.exec();
}
