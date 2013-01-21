#include "mapdrawer.h"

MapDrawer::MapDrawer(TronMap *map, QWidget *parent) :
    QWidget(parent)
{
    this->map = map;

    background = QBrush(QColor(255, 255, 255));
    p1b=QBrush(QColor(255,0,0));
    p2b=QBrush(QColor(0,0,255));
    p1h=QBrush(QColor(100,0,0));
    p2h=QBrush(QColor(0,0,100));
    empty=QBrush(QColor(255,255,255));
    block=QBrush(QColor(100,100,100));

    p_p1b=QPen(QColor(255,0,0));
    p_p2b=QPen(QColor(0,0,255));
    p_p1h=QPen(QColor(100,0,0));
    p_p2h=QPen(QColor(0,0,100));
    p_empty=QPen(QColor(0,0,0));
    p_block=QPen(QColor(100,100,100));

}

void MapDrawer::paintEvent(QPaintEvent *event)
{
    QPainter painter;

    painter.begin(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.fillRect(event->rect(), background);
    painter.translate(20,20);

    for(int i=0; i<map->MapSize.X; i++)
        for(int j=0; j<map->MapSize.Y; j++)
        {
            if(map->MapData[i][j] == C_Empty)
            {
                painter.setBrush(empty);
                painter.setPen(p_empty);
            }
            if(map->MapData[i][j] == C_Block)
            {
                painter.setBrush(block);
                painter.setPen(p_block);
            }
            if(map->MapData[i][j] == C_Player1Body)
            {
                painter.setBrush(p1b);
                painter.setPen(p_p1b);
            }
            if(map->MapData[i][j] == C_Player2Body)
            {
                painter.setBrush(p2b);
                painter.setPen(p_p2b);
            }
            if(map->MapData[i][j] == C_Player1Head)
            {
                painter.setBrush(p1h);
                painter.setPen(p_p1h);
            }
            if(map->MapData[i][j] == C_Player2Head)
            {
                painter.setBrush(p2h);
                painter.setPen(p_p2h);
            }

            painter.drawEllipse(QPoint(i*10,j*10), 5, 5);
        }

    //qDebug() << "REPAINT";

    painter.end();
}
