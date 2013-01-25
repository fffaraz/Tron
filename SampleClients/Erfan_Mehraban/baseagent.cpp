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
    if(x>=0 && y>=0 && x<map->MapSize.X && y<map->MapSize.Y)
	{
			if ( map->MapData[x][y]==C_Empty)
			{
				return true;
			}
	}
    return false;
}

int BaseAgent::nextX(int x,char c)
{
    if(c=='r')
        return x+1;
    else if(c=='l')
        return x-1;
    return x;
}

int BaseAgent::nextY(int y,char c)
{
    if(c=='d')
        return y+1;
    else if(c=='u')
        return y-1;
    return y;
}

Point BaseAgent::ehead()
{
    if(team==1)
        return map->Head2;
    return map->Head1;
}

Point BaseAgent::head()
{
    if(team==1)
        return map->Head1;
    return map->Head2;
}

int BaseAgent::ABS(int a)
{
	int b=a*(-1);
	if (a<0) return b;
	return a;
}
