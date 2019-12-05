/*************************
* BOARD.CPP
* board class implementation
************************/
#ifndef _BOARD_CPP_
#define _BOARD_CPP_

#include "Eval.cpp"
#include "Macros.hpp"
#include "Board.hpp"
#include <vector>
#include <list>
#include <iterator>
#include <sstream>
#include <string>
#include <iostream>
#include <stdlib.h>     /* srand, rand */
using namespace std;

unsigned long long agent,enemy,mblack,mwhite;
vector <unsigned long long> moveList;
std::string enemyColor, agentColor;
int myColor,moveNumber;
bool mturn;
char flag;


Board::Board()
{
	moveNumber = 0;
	myColor = 1;
	mwhite = SWHITE;
	mblack = SBLACK;
	agent = mblack;
	enemy = mwhite;
	turn = true;
	mflag = 1;
	flag = mflag;
};
Board::Board(char flag, unsigned long long black, unsigned long long white)
{
	turn = true;
	mflag = flag;
	mwhite = white;
	mblack = black;
	moveNumber = 0;
	agentColor = flag;
	if(flag == 'B')
	{
		agent = black;
		enemy = white;
		enemyColor = "W";
		myColor = 1;
	}
	else
	{
		agent = white;
		enemy = black;
		enemyColor = "B";
		myColor = 1;
	}
	moveList.clear();
	//for(int i =0; i<64; i++)moveList[i] = 0;
}

void Board::setColor(char flag,unsigned long long black, unsigned long long white)
{
	agentColor = flag;
	if(flag == 'B')
	{
		agent = black;
		enemy = white;
		enemyColor = "W";
		myColor = 1;
	}
	else
	{
		agent = white;
		enemy = black;
		enemyColor = "B";
		myColor = 0;
	}
}

string Board::moveOut(bool player,unsigned long long move)
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
void Board::moveIn(string in)
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

unsigned long long Board::generateMoves(bool player)
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

void Board::ApplyMoves(bool player,unsigned long long move)
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

std::string Board::toString()
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

unsigned long long Board::Evaluate(Board b)
{
	int maxEval = 0;
	double maxDbl = 0;
	double place = 0;
	int movenumber = 0;
	vector <unsigned long long> randMove;
	//cout << "HereI" << endl;
	int g = moveList.size();
	for(int i = 0; i < g; i++)
	{

			movenumber++;
			Board f(b.mflag,b.mblack,b.mwhite);
			f.ApplyMoves(true,moveList.at(i));
			f.makeMoveList(f.generateMoves(f.turn));
			Eval e(f);
			place = e.evaluate();
			//cout << place << endl;
			if(place > maxDbl)
			{
				maxDbl = place;
				maxEval = i;
			}
	}
			//printBB(moveList[i]);
			//randMove.push_back(moveList[i]);

	if(movenumber)
	{
		//int k = rand() % randMove.size();

		return moveList.at(maxEval);
	}
	else
	{
		return ZEROS;
	}

}

unsigned long long Board::shiftN(unsigned long long bb)
{
	return (bb & MASK_N) << 8;
}

unsigned long long Board::shiftS(unsigned long long bb)
{
	return (bb & MASK_S) >> 8;
}

unsigned long long  Board::shiftE(unsigned long long bb)
{
	return (bb & MASK_E) >> 1;
}
unsigned long long  Board::shiftW(unsigned long long bb)
{
	  return (bb & MASK_W) << 1;
}
unsigned long long  Board::shiftNE(unsigned long long bb)
{
	return shiftN(shiftE(bb));
}
unsigned long long  Board::shiftNW(unsigned long long bb)
{
	return shiftN(shiftW(bb));
}
unsigned long long  Board::shiftSE(unsigned long long bb)
{
	return shiftS(shiftE(bb));
}
unsigned long long  Board::shiftSW(unsigned long long bb)
{
	return shiftS(shiftW(bb));
}

string Board::mstring(int i)
{
	std::string out_string;
	std::stringstream ss;
	ss << i;
	out_string = ss.str();
	return out_string;
}
string Board::cstring(char i)
	{
		std::string out_string;
		std::stringstream ss;
		ss << i;
		out_string = ss.str();
		return out_string;
	}

int Board::bbCount(unsigned long long b)
{
	int cnt=0;
	while(b)
	{
		b &= (b-1);
		cnt++;
	}
	return cnt;
}

void Board::makeMoveList(unsigned long long b)
{
	unsigned long long comp;
	moveList.clear();
	for(int i = 0;i<64;i++)
	{
		comp = (1Ull << i);
		if(b & comp )
		{

			moveList.push_back(comp);
			//printBB(moveList[i]);
		}
	}
}
void Board::printBB(unsigned long long bb)
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



#endif //_BOARD_CPP_
