#ifndef ROBOT_H
#define ROBOT_H

#include <QList>
#include <QDebug>
#include <QMessageBox>
#include "position.h"
#include "map.h"
#include "graph.h"
#include "sleeper.h"

class Robot {
  private:
    Position current;
    Position target;
    Map * map;
    int steps;
    bool targetFound;
    QMessageBox * message;
    Graph graph;
    void findTarget ();
    void scanPerimeter ();

  public:
    Robot (Map * m);
    ~Robot ();
};

#endif
