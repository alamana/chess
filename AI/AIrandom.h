#ifndef AIRANDOM_H
#define AIRANDOM_H
#include "chessmove.h"
#include "AIgeneric.h"

class AIrandom : public AIgeneric {
    public:
	AIrandom();
	int getNextMove(int*, const int &);
};



#endif
