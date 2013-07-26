#ifndef AINEGASCOUT_H
#define AINEGASCOUT_H

#include <string>
#include <iostream>
#include "AIgeneric.h"

using namespace std;

class AInegascout : public AIgeneric {
    public:
	AInegascout();
	string name;
	virtual int getNextMove(const int*, const int &);
	virtual int pawnPromotion(const int*, const int &);
    private:
	double computeValue(const int *, int);
       	double negascout(int *, int, double, double, int, int);
	int movecount;
};

#endif
