#include "../include/graphicalmap.h"

GraphicalMap :: GraphicalMap () : widthofmap (25), widthoffield (25) {
  resize (widthoffield * 25, width());
  resize (widthoffield * 25, height());
}

void GraphicalMap :: paintEvent (QPaintEvent * event) {
  int columnposition = 0;
  int rowposition = 0;
  for (int i = 0; i < fields . size (); i++) {
    if (columnposition >= widthoffield * 25) {
      columnposition = 0;
      rowposition += 25;
    }
    if (fields.at (i) == 'E') {
      drawRect (columnposition, rowposition, widthoffield, widthoffield, QColor(Qt  ::  lightGray));
    } else if (fields . at (i) == 'O') {
      drawRect (columnposition, rowposition, widthoffield, widthoffield, QColor(Qt  ::  black));
    } else if (fields . at (i) == 'R') {
      drawRect (columnposition, rowposition, widthoffield, widthoffield, QColor(Qt  ::  darkGreen));
    } else if (fields . at (i) == 'T') {
      drawRect (columnposition, rowposition, widthoffield, widthoffield, QColor(Qt  ::  magenta));
    }
    columnposition += 25;
  }
}

void GraphicalMap :: drawRect (int x, int y, int width, int height, QColor c) {
    QPainter p;
    p.begin (this);
    p.setRenderHint (QPainter  ::  Antialiasing);
    QPainterPath path;
    path.addRoundedRect (QRectF (x, y, width, height), 4, 4);
    QPen pen (Qt  ::  black, 2);
    p.setPen (pen);
    p.fillPath (path, c);
    p.drawPath (path);
    p.end ();
}

void GraphicalMap :: setFields (QVector <char> f) {
  fields = f;
}
