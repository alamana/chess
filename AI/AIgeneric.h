#ifndef AIGENERIC_H
#define AIGENERIC_H

#include <string>

using namespace std;

class AIgeneric {
    public:
	virtual int getNextMove(int*, const int &) = 0;
	virtual int pawnPromotion(int*, const int &) = 0;
	string name;
};

#endif
