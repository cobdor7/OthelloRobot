//============================================================================
// Name        : isit64.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
#define MASK_W	0b0111111101111111011111110111111101111111011111110111111101111111LL
#define MASK_F	0b1111111111111111111111111111111111111111111111111111111111111111LL
#include <iostream>
#include <bitset>
#include <stdint.h>
using namespace std;

int main() {
	long long as = MASK_W;

	//std::bitset<64> x(longint);
	//std::cout << x << '\n';
	printf("%llx\n",as);


	return 0;
}
