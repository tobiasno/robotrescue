#include "../include/map.h"

Map :: Map () : gmap (new GraphicalMap ()) {
  srand (time (NULL));
  for (int i = 0; i < 625; i++) {
    if (rand () % 100 + 1 <= 15) {
      fields . append ('O');
      //qDebug () << "Obstacle at: " << i;
    } else {
      fields . append ('E');
    }
  }
  target = setRandomFieldTo ('T');
  qDebug () << "Target at:" << target . getPositionAsPair () . first << target . getPositionAsPair () . second;
  gmap -> setFields (fields);
  gmap -> show ();
}

Map :: ~Map () {
  delete gmap;
}

Position Map :: setRandomFieldTo (char c) {
  srand (time (NULL));
  int count = 1;
  Position p;
  while (count > 0) {
    p = Position (rand () % 25, rand () % 25);
    if (fields . at (p . getPosition()) == 'E') {
      fields.replace (p . getPosition(), c);
      count--;
    }
  }
  return p;
}

bool Map :: isEmpty (Position p) {
  if (fields . at (p . getPosition()) == 'E') {
    return true;
  } else {
    return false;
  }
}

bool Map :: isObstacle (Position p) {
  if (fields . at (p . getPosition()) == 'O') {
    return true;
  } else {
    return false;
  }
}

bool Map :: isTarget (Position p) {
  if (fields . at (p . getPosition()) == 'T') {
    return true;
  } else {
    return false;
  }
}

Position Map :: deployRobot () {
  robotLocation = setRandomFieldTo ('R');
  qDebug () << "Robot starts at: " << robotLocation . getPositionAsPair () . first << robotLocation . getPositionAsPair () . second;
  redrawMap ();
  return robotLocation;
}

bool Map :: moveRobot (Position p) {
  if (!isObstacle (p)) {
    setField (robotLocation, 'E');
    setField (p, 'R');
    robotLocation = p;
    redrawMap ();
    return true;
  } else {
    return false;
  }
}

void Map :: setField (Position p, char c) {
  fields . replace (p . getPosition(), c);
}

Position Map :: getTargetPosition () {
  return target;
}

void Map :: redrawMap () {
  gmap -> setFields (fields);
  gmap -> update ();
  qApp->processEvents ();
}
