//============================================================================
// Name        : ajamesOthello.cpp
// Author      : Andrew James
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
#define _POSIX_SOURCE

#include <stdbool.h>
#include <unistd.h>
#include "Eval.cpp"
#include "Macros.hpp"
#include "Board.hpp"
//#include "Board.cpp"
#include <vector>
#include <time.h>
#include <signal.h>
#include <sys/types.h>
#include <list>
#include <iterator>
#include <sstream>
#include <string>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>     /* srand, rand */
#include <sys/time.h>

#include <sys/types.h>

using namespace std;



void sigalrm_handler(int sig)
{
    // This gets called when the timer runs out.  Try not to do too much here;
    // the recommended practice is to set a flag (of type sig_atomic_t), and have
    // code elsewhere check that flag (e.g. in the main loop of your program)
}



int main() {
	string inStr = "I W";
	bool flag = 1;
	Board b('W', SBLACK, SWHITE);
	string s = "W b 7";

	//b.printBB(b.agent);

	cout << "C Please Initialize Player!" << endl;
	getline (cin,inStr);

	if(inStr == "I B")
	{
		b.setColor('B',SBLACK, SWHITE);
		//b.turn = 1;

		cout << "R B" << endl;
	}
	else
	{
		b.setColor('W',SBLACK, SWHITE);
		//b.turn = 1;
		cout << "R W" << endl;
	}


	cout << b.toString() << endl;
	//sleep(30000);
	if(b.myColor)
	{
		b.moveNumber++;
		b.turn = !(b.turn);
		b.makeMoveList(b.generateMoves(b.turn));

		b.turn = !(b.turn);
		string outStr = b.moveOut(b.turn,b.Evaluate(b));
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
				outStr = b.moveOut(b.turn,b.Evaluate(b));
			}
			else
			{
				b.makeMoveList(b.generateMoves(b.turn));
				 outStr = b.moveOut(b.turn,b.Evaluate(b));
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
