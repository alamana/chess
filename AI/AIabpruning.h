#ifndef AIABPRUNING_H
#define AIABPRUNING_H

#include <string>
#include <iostream>
#include "AIgeneric.h"

using namespace std;

class AIabpruning : public AIgeneric {
    public:
	AIabpruning();
	string name;
	virtual int getNextMove(const int*, const int &);
	virtual int pawnPromotion(const int*, const int &);
    private:
	double computeValue(const int *, int);
	double negamax(int *, int, double, double, int, int); 
};

#endif
