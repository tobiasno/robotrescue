#include "../include/robot.h"

Robot :: Robot (Map * m) : map (m), steps (0), targetFound (false), graph () {
  current = map -> deployRobot ();
  //qDebug () << current . getPositionAsPair () . first << " " << current . getPositionAsPair () . second;
  target = map -> getTargetPosition ();
  findTarget ();
}

Robot :: ~Robot () {
  delete message;
}

void Robot :: findTarget () {
  if (current . getPosition() == target . getPosition()) {
    qDebug () << "Robot started on target. 0 steps needed.";
  } else {
    int failsafe = 0;
    QList <int> badpositions;
    while (!targetFound && steps <= 80 && failsafe <= 1000) {
      Position remember = current;
      scanPerimeter ();
      Position nextBest = graph.getClosestTo (target, badpositions);
      //qDebug () << current.getPosition () << " " << target.getPosition ();
      QList <Position> path = graph . findShortestPath (current . getPosition (), nextBest . getPosition ());
      QList <Position> :: iterator i;
      for (i = path . begin (); i != path . end (); i++) {
        qDebug () << "Move robot to:" << i -> getPositionAsPair () . first << i -> getPositionAsPair () . second;
        if (map -> moveRobot (*i)) {
          current = *i;
          steps++;
        }
        Sleeper :: msleep (150);
      }
      // If nextBest was not reachable, add it to the list of position
      // that the robot is not suposed to chose again.
      if (remember . equals (current)) {
        badpositions . append (nextBest . getPosition ());
        qDebug () << "Attempted new position was not reachable";
      } else {
        badpositions . clear ();
      }
      if (current.equals (target)) {
        targetFound = true;
      }
      failsafe++;
    }
    if (!targetFound) {
      qDebug() << "Failed to find Target";
      QString report = QString ("The robot has exhausted it's steps and failed to find the target.");
      message = new QMessageBox (QMessageBox::NoIcon, "Stopped!", report, QMessageBox::Ok, NULL);
      message -> show ();
    } else {
      qDebug() << "Target found after " << steps << " steps.";
      QString report = QString ("The robot has found the target after %1 steps.") . arg (steps);
      message = new QMessageBox (QMessageBox::NoIcon, "Success!", report, QMessageBox::Ok, NULL);
      message -> show ();
    }
  }
}

void Robot :: scanPerimeter () {
  for (int i = -8; i <= 8; i++) {
    for (int j = -8; j <= 8; j++) {
      if (current . getPositionAsPair() . first + i >= 0 && current . getPositionAsPair() . first + i <= 24 &&
          current . getPositionAsPair() . second + j >= 0 && current . getPositionAsPair() . second + j <= 24) {
        Position tmp = Position (current . getPositionAsPair() . first + i, current . getPositionAsPair() . second + j);
        //qDebug () << current . getPositionAsPair() . first + i << " " << current . getPositionAsPair() . second + j;
        if (!map -> isObstacle (tmp)) {
          //qDebug () << tmp . getPositionAsPair () . first << " " << tmp . getPositionAsPair () . second;
          //qDebug () << "Insert into graph: " << tmp . getPosition ();
          graph.addNode (tmp . getPosition());
        }
      }
    }
  }
  for (int i = -8; i <= 8; i++) {
    for (int j = -8; j <= 8; j++) {
      Position tmp = Position (current . getPositionAsPair () . first + i, current . getPositionAsPair () . second + j);
      if (!map -> isObstacle (tmp)) {
        if (graph . contains (tmp . getUp () . getPosition ())) {
          graph . connectNodes (tmp . getPosition (), tmp . getUp () . getPosition ());
        }
        if (graph . contains (tmp . getRight ().getPosition ())) {
          graph . connectNodes (tmp . getPosition (), tmp . getRight () . getPosition ());
        }
        if (graph . contains (tmp.getDown () . getPosition ())) {
         graph.connectNodes (tmp . getPosition (), tmp . getDown () . getPosition ());
        }
        if (graph . contains (tmp . getLeft () . getPosition ())) {
          graph . connectNodes (tmp . getPosition (), tmp . getLeft () . getPosition ());
        }
      }
    }
  }
}
