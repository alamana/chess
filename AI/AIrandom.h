#ifndef AIRANDOM_H
#define AIRANDOM_H
#include "chessmove.h"
#include "AIgeneric.h"

class AIrandom : public AIgeneric {
    public:
	AIrandom();
	string name;
	virtual int getNextMove(const int*, const int &);
	virtual int pawnPromotion(const int*, const int &);
};



#endif
