#ifndef AIOPTIMIZED_H
#define AIOPTIMIZED_H

#include <string>
#include <iostream>
#include "AIgeneric.h"
#include "AIoptimizedmove.h"

class AIoptimized : public AIgeneric {
    public:
	AIoptimized();
	~AIoptimized();
	string name;
	virtual int getNextMove(const int*, const int &);
	virtual int pawnPromotion(const int*, const int &);
    private:
	double computeValue(const int *, int);
	double negamax(double, double, int); 
	int valuelist[8];
	double val;
	int board[125];
	int depth;
	AIoptimizedmove * mover;
};

#endif
