/*************************
* EVAL.CPP
*
************************/
#ifndef _EVAL_CPP_
#define _EVAL_CPP_

#include "Eval.hpp"
#include "Macros.hpp"
#include "Board.hpp"
#include <vector>
#include <list>
#include <iterator>
#include <sstream>
#include <string>
#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <fstream>
#include <vector>
#include <climits>
#include <time.h>
#include <ctype.h>
#include <unistd.h>
#include <stdlib.h>



using namespace std;


class Eval {
public:

	Board board;
	double mgreedy;
    double mcornerCaptured;
    double mavoidX;
    double mobility;
    double mpotentialMobility;
    double msecured;
    double wedgeAlert;
    
	Eval(Board b)
	{
		
		board.setColor(b.mflag,b.mblack,b.mwhite);
	}

	double evaluate() 
	{    
    	double doubleValue = 0;
    	board.makeMoveList(board.generateMoves(1));
    	int myCount = board.moveList.size();
    
    	board.makeMoveList(board.generateMoves(0));
    	int oppCount = board.moveList.size();
    	int total = myCount + oppCount;
    	
    	mobility = 0;
        if (total != 0) {
            mobility = (myCount - oppCount) / (double) total;
        }
        mgreedy = greedy();
    	
    	if (total == 0) {
            double result = mgreedy * 1000;
            return result;
        }
        
        mcornerCaptured = cornerCaptured();
        wedgeAlert = wedge();
      
            doubleValue = 45*mgreedy + 60*mcornerCaptured + 135*mobility + 60*wedgeAlert;
        
    	
		return doubleValue;
	}

		double greedy() {
	        int myCount = board.bbCount(board.agent);
	        int oppCount = board.bbCount(board.enemy);
	        return (myCount - oppCount) / ((double) (myCount + oppCount));
	    }//greedy


	double cornerCaptured() 
	{
        unsigned long long corners = 0x8100000000000081l;
        int myCount = board.bbCount(board.agent & corners);
        int oppCount = board.bbCount(board.enemy & corners);
        return (myCount - oppCount) / 4.0;
    }

	//
	double wedge() {
        int myCount=0;
        int oppCount=0;
        double total = myCount+oppCount;
        if(total!=0) {
            return (oppCount-myCount)/total;
        }
        return 0.0;
    }
	


};

#endif
