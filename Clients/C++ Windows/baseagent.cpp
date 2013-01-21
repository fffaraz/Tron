#include "baseagent.h"

BaseAgent::BaseAgent(int Player)
{
    team = Player;
}

void BaseAgent::setMap(TronMap *map)
{
	this->map = map;
}

int BaseAgent::Team()
{
    return team;
}

bool BaseAgent::isEmpty(int x,int y)
{
    if(x<0 || y<0 || map->MapSize.X<=x || map->MapSize.Y<=y || map->MapData[x][y]!=C_Empty)
        return false;
    return true;
}

int BaseAgent::nextX(int x,char c)
{
    if(c=='d')
        return x+1;
    else if(c=='u')
        return x-1;
    return x;
}

int BaseAgent::nextY(int y,char c)
{
    if(c=='r')
        return y+1;
    else if(c=='l')
        return y-1;
    return y;
}

Point BaseAgent::head()
{
    if(team==1)
        return map->Head1;
    return map->Head2;
}
