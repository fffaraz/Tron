#include "tronserver.h"
#include <QGraphicsScene>


Point nPoint(uint16 x, uint16 y)
{
    Point t;
    t.X = x;
    t.Y = y;
    return t;
}

TronServer::TronServer(QString ip1, QString ip2, int sizeX, int sizeY, int blocks, QObject *parent) :
    QObject(parent)
{
    m_udp = new QUdpSocket(this);
    m_udp->bind(QHostAddress::Any, 30001, QUdpSocket::ReuseAddressHint);
    connect(m_udp, SIGNAL(readyRead()), this, SLOT(UdpData()));

    m_timer = new QTimer(this);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(TimerShot()));

    m_IP1 = ip1;
    m_IP2 = ip2;
    last_move_1 = 'd';
    last_move_2 = 'u';
    m_state = ans_1 = ans_2 = false;

    ClearMap(sizeX, sizeY);
    RandMap(blocks);

    qDebug() << "Server Created!";
}

void TronServer::ClearMap(int sizeX, int sizeY)
{
    m_map.Cycle = 0;
    m_map.CycleLen = 0;
    sizeX = min(sizeX, MAX_X);
    sizeY = min(sizeY, MAX_Y);
    m_map.MapSize = nPoint(sizeX,sizeY);
    m_map.Head1 = nPoint(0,0);
    m_map.Head2 = nPoint(sizeX-1, sizeY-1);

    for(int i=0; i<sizeX; i++)
        for(int j=0; j<sizeY; j++)
            m_map.MapData[i][j] = C_Empty;

    m_map.MapData[0]      [0]       = C_Player1Head;
    m_map.MapData[sizeX-1][sizeY-1] = C_Player2Head;

    emit MapUpdated();
}

void TronServer::RandMap(int blocks)
{
    QTime time = QTime::currentTime();
    qsrand((uint)time.msec());

    for(int i=0; i<blocks; i++)
    {
        int randX = (qrand() % (m_map.MapSize.X-2)) + 1;
        int randY = (qrand() % (m_map.MapSize.Y-2)) + 1;
        if(m_map.MapData[randX][randY]==C_Block)
        {
            i--;
            continue;
        }
        m_map.MapData[randX][randY] = C_Block;
    }

    emit MapUpdated();
}

void TronServer::LoadMap(QString file)
{
    ifstream fin(file.toStdString().c_str());

    int sizeX, sizeY, Blocks;
    fin>>sizeX;
    fin>>sizeY;
    fin>>Blocks;

    ClearMap(sizeX, sizeY);

    for(int i=0; i<Blocks; i++)
    {
        int bx, by;
        fin>>bx>>by;
        m_map.MapData[bx][by] = C_Block;
    }

    emit MapUpdated();
}

void TronServer::Start(int Interval)
{
    m_map.CycleLen = Interval;
    m_state = true;
    m_timer->setInterval(Interval);
    m_timer->start();
    qDebug() << "Start " << Interval;
}

void TronServer::Stop()
{
    m_state = false;
    m_timer->stop();
    qDebug() << "Stop";
}

void TronServer::TimerShot()
{
    if(!m_state) return;
    if(ans_1 || ans_2) Play();
    QByteArray bytdata((char*)(&m_map), sizeof(struct TronMap));
    QHostAddress br = QHostAddress::Broadcast;
    if(!m_state) return;
    m_udp->writeDatagram(bytdata, br, 30000);
    qDebug() << "Sent" << bytdata.size() << br.toString();
    ans_1 = false;
    ans_2 = false;
    emit MapUpdated();
}

