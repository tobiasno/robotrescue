#ifndef GRAPH_H
#define GRAPH_H

#include <QList>
#include <QPair>
#include <QQueue>
#include <QDebug>
#include "position.h"

class Graph {
  private:
    QList <int> nodes;
    QList <QPair <int, int>> adj;
    bool isVisited (QList <QPair <int, bool>> & list, int n);
    void markVisited (QList <QPair <int, bool>> & list, int n);
    //void markDistance (QList <QPair <int, int>> & list, int newDistance, int n);
    //int getDistance (QList <QPair <int, int>> & list, int n);
    QList <int> getAdj (int n);

  public:
    Graph ();
    bool addNode (int n);
    bool connectNodes (int from, int to);
    bool contains (int n);
    bool isConnected (int from, int to);
    Position getClosestTo (Position p, QList <int> notthis);
    QList <Position> findShortestPath (int start, int target);
};

#endif
