#ifndef AIRANDOM_H
#define AIRANDOM_H
#include "chessmove.h"
#include "AIgeneric.h"

class AIrandom : public AIgeneric {
    public:
	AIrandom();
	virtual int getNextMove(int*, const int &);
	virtual int pawnPromotion(int*, const int &);
};



#endif
