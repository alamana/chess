#ifndef CHESSAI_H
#define CHESSAI_H
#include <iostream>
#include <string>
#include <vector>
#include "AIgeneric.h"

using namespace std;

class chessAI {
    public:
	chessAI();
	~chessAI();
	void setAI();
	int getNextMove(int*, const int &);
	int pawnPromotion(int *, const int &);
	vector<string> getAIList();
	void setAI(int);
    private:
	vector<AIgeneric*> AIlist;
	vector<string> names;
	int selectedAI;
};

#endif