void TronServer::Play()
{
    Point h1 = m_map.Head1;
    Point h2 = m_map.Head2;
    Point nh1 = h1;
    Point nh2 = h2;

    switch(last_move_1)
    {
    case 'u':
        nh1.X = nh1.X -1;
        break;
    case 'd':
        nh1.X = nh1.X +1;
        break;
    case 'r':
        nh1.Y = nh1.Y +1;
        break;
    case 'l':
        nh1.Y = nh1.Y -1;
        break;
    }

    switch(last_move_2)
    {
    case 'u':
        nh2.X = nh2.X -1;
        break;
    case 'd':
        nh2.X = nh2.X +1;
        break;
    case 'r':
        nh2.Y = nh2.Y +1;
        break;
    case 'l':
        nh2.Y = nh2.Y -1;
        break;
    }

    int over = isGameOver(nh1, nh2);

    if(over)
    {
        Stop();
        emit GameOver(over);
    }
    else
    {
        m_map.MapData[h1.X] [h1.Y]  = C_Player1Body;
        m_map.MapData[nh1.X][nh1.Y] = C_Player1Head;
        m_map.Head1 = nh1;

        m_map.MapData[h2.X] [h2.Y]  = C_Player2Body;
        m_map.MapData[nh2.X][nh2.Y] = C_Player2Head;
        m_map.Head2 = nh2;
    }
}

int TronServer::isGameOver(Point nh1, Point nh2)
{
   bool over_1 = false;
   bool over_2 = false;

   if(!(nh1.X<m_map.MapSize.X) || !(nh1.Y<m_map.MapSize.Y))
   {
       over_1 = true;
       qDebug() << "GAMEOVER 1 (max)";
   }

   if(!(nh1.X>-1) || !(nh1.Y>-1))
   {
       over_1 = true;
       qDebug() << "GAMEOVER 1 (min)";
   }

   if(!(nh2.X<m_map.MapSize.X) || !(nh2.Y<m_map.MapSize.Y))
   {
       over_2=true;
       qDebug() << "GAMEOVER 2 (max)";
   }

   if(!(nh2.X>-1) || !(nh2.Y>-1))
   {
       over_2 = true;
       qDebug() << "GAMEOVER 2 (min)";
   }

   if(!over_1 && !over_2)
   {
       if(m_map.MapData[nh1.X][nh1.Y] != C_Empty)
       {
           over_1 = true;
           qDebug() << "GAMEOVER 1";
       }

       if(m_map.MapData[nh2.X][nh2.Y] != C_Empty)
       {
           over_2 = true;
           qDebug() << "GAMEOVER 2";
       }

       if(nh2.X==nh1.X && nh1.Y==nh2.Y)
       {
           over_1 = over_2 = true;
           qDebug() << "GAMEOVER 1 & 2";
       }
   }

   if(over_1 && over_2) return 3;
   if(over_1) return 1;
   if(over_2) return 2;
   return 0;
}

void TronServer::UdpData()
{
    while (m_udp->hasPendingDatagrams())
    {
        QByteArray datagram;
        datagram.resize(m_udp->pendingDatagramSize());
        QHostAddress sender;
        quint16 senderPort;
        m_udp->readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);
        qDebug() << sender.toString() << datagram;
        processTheDatagram(sender.toString(), datagram);
    }
}

void TronServer::processTheDatagram(QString ip, QString data)
{
    if (!m_state) return;
    if (data.length() != 2) return;

    char c = data.toStdString()[0];
    char t;

    if      (ip == m_IP1) t = '1';
    else if (ip == m_IP2) t = '2';
    else return;

    if (m_IP1 == m_IP2)
    {
        t = data.toStdString()[1];
    }

    if(t=='1' && ans_1) return;
    if(t=='2' && ans_2) return;

    if(t=='1' && (c=='u' || c=='d' || c=='r' || c=='l'))
    {
        ans_1 = true;
        last_move_1 = c;
    }

    if(t=='2' && (c=='u' || c=='d' || c=='r' || c=='l'))
    {
        ans_2 = true;
        last_move_2 = c;
    }
}

TronServer::~TronServer()
{
    m_udp->close();
    m_udp->deleteLater();
    m_timer->stop();
    m_timer->deleteLater();
}

TronMap* TronServer::GetMap()
{
    return &m_map;
}
