#ifndef AIOPTIMIZED_H
#define AIOPTIMIZED_H

#include <string>
#include <iostream>
#include "AIgeneric.h"
#include "AIoptimizedmove.h"

class AIoptimized : public AIgeneric {
    public:
	AIoptimized();
	string name;
	virtual int getNextMove(const int*, const int &);
	virtual int pawnPromotion(const int*, const int &);
    private:
	double computeValue(const int *, int);
	double negamax(int *, int, double, double, int, int); 
	int valuelist[8];
	double val;
	AIoptimizedmove mover;
};

#endif
