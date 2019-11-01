//============================================================================
// Name        : ajamesOthello.cpp
// Author      : Andrew James
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================


#define WHITE	0b0000000000000000000010000000100000001000000000000000000000000000Ull
#define BLACK	0b0000000000000000000000000011000000010000000000000000000000000000Ull
#define SWHITE	0b0000000000000000000000000001000000001000000000000000000000000000Ull
#define SBLACK	0b0000000000000000000000000000100000010000000000000000000000000000Ull
#define MASK_E  0xFEFEFEFEFEFEFEFEUll
#define MASK_W  0x7F7F7F7F7F7F7F7FUll

//#define MASK_E	0b1111111011111110111111101111111011111110111111101111111011111110Ull;
//#define MASK_W	0b0111111101111111011111110111111101111111011111110111111101111111Ull;
#define MASK_N	 0x00FFFFFFFFFFFFFFUll
#define MASK_S	 0xFFFFFFFFFFFFFF00Ull
#define TESTM	0b1000000000000000000000000000000000000000000000000000000000000000Ull
#define ZEROS	0b0000000000000000000000000000000000000000000000000000000000000000Ull


#include <vector>
#include <list>
#include <iterator>
#include <sstream>
#include <string>
#include <iostream>
#include <stdlib.h>     /* srand, rand */
using namespace std;



class Board
{
	public:
	unsigned long long agent,enemy;
	unsigned long long moveList [64];
	std::string enemyColor, agentColor;
	int myColor;
	bool turn;
	Board(char flag)
	{
		turn = true;
		agentColor = flag;
		if(flag == 'B')
		{
			agent = SBLACK;
			enemy = SWHITE;
			enemyColor = "W";
			myColor = 1;
		}
		else
		{
			agent = SWHITE;
			enemy = SBLACK;
			enemyColor = "B";
			myColor = 1;
		}
		for(int i =0; i<64; i++)moveList[i] = 0;
	}

	void setColor(char flag)
	{
		agentColor = flag;
		if(flag == 'B')
		{
			agent = SBLACK;
			enemy = SWHITE;
			enemyColor = "W";
			myColor = 1;
		}
		else
		{
			agent = SWHITE;
			enemy = SBLACK;
			enemyColor = "B";
			myColor = 0;
		}
	}

	string moveOut(bool player,unsigned long long move)
	{
		string str;
		//move = 3Ull;
		int i = 0;
		if(player)
		{
			str += 'B';
		}
		else
		{
			str += 'W';
		}

		if(move)
		{
			while((i<64) && ((move & ~(1Ull << i))))i++;
			char x = ((i)%8) + 97;
			char y = ((i)/8) + 49;
			str = str + ' ' + x + ' ' + y;
		}
		return str;
	}
 //################################################################################
	void moveIn(string in)
	{
		unsigned long long mover;


		//cout << mover << endl;
		if(in.length() > 3)
		{
			int y = in.at(2) - 97;
			int x = in.at(4) - 49;
			int n;
			n = (8 * x) + y;
			mover = 1Ull << n;
			if(in.at(0) == 'B' && myColor)
			{
				ApplyMoves(1,mover);
			}
			else if(in.at(0) == 'B' && !myColor)
			{
				ApplyMoves(0,mover);
			}
			else if(in.at(0) == 'W' && !myColor)
			{
				ApplyMoves(1,mover);
			}
			else
			{
				ApplyMoves(0,mover);
			}
		}

	}

