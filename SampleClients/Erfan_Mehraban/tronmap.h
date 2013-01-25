#ifndef TRONMAP_H
#define TRONMAP_H

#define C_E  0
#define C_B  3
#define C_B1 1
#define C_B2 2
#define C_H1 10
#define C_H2 20
#define MAX_X 100
#define MAX_Y 100

typedef unsigned short int uint16;
typedef          short int  int16;
struct Point
{
    int16 X;
    int16 Y;
};

enum CellType
{
    C_Empty = 0,
    C_Block = 3,
    C_Player1Body = 1,
    C_Player2Body = 2,
    C_Player1Head = 10,
    C_Player2Head = 20
};

enum MoveType
{
    C_UP = 'u',
    C_DOWN = 'd',
    C_LEFT = 'l',
    C_RIGHT = 'r'
};


// sizeof(TronMap) == 2 + 2 + 4 + 10000 + 4 + 4 == 10016
struct TronMap
{
    uint16 Cycle;
    uint16 CycleLen;
    Point MapSize;
    char  MapData[MAX_X][MAX_Y];
    Point Head1;
    Point Head2;
};


#endif // TRONMAP_H
