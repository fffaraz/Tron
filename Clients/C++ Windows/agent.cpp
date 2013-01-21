#include "agent.h"

Agent::Agent(int Player) :
    BaseAgent(Player)
{
}

char Agent::percept()
{
    //Your Code Goes Here:
    int x=head().X;
    int y=head().Y;
    string w;
    if(Team()==1)
        w="drul";
    else
        w="uldr";
    for(int i=0;i<3;i++)
    {
        if(isEmpty(nextX(x,w[i]),nextY(y,w[i])))
            return w[i];
    }
    return w[3];
}
