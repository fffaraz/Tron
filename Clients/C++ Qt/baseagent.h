#ifndef BASEAGENT_H
#define BASEAGENT_H

#include <QObject>

#include "tronmap.h"

class BaseAgent : public QObject
{
    Q_OBJECT
public:
    explicit BaseAgent(int Team, QObject *parent =0);
    virtual char Percept(TronMap* map) =0;
    int Team();

private:
    int team;
};

#endif // BASEAGENT_H
