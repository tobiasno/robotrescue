#include "../include/position.h"

Position :: Position () {
  position = 0;
}

Position :: Position (int x, int y) {
  if (x < 0) {
    x = 0;
  }
  if (y < 0) {
    y = 0;
  }
  position = (x + y * 25) % 625;
}

Position :: Position (int x) {
  if (x < 0) {
    x = 0;
  }
  position = x % 625;
}

int Position :: getPosition () {
  return position;
}

QPair<int, int> Position :: getPositionAsPair () {
  return QPair <int, int> (position % 25, (position - (position % 25)) / 25);
}

bool Position :: equals (Position & p) {
  return position == p . getPosition ();
}

Position Position :: getUp () {
  if (getPositionAsPair() . second > 0) {
    return Position (getPositionAsPair() . first, getPositionAsPair() . second - 1);
  } else {
    return Position (getPositionAsPair() . first, getPositionAsPair() . second);
  }
}

Position Position :: getDown () {
  if (getPositionAsPair() . second < 24) {
    return Position (getPositionAsPair() . first, getPositionAsPair() . second + 1);
  } else {
    return Position (getPositionAsPair() . first, getPositionAsPair() . second);
  }
}

Position Position :: getLeft () {
  if (getPositionAsPair() . first > 0) {
    return Position (getPositionAsPair() . first - 1, getPositionAsPair() . second);
  } else {
    return Position (getPositionAsPair() . first, getPositionAsPair() .second);
  }
}

Position Position :: getRight () {
  if (getPositionAsPair() . second < 24) {
    return Position (getPositionAsPair() . first + 1, getPositionAsPair() . second);
  } else {
    return Position (getPositionAsPair() . first, getPositionAsPair() . second);
  }
}