	unsigned long long generateMoves(bool player)
	{
		unsigned long long genAgent,genEnemy,placeHolder,captured;
		unsigned long long moves = 0;

		if(!player)
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
		cout << "C Generated Moves:" << endl;
		printBB(moves);
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

	std::string toString()
	{
		int i;
		int bit = 0;
		std::string board = "C     ";

		//for (i = 0; i < 16; i++)
		//	board += ("##");
		//board += ("\nC     ");
		string abc = "<a><b><c><d><e><f><g><h>";
		board.append(abc);

		board += ("\nC     ");

		for (i = 0; i < 12; i++)
			board += ("==");
		board += ("\n");


		for (i = 1; i <= 8; i++) {
			board.append("C <");
			board.append(mstring(i));
			board.append("> ");
			for (int j = 1; j <= 8; j++) {
				if (myColor == 1) {
					if (((agent >> bit) & 1) != 0)
						board += (" B ");
					else if (((enemy >> bit) & 1) != 0)
						board += (" W ");
					else
						board += (" - ");
				} else {
					if (((agent >> bit) & 1) != 0)
						board += (" W ");
					else if (((enemy >> bit) & 1) != 0)
						board += (" B ");
					else
						board += (" - ");
				}
				bit++;
			}
			board += ("\n");
		}

		board += ("C     ");
		for (i = 0; i < 12; i++)
			board += ("==");
		board += ("\nC ");

		board += "Turn is:";
		if(turn)
		{
			board += "Black";
		}
		else
		{
			board += "White";
		}

		//board += ("\nC ");

		//for (i = 0; i < 16; i++)
		//	board = board.append("##");

		return board;

	}

	unsigned long long Evaluate()
	{
		int movenumber = 0;
		vector <unsigned long long> randMove;
		for(int i = 0; i < 64; i++)
		{
			if(moveList[i])
			{
				movenumber++;
				//printBB(moveList[i]);
				randMove.push_back(moveList[i]);
			}
		}
		if(movenumber)
		{
			int k = rand() % randMove.size();

			return randMove.at(k);
		}
		else
		{
			return ZEROS;
		}

	}

	unsigned long long shiftN(unsigned long long bb)
	{
		return (bb & MASK_N) << 8;
	}

	unsigned long long shiftS(unsigned long long bb)
	{
		return (bb & MASK_S) >> 8;
	}

	unsigned long long  shiftE(unsigned long long bb)
	{
		return (bb & MASK_E) >> 1;
	}
	unsigned long long  shiftW(unsigned long long bb)
	{
		  return (bb & MASK_W) << 1;
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

	string mstring(int i)
	{
		std::string out_string;
		std::stringstream ss;
		ss << i;
		out_string = ss.str();
		return out_string;
	}
	string cstring(char i)
		{
			std::string out_string;
			std::stringstream ss;
			ss << i;
			out_string = ss.str();
			return out_string;
		}

	int bbCount(unsigned long long b)
	{
		int cnt=0;
		while(b)
		{
			b &= (b-1);
			cnt++;
		}
		return cnt;
	}

	void makeMoveList(unsigned long long b)
	{
		unsigned long long comp;
		for(int i =0; i<64; i++)moveList[i] = 0;
		for(int i = 0;i<64;i++)
		{
			comp = (1Ull << i);
			if(b & comp )
			{

				moveList[i] = comp;
				//printBB(moveList[i]);
			}
		}
	}
	void printBB(unsigned long long bb)
	{

		string place = "C ";
		for(int i = 1; i<64;i++)
		{

			if((i % 8) == 0)
			{

				place += "\nC ";
			}
			if(bb & (1Ull << i))
			{
				place += "  1";
			}
			else
			{
				place += "  0";
			}


		}
		cout << place << endl;

	}

};




int main() {
	string inStr = "I W";
	bool flag = 1;
	Board b('W');
	string s = "W b 7";

	//b.printBB(b.agent);

	cout << "C Please Initialize Player!" << endl;
	getline (cin,inStr);

	if(inStr == "I B")
	{
		b.setColor('B');
		//b.turn = 1;

		cout << "R B" << endl;
	}
	else
	{
		b.setColor('W');
		//b.turn = 1;
		cout << "R W" << endl;
	}


	cout << b.toString() << endl;

	if(b.myColor)
	{
		b.turn = !(b.turn);
		b.makeMoveList(b.generateMoves(b.turn));
		b.turn = !(b.turn);
		string outStr = b.moveOut(b.turn,b.Evaluate());
		b.moveIn(outStr);
		if(b.bbCount((b.agent & b.enemy) >= 64))
		{
			int blackColor;
			if(b.turn)
			{
				blackColor = b.bbCount(b.agent);
			}
			else
			{
				blackColor = -1 * (b.bbCount(b.enemy));
			}
			flag = 0;
			cout << blackColor << endl;
		}
		else
		{
			cout << "Agent Moves:" << endl;
			cout << outStr << endl;
		}
		b.turn = !(b.turn);
		cout << b.toString() << endl;
	}

	while(flag)
	{
		cout << "C Please Submit Move!" << endl;
		getline (cin,inStr);
		if(inStr[0] == 'C') {}
		else if(inStr[0] == 'W' ||inStr[0] == 'B')
		{
			b.moveIn(inStr);
			b.turn = !(b.turn);
			cout << b.toString() << endl;

			//cout << !((b.turn)) << endl;
			//cout << b.turn << endl;

			string outStr;

			if(b.myColor == 1)
			{
				b.turn = !(b.turn);
				b.makeMoveList(b.generateMoves(b.turn));
				b.turn = !(b.turn);
				outStr = b.moveOut(b.turn,b.Evaluate());
			}
			else
			{
				b.makeMoveList(b.generateMoves(b.turn));
				 outStr = b.moveOut(b.turn,b.Evaluate());
			}



			if(b.bbCount((b.agent & b.enemy) >= 64))
			{
				int blackColor;
				if(b.turn)
				{
					blackColor = b.bbCount(b.agent);
				}
				else
				{
					blackColor = -1 * (b.bbCount(b.enemy));
				}
				b.turn = ~ b.turn;
				flag = 0;
				cout << blackColor << endl;
			}
			else
			{
				cout << "C Agent Moves:" << endl;
				cout << outStr << endl;
				b.moveIn(outStr);
			}
		}
		else
		{
			flag = 0;
		}
		b.turn = !(b.turn);
		//cout << b.toString() << endl;
	}

	return 0;
}
