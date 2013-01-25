#ifndef BASEAGENT_H
#define BASEAGENT_H

#include <cstdlib>
#include <iostream>
#include "tronmap.h"

using namespace std;

class BaseAgent
{
public:
    explicit BaseAgent(int Player);
    virtual char percept() =0;
    void setMap(TronMap* map);
    int Team();
    bool isEmpty(int x,int y);
    int nextX(int x,char c);
    int nextY(int y,char c);
	int ABS(int a);
    Point head();
	Point ehead();
protected:
    TronMap* map;
private:
    int team;
};

#endif // BASEAGENT_H
