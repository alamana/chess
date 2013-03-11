#ifndef CHESSAI_H
#define CHESSAI_H
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include "AIgeneric.h"

using namespace std;
class chessAI {
    public:
	chessAI();
	~chessAI();
	void setAI();
	int getNextMove(int*, const int &);
    private:
	vector<AIgeneric*> AIlist;
	vector<string> names;
	int selectedAI;
};

#endif
