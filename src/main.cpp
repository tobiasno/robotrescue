/**
 * @author Tobias Nolte <tobias.nolte@stud.hshl.de>
 */  

#include <QApplication>
#include "../include/map.h"
#include "../include/robot.h"
#include "../include/graph.h"
#include "../include/position.h"

int main (int argc, char *argv[]) {
  QApplication app(argc, argv);

  qDebug() << "Start";

  Map * m_pointer;
  Map m;
  m_pointer = & m;
  Robot r (m_pointer);

  qDebug() << "End";

  return app.exec();
}
