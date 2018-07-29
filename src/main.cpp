#include <QApplication>
#include <QObject>
//#include "fool/Table.h"
#include <QList>
#include <QDebug>
#include "src/drawing/GameScene.h"
#include "src/fool/Fool.h"

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);

  SCENE_VIEW game_scene;
  FOOL_GAME *fool = new FOOL_GAME();
  game_scene.setGame(fool);
  fool->game();
  //QList<QGraphicsItem*> l = game_scene.items();
  //qDebug() << l.size();
  //QGraphicsItem* i = l.back();
  game_scene.show();

  return a.exec();
}
