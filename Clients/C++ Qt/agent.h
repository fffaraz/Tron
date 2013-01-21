#ifndef AGENT_H
#define AGENT_H

#include "baseagent.h"

class Agent : public BaseAgent
{
    Q_OBJECT

public:
    Agent(int Team, QObject *parent = 0);
    char Percept(TronMap* map);
    
};

#endif // AGENT_H
