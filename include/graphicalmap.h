#ifndef GRAPHICALMAP_H
#define GRAPHICALMAP_H

#include <QDebug>
#include <QVector>
#include <QWidget>
#include <QPaintEvent>
#include <QPainter>
#include <QPen>

class GraphicalMap : public QWidget {
  Q_OBJECT

  private:
    QVector <char> fields;
    void drawRect (int x, int y, int width, int height, QColor c);
    int widthofmap;
    int widthoffield;

  protected:
    void paintEvent (QPaintEvent * event);

  public:
    GraphicalMap ();
    void setFields (QVector <char> f);
};

#endif
