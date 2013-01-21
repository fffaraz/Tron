#ifndef TRONSERVER_H
#define TRONSERVER_H

#include <QObject>
#include <QTimer>
#include <QTime>
//#include <QUdpSocket>
//#include <QtNetwork>
#include <QtNetwork/QUdpSocket>
#include <QDebug>
#include <algorithm>
#include <fstream>

using namespace std;

#include "tronmap.h"

class TronServer : public QObject
{
    Q_OBJECT

public:
    TronServer(QString ip1, QString ip2, int blocks, int sizeX, int sizeY, QObject *parent = 0);
    TronMap* GetMap();
    ~TronServer();

private:
    TronMap     m_map;

    QUdpSocket *m_udp;
    QTimer     *m_timer;
    QString     m_IP1;
    QString     m_IP2;

    char last_move_1;
    char last_move_2;
    bool m_state;
    bool ans_1;
    bool ans_2;

    void processTheDatagram(QString ip, QString data);
    int  isGameOver(Point nh1, Point nh2);
    void Play();

signals:
    void GameOver(int Player);
    void MapUpdated();
    
public slots:
    void Start(int Interval);
    void Stop();
    void ClearMap(int sizeX, int sizeY);
    void RandMap(int blocks);
    void LoadMap(QString file);

private slots:
    void TimerShot();
    void UdpData();
    
};

#endif // TRONSERVER_H
