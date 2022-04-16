#ifndef MAP_H
#define MAP_H

#include <QApplication>
#include <QDebug>
#include <QVector>
#include <stdlib.h>
#include <time.h>
#include "position.h"
#include "graphicalmap.h"

class Map {
  private:
    QVector <char> fields;
    Position robotLocation;
    Position target;
    Position setRandomFieldTo (char c);
    void setField (Position p, char c);
    GraphicalMap * gmap;
    void redrawMap ();

  public:
    Map ();
    ~Map ();
    bool isEmpty (Position p);
    bool isObstacle (Position p);
    bool isTarget (Position p);
    Position deployRobot ();
    bool moveRobot (Position p);
    Position getTargetPosition ();
};

#endif
