#ifndef MAPDRAWER_H
#define MAPDRAWER_H

#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QBrush>
#include <QColor>
#include <QDebug>

#include "tronmap.h"

class MapDrawer : public QWidget
{
    Q_OBJECT
public:
    explicit MapDrawer(TronMap* map, QWidget *parent = 0);

protected:
     void paintEvent(QPaintEvent *event);

private:
     TronMap* map;
     QBrush background;

     QBrush p1b;
     QBrush p2b;
     QBrush p1h;
     QBrush p2h;
     QBrush empty;
     QBrush block;

     QPen p_p1b;
     QPen p_p2b;
     QPen p_p1h;
     QPen p_p2h;
     QPen p_empty;
     QPen p_block;

signals:

public slots:

};

#endif // MAPDRAWER_H
