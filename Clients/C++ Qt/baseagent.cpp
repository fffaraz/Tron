#include "baseagent.h"

BaseAgent::BaseAgent(int Team, QObject *parent) :
    QObject(parent)
{
    team = Team;
}

int BaseAgent::Team()
{
    return team;
}
