#ifndef CHESSAI_H
#define CHESSAI_H
#include <iostream>
#include <string>
#include "AIgeneric.h"

using namespace std;
class chessAI {
    public:
	chessAI();
	~chessAI();
	void setAI();
	int getNextMove(int*, const int &);
    private:
	AIgeneric ** AIlist;
	string *names;
	int length;
	int selectedAI;
};

#endif
