#ifndef TRONCLIENT_H
#define TRONCLIENT_H

#include <QObject>
#include <QUdpSocket>
#include <QDebug>

#include "tronmap.h"
#include "baseagent.h"

class TronClient : public QObject
{
    Q_OBJECT
public:
    explicit TronClient(BaseAgent* agent, QObject *parent = 0);
    TronMap* GetMap();

private:
    QUdpSocket* m_udp;
    TronMap m_map;
    BaseAgent* m_agent;
    void processTheDatagram(QByteArray datagram);

signals:
    void MapUpdated();

private slots:
    void readPendingDatagrams();

public slots:

    
};

#endif // TRONCLIENT_H
