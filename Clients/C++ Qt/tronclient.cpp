#include "tronclient.h"

TronClient::TronClient(BaseAgent *agent, QObject *parent) :
    QObject(parent)
{
    m_agent = agent;
    m_udp = new QUdpSocket(this);
    m_udp->bind(QHostAddress::Any, 30000, QUdpSocket::ReuseAddressHint);
    connect(m_udp,SIGNAL(readyRead()),this,SLOT(readPendingDatagrams()));
}

void TronClient::readPendingDatagrams()
{
    while (m_udp->hasPendingDatagrams())
    {
        QByteArray datagram;
        datagram.resize(m_udp->pendingDatagramSize());
        QHostAddress sender;
        quint16 senderPort;
        m_udp->readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);
        processTheDatagram(datagram);
    }
}

void TronClient::processTheDatagram(QByteArray datagram)
{
    memcpy((void*)(&m_map), datagram.data(), datagram.size());
    emit MapUpdated();
    char ans[3];
    ans[0] = m_agent->Percept(&m_map);
    ans[1] = m_agent->Team()==1?'1':'2';
    ans[2] = 0;
    m_udp->writeDatagram(ans,2,QHostAddress::Broadcast,30001);
    qDebug() << ans;
}


TronMap* TronClient::GetMap()
{
    return &m_map;
}
