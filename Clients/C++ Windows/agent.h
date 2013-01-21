#ifndef AGENT_H
#define AGENT_H

#include "baseagent.h"

class Agent : public BaseAgent
{
public:
    Agent(int Player);
    char percept();
};

#endif // AGENT_H
