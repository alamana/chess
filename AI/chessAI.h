#include <iostream>
#include <string>

#ifndef CHESSAI_H
#define CHESSAI_H

class chessAI {
    public:
	chessAI();
	void setAI();
	int getNextMove();
    private:
	int (**AIlist)(int*, int);
	string *names;
	int length;
	int selectedAI;
};

#endif
