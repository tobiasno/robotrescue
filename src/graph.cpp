#include "../include/graph.h"

Graph :: Graph () {
}

bool Graph :: addNode (int n) {
  if (!contains (n)) {
    nodes . append (n);
    //Position test = Position (n); qDebug () << "Add node:" << test . getPositionAsPair () . first << test . getPositionAsPair () . second;
    return true;
  } else {
    return false;
  }
}

bool Graph :: connectNodes (int from, int to) {
  if (!isConnected (from, to)) {
    adj . append (QPair <int, int> (from, to));
    return true;
  } else {
    return false;
  }
}

bool Graph :: contains (int n) {
  return nodes . contains (n);
}

bool Graph :: isConnected (int from, int to) {
  bool result = false;
  QList <QPair <int, int>> :: iterator i;
  for (i = adj . begin (); i != adj . end (); i++) {
    //qDebug () << *i;
    if ((i -> first == from && i -> second == to) || (i -> first == to && i -> second == from)) {
      result = true;
    }
  }
  return result;
}

QList <int> Graph :: getAdj (int n) {
  QList <int> result;
  QList <QPair <int, int>> :: iterator i;
  for (i = adj . begin (); i != adj.end (); i++) {
    if (result . isEmpty ()) {
      if (n == i -> first) {
        result . append (i -> second);
      }
      if (n == i -> second) {
        result . append (i -> first);
      }
    } else {
      if (n == i -> first && !result . contains (i -> second)) {
        result . append (i -> second);
      }
      if (n == i -> second && !result . contains (i -> first)) {
        result . append (i -> first);
      }
    }
  }
  return result;
}

Position Graph :: getClosestTo (Position p, QList <int> notthis) {
  Position result = Position ();
  int prevDistance = 1000;
  QList <int> :: iterator i;
  for (i = nodes . begin (); i != nodes . end (); i++) {
    Position tmp = Position (*i);
    int newDistanceX = p . getPositionAsPair () . first - tmp . getPositionAsPair () . first;
    int newDistanceY = p . getPositionAsPair () . second - tmp.getPositionAsPair () . second;
    if (newDistanceX < 0) {
      newDistanceX *= -1;
    }
    if (newDistanceY < 0) {
      newDistanceY *= -1;
    }
    if (newDistanceX + newDistanceY < prevDistance && !notthis . contains (tmp . getPosition ())) {
      result = tmp;
      prevDistance = newDistanceX + newDistanceY;
    }
  }
  qDebug () << "Next best Target:" << result . getPositionAsPair () . first << result . getPositionAsPair () . second;
  return result;
}

QList <Position> Graph :: findShortestPath (int start, int target) {
  // Declare data structures for BFS
  QList <QPair <int, bool>> visited;
  //QList <QPair <int, int>> distance;
  QList <QPair <int, int>> pi;
  QQueue <int> queue;
  QList <Position> result;
  // Mark all nodes but the start as non visited and mark distance as unlimited
  QList <int> :: iterator i;
  for (i = nodes . begin (); i != nodes . end (); i++) {
    if (*i != start) {
      visited.append (QPair <int, bool> (*i, false));
      //distance . append (QPair <int, int> (*i, 1000));
      //qDebug () << *i;
    }
  }
  // Mark start as visited
  visited . append (QPair <int, bool> (start, true));
  // Distance of start to star is 0
  //distance . append (QPair <int, int> (start, 0));
  // Add start to pi with no predecessor
  pi . append (QPair <int, int> (start, -1));
  // Add start to the queue
  queue . enqueue (start);
  // BFS: while queue not empty, remove start from queue, get adj list of start,
  // for each node adj to start mark as visited, record predecessor and add to queue
  while (!queue . empty ()) {
    start = queue . dequeue ();
    //qDebug () << start;
    QList <int> sAdj = getAdj (start);
    QList <int> :: iterator j;
    for (j = sAdj . begin (); j != sAdj . end (); j++) {
      //qDebug () << "Node in adj list:" << *j;
      if (!isVisited (visited, *j)) {
        markVisited (visited, *j);
        //markDistance (distance, getDistance (distance, start) + 1, *j);
        pi.append (QPair <int, int> (*j, start));
        //qDebug () << "Mark node as visited:" << *j << "Predecessor:" << start << "Distance:" << getDistance (distance, *j);
        queue.enqueue (*j);
      }
    }
    //qDebug () << "New adj list";
  }
  //qDebug () << "Queue empty!";
  result.append (Position (target));
  //qDebug () << "Insert into path:" << target;
  // Extrace path for robot
  for (int i = 0; i < pi . size (); i++) {
    QList <QPair <int, int>> :: iterator k;
    for (k = pi . begin (); k != pi . end (); k++) {
      if (k -> first == target && k -> second != -1) {
        result . prepend (Position (k -> second));
        target = k -> second;
        //qDebug () << "Insert into path:" << k -> second;
        //pi.erase (k);
      }
    }
  }
  result . removeFirst (); //test
  //qDebug () << "First position in BFS result:" << result.first ().getPositionAsPair ().first << result.first ().getPositionAsPair ().second;
  return result;
}

bool Graph :: isVisited (QList <QPair <int, bool>> & list, int n) {
  bool result = false;
  QList <QPair <int, bool>> :: iterator i;
  for (i = list . begin (); i != list . end (); i++) {
    if (i -> first == n && i -> second == true) {
      result = true;
    }
  }
  return result;
}

void Graph :: markVisited (QList <QPair <int, bool>> & list, int n) {
  QList <QPair <int, bool>> :: iterator i;
  for (i = list . begin (); i != list . end (); i++) {
    if (i -> first == n) {
      *i = QPair <int, bool> (i -> first, true);
    }
  }
}

/*void Graph :: markDistance (QList <QPair <int, int>> & list, int newDistance, int n) {
  QList <QPair <int, int>> :: iterator i;
  for (i = list . begin (); i != list . end (); i++) {
    if (i -> first == n) {
      *i = QPair <int, int> (i -> first, newDistance);
    }
  }
}

int Graph :: getDistance (QList <QPair <int, int>> & list, int n) {
  int result = 1000;
  QList <QPair <int, int>> :: iterator i;
  for (i = list . begin (); i != list . end (); i++) {
    if (i -> first == n) {
      result = i -> second;
    }
  }
  return result;
}*/
