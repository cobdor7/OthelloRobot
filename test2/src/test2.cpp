//============================================================================
// Name        : test2.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================


#define SBLACK	0b0000000000000000000000000001000000001000000000000000000000000000ll;
#define SWHITE	0b0000000000000000000000000000100000010000000000000000000000000000ll;
#define MASK_E	0b1111111011111110111111101111111011111110111111101111111011111110ll;
#define MASK_W	0b0111111101111111011111110111111101111111011111110111111101111111;

#include <string>
#include <iostream>
using namespace std;



class Board
{
	public:
	unsigned long long agent,enemy;
	std::string enemyColor, agentColor;
	Board(char flag)
	{
		agentColor = flag;
		if(flag == 'B')
		{
			agent = SBLACK;
			enemy = SWHITE;
			enemyColor = "W";
		}
		else
		{
			agent = SWHITE;
			enemy = SBLACK;
			enemyColor = "B";
		}
	}

	unsigned long long generateMoves(bool player)
	{
		unsigned long long genAgent,genEnemy,placeHolder,moves,captured;

		if(player)
		{
			genEnemy = enemy;
			genAgent = agent;
		}
		else
		{
			genEnemy = agent;
			genAgent = enemy;
		}
		placeHolder = ~(genAgent | genEnemy);

		//North
		captured = shiftN(genAgent) & genEnemy;
		for(int i = 0;i < 5; i++)
		{
			captured |= shiftN(captured) & genEnemy;
		}
		moves |= shiftN(captured) & placeHolder;

		//South
		captured = shiftS(genAgent) & genEnemy;
		for(int i = 0;i < 5; i++)
		{
			captured |= shiftS(captured) & genEnemy;
		}
		moves |= shiftS(captured) & placeHolder;

		//East
		captured = shiftE(genAgent) & genEnemy;
		for(int i = 0;i < 5; i++)
		{
			captured |= shiftE(captured) & genEnemy;
		}
		moves |= shiftE(captured) & placeHolder;

		//West
		captured = shiftW(genAgent) & genEnemy;
		for(int i = 0;i < 5; i++)
		{
			captured |= shiftW(captured) & genEnemy;
		}
		moves |= shiftW(captured) & placeHolder;

		//NorthEast
		captured = shiftNE(genAgent) & genEnemy;
		for(int i = 0;i < 5; i++)
		{
			captured |= shiftNE(captured) & genEnemy;
		}
		moves |= shiftNE(captured) & placeHolder;

		//NorthWest
		captured = shiftNW(genAgent) & genEnemy;
		for(int i = 0;i < 5; i++)
		{
			captured |= shiftNW(captured) & genEnemy;
		}
		moves |= shiftNW(captured) & placeHolder;


		//SouthEast
		captured = shiftSE(genAgent) & genEnemy;
		for(int i = 0;i < 5; i++)
		{
			captured |= shiftSE(captured) & genEnemy;
		}
		moves |= shiftSE(captured) & placeHolder;

		//SouthWest
		captured = shiftSW(genAgent) & genEnemy;
		for(int i = 0;i < 5; i++)
		{
			captured |= shiftSW(captured) & genEnemy;
		}
		moves |= shiftSW(captured) & placeHolder;


		return moves;
	}

