/*************************
 * BOARD.H
 * board class declaration
 ************************/
#ifndef _BOARD_H_
#define _BOARD_H_

#include <vector>
#include <list>
#include <iterator>
#include <sstream>
#include <string>
#include <iostream>
#include <stdlib.h> 

using namespace std;

class Board {
public:
	
	unsigned long long agent,enemy,mblack,mwhite;
	vector <unsigned long long> moveList;
	//unsigned long long moveList [64];
	std::string enemyColor, agentColor;
	int myColor,moveNumber;
	bool turn;
	char mflag;
	Board(char flag, unsigned long long black, unsigned long long white);
	Board();
	void setColor(char flag, unsigned long long black,
			unsigned long long white);
	string moveOut(bool player, unsigned long long move);
	void moveIn(string in);
	unsigned long long generateMoves(bool player);
	
	void ApplyMoves(bool player, unsigned long long move);
	std::string toString();
	unsigned long long Evaluate(Board b);
	unsigned long long shiftNE(unsigned long long bb);
	unsigned long long shiftNW(unsigned long long bb);
	unsigned long long shiftSE(unsigned long long bb);
	unsigned long long shiftSW(unsigned long long bb);
	unsigned long long shiftN(unsigned long long bb);
	unsigned long long shiftS(unsigned long long bb);
	unsigned long long shiftE(unsigned long long bb);
	unsigned long long shiftW(unsigned long long bb);
	string mstring(int i);

	string cstring(char i);
	int bbCount(unsigned long long b);
	void makeMoveList(unsigned long long b);
	void printBB(unsigned long long bb);

};

#endif
