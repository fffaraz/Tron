#include "agent.h"

Agent::Agent(int Team, QObject *parent) :
    BaseAgent(Team, parent)
{
}

char Agent::Percept(TronMap* map)
{
    if(Team()==1) return 'd';
    else return 'u';
}
