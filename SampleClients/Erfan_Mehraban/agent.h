#ifndef AGENT_H
#define AGENT_H

#include "baseagent.h"
#include "tronmap.h"


class Agent : public BaseAgent
{
public:
    Agent(int Player);
    char percept();
	int score[4][4];//avval = urdl dovoom= sum, tedad harekatii ke mitoonam beram , man- harekataye yaroo , nazdike (-1 ya 1)
	int painting(Point here, char side);
	int paint (Point here, char side);
	bool isStuck();
	bool mark[MAX_X][MAX_Y];
	bool enemy_mark[MAX_X][MAX_Y];
	char stuck();
	int findmin(int a[],int len,int except);
	int getdistance(Point start,Point end);
	int getFreeArea();
};

#endif // AGENT_H
