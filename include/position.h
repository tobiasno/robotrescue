#ifndef POSITION_H
#define POSITION_H

#include <QPair>

class Position {
  private:
    int position;

  public:
    Position ();
    Position (int x, int y);
    Position (int x);
    int getPosition ();
    QPair <int, int> getPositionAsPair ();
    bool equals (Position & p);
    Position getUp ();
    Position getDown ();
    Position getLeft ();
    Position getRight ();
};

#endif