	void ApplyMoves(bool player,unsigned long long move)
	{
		unsigned long long Agent,Enemy,captured;

		if(player)
				{
					Enemy = enemy;
					Agent = agent;
				}
				else
				{
					Enemy = agent;
					Agent = enemy;
				}

		Agent |= move;

		//North
		captured = shiftN(move) & Enemy;
		for (int i = 0; i < 5; i++)
		{
			captured |= shiftN(captured) & Enemy;
		}
		 if ((shiftN(captured) & Agent) != 0) {
			 Agent |= captured;
			 Enemy &= ~captured;
		}

		//South
		captured = shiftS(move) & Enemy;
		for (int i = 0; i < 5; i++)
		{
			captured |= shiftS(captured) & Enemy;
		}
		 if ((shiftS(captured) & Agent) != 0) {
			 Agent |= captured;
			 Enemy &= ~captured;
		}


		 //East
		captured = shiftE(move) & Enemy;
		for (int i = 0; i < 5; i++)
		{
			captured |= shiftE(captured) & Enemy;
		}
		 if ((shiftE(captured) & Agent) != 0) {
			 Agent |= captured;
			 Enemy &= ~captured;
		}
		//West
		captured = shiftW(move) & Enemy;
		for (int i = 0; i < 5; i++)
		{
			captured |= shiftW(captured) & Enemy;
		}
		 if ((shiftW(captured) & Agent) != 0) {
			 Agent |= captured;
			 Enemy &= ~captured;
		}
		//NorthEast
		captured = shiftNE(move) & Enemy;
		for (int i = 0; i < 5; i++)
		{
			captured |= shiftNE(captured) & Enemy;
		}
		 if ((shiftNE(captured) & Agent) != 0) {
			 Agent |= captured;
			 Enemy &= ~captured;
		}

		//SouthEast
		captured = shiftSE(move) & Enemy;
		for (int i = 0; i < 5; i++)
		{
			captured |= shiftSE(captured) & Enemy;
		}
		 if ((shiftSE(captured) & Agent) != 0) {
			 Agent |= captured;
			 Enemy &= ~captured;
		}


		 //NorthWest
		captured = shiftNW(move) & Enemy;
		for (int i = 0; i < 5; i++)
		{
			captured |= shiftNW(captured) & Enemy;
		}
		 if ((shiftNW(captured) & Agent) != 0) {
			 Agent |= captured;
			 Enemy &= ~captured;
		}
		//SouthWest
		captured = shiftSW(move) & Enemy;
		for (int i = 0; i < 5; i++)
		{
			captured |= shiftSW(captured) & Enemy;
		}
		 if ((shiftSW(captured) & Agent) != 0) {
			 Agent |= captured;
			 Enemy &= ~captured;
		}

		 if(player)
		{
			enemy = Enemy;
			agent = Agent;
		}
		else
		{
			enemy = Agent;
			agent = Enemy;
		}

	}

	std::string toString(long long Agent, long long Enemy)
	{
		std::string  str = "BOARD\n Agent is:";
		str = str + agentColor;
		str.append("\n");
		for(int i = 1;i<65; i++)
		{
			if( ~((agent | enemy) & (1 << i)) )str.append(" - ");
			else if (agent & (1 << i))
			{
				str.append(" ");
				str.append(agentColor);
				str.append(" ");
			}
			else
			{
				str.append(" ");
				str.append(enemyColor);
				str.append(" ");
			}
			if( ~(i % 8)) str.append("\n");
		}
		return str;
	}

	int Evaluate()
	{
		return 0;
	}

	unsigned long long shiftN(long bb)
	{
		return bb << 8;
	}

	unsigned long long shiftS(long bb)
	{
		return bb >> 8;
	}

	unsigned long long  shiftE(unsigned long long bb)
	{
		bb &= MASK_E;
		return bb >> 1;
	}
	unsigned long long  shiftW(unsigned long long bb)
	{
		bb &= MASK_E;
		return bb << 1;
	}
	unsigned long long  shiftNE(unsigned long long bb)
	{
		return shiftN(shiftE(bb));
	}
	unsigned long long  shiftNW(unsigned long long bb)
	{
		return shiftN(shiftW(bb));
	}
	unsigned long long  shiftSE(unsigned long long bb)
	{
		return shiftS(shiftE(bb));
	}
	unsigned long long  shiftSW(unsigned long long bb)
	{
		return shiftS(shiftW(bb));
	}
};
int main() {
	Board b('B');

	cout << "!!!Hello Wld!!!" << endl; // prints !!!Hello World!!!
	return 0;
}

