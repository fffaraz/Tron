#include "agent.h"

Agent::Agent(int Player) :
    BaseAgent(Player)
{
}

char Agent::percept()
{
	int x = head().X;
	int y = head().Y;
	//cout << "head : " << x << " , " << y << endl;
	string moves;
    if(Team()==1)
        moves="drul"; //harkat da jahate padsaat gard
    else
        moves="uldr"; // harkat da jahate saat gard

	for (int i =0;i<map->MapSize.X;i++)
		for (int j =0;j<map->MapSize.Y;j++)
			mark[i][j]=false; //hameye mark haro false mikone! hamaro pak mikone

	for (int i =0;i<map->MapSize.X;i++)
		for (int j =0;j<map->MapSize.Y;j++)
			enemy_mark[i][j]=false; //hameye enemy_mark haro false mikone! hamaro pak mikone

	
	for (int i =0;i<4;i++)
		for (int j =0;j<4;j++)
			score[i][j]=0; //hameye score haro 0 mikone


	for (int move=0;move<4;move++) // emtiaz dehi be har harekat
	{
		Point here_now;	here_now.X=nextX(x,moves[move]); here_now.Y=nextY(y,moves[move]); 
		//mark[here_now.X][here_now.Y]=true;//jaii ke mire!
		if (isEmpty(here_now.X,here_now.Y)) // age por bood ke hichi!
		{
			//cout << "x and y now :" << here_now.X << " , "<<here_now.Y;
			score[move][1]=painting(here_now,'m')+1; //chand ta khoone mitoone bere
			//cout << "painting of " << moves[move] <<" is : "<< score[move][1] << endl;


			Point enemy_head=ehead(); //sare yaroo ro mirize to enemy_head
			int enemy_score[4]={0}; // emtiaz haro hame 0 mokine!
			enemy_mark[here_now.X][here_now.Y]=true; //injaii ro ke alan hast mark mikone!
			for (int enemy_move=0;enemy_move<4;enemy_move++) //baraye har harekat harif mikhad emtiaz hesab bokone
			{
				Point enemy_pos;	enemy_pos.X=nextX(enemy_head.X,moves[enemy_move]);	enemy_pos.Y=nextY(enemy_head.Y,moves[enemy_move]); 
				enemy_mark[enemy_pos.X][enemy_pos.Y]=true;
				if (isEmpty(enemy_pos.X,enemy_pos.Y))
				{
					enemy_score[enemy_move]=painting(enemy_pos,'e');
					//cout << "\t painting enemy " << moves[enemy_move] << " is : "<< enemy_score[enemy_move] << endl;
					//cout << "\t"<< "enemy pos: "<< enemy_pos.X << " , " << enemy_pos.Y << endl;
					for (int i =0;i<map->MapSize.Y;i++) //enemy mark ro 0 mikone
						for (int j =0;j<map->MapSize.X;j++)
							enemy_mark[i][j]=false; //hameye enemy_mark haro false mikone! hamaro pak mikone
				}
			}

			int minus=findmin(enemy_score,4,0);
			for (int i=0;i<4;i++)
			{
				if (enemy_score[i]!=0) enemy_score[i]=enemy_score[i]-minus;
				score[move][2]+=enemy_score[i];
				//cout << "\t now enemy score of " << moves[i] <<" is " << enemy_score[i] <<endl;
			}
			

			score[move][3]=getdistance(here_now,ehead());
			if (score[move][3] <= 1) {/*cout << "nazdiiiiiiiiiiik!"<<endl;*/ stuck(); }

			for (int i =0;i<map->MapSize.Y;i++)
				for (int j =0;j<map->MapSize.X;j++)
					mark[i][j]=false; //hameye mark haro false mikone!
		}
	}

	int min=10000;
	for (int i=0;i<4;i++)
		if (score[i][1]<min && score[i][1]!=0)
			min = score[i][1];


	for (int i=0;i<4;i++)
		if (score[i][1]!=0)
		{
			score[i][1]=score[i][1]-min;
			//cout << "now the painting of " <<moves[i] << " is : " << score[i][1] <<"and the min is " << min <<endl;
		}

		min=10000;
		int min_id;
		for (int i=0;i<4;i++)
			if (score[i][3]<min && score[i][3]!=0)
			{
				min = score[i][3];
				min_id=i;
			}

		
		for (int i=0;i<4;i++)
		{
			if (i!=min_id)
				score[i][3]=0;
			else
				score[i][3]=2; ///////////////////////////////////////////////////////////////////////////////////////////////////
		}

		//cout << "now the closest is : "<< moves[min_id] << " Point : " << score[min_id][3] << endl;


	//jamm score ha
	for (int move=0;move<4;move++)
	{
		score[move][0]+=score[move][1]+score[move][3]-score[move][2];
	}
	
	int max_char_id=0;
	int max_score=0;
	for (int move=0;move<4;move++)
	{
		if (max_score<score[move][0])
		{
			//cout <<"score move "<< moves[move] <<" is bigger than previouse :"<< score[move][0] <<endl;
			max_score = score[move][0];
			max_char_id = move;
		}
	}
	cout << "our algorithm output: "<< moves[max_char_id] <<endl << "\t and the score is " << max_score<<endl ;
	if (max_score!=0) 
		return moves[max_char_id];
	return stuck();
	//return stuck();
}

int Agent::painting(Point here , char side)
{
	int return_value = 0; Point temp;
	temp.Y=here.Y;
	temp.X=here.X-1;	return_value += paint(temp, side);
	temp.X=here.X+1;	return_value += paint(temp, side);
	temp.X=here.X;
	temp.Y=here.Y-1;	return_value += paint(temp, side);
	temp.Y=here.Y+1;	return_value += paint(temp, side);
	temp.Y=here.Y;
	return return_value;
			
}

int Agent::paint(Point here, char side)
{
	int x = here.X; int y = here.Y;
	int counter = 0;
	if(isEmpty(x, y))
			{
				if (side == 'm')
				{
					if (!mark[x][y])
					{
						counter++;
						Point next; next.X=x; next.Y=y;
						mark[x][y]=true;
						//cout << "painted : " << x <<  " , " << y << endl;
						counter+=painting(next,'m');
					}
				}
				if (side == 'e')
				{
					if (!enemy_mark[x][y])
					{
						counter++;
						Point next; next.X=x; next.Y=y;
						enemy_mark[x][y]=true;
						//cout << "painted enemy: " << x <<  " , " << y << endl;
						counter+=painting(next,'e');
					}
				}
			}
	return counter;
}

char Agent::stuck()
{
	int x = head().X;
	int y = head().Y;
	string moves;
    if(Team()==1)
        moves="uldr";
    else
        moves="drul";

	for(int i=0;i<3;i++)
    {
		Point nextp; nextp.X=nextX(x,moves[i]); nextp.Y=nextY(y,moves[i]);
		//cout << "distans for stuck " << getdistance(head(),nextp) << endl;
		if(isEmpty(nextp.X,nextp.Y)) //&& getdistance(head(),nextp)>1 )
		{ /*cout << "raft too if!!" << endl;*/  cout << "stuck "<< moves[i] << endl;   return moves[i]; }
		
    }
	return moves[3];
}

int Agent::findmin(int a[],int len,int except)
{
	int min=10000;
	for (int i=0;i<len;i++)
		if (a[i] != except)
			if (a[i]<min) min=a[i];
	return min;
}

int Agent::getdistance(Point start,Point end)
{
	return ABS(start.X-end.X)+ABS(start.Y-end.Y);
}