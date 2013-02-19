#ifndef GREEDYAI_H
#define GREEDYAI_H

#include "AI/bitboard.h"
#include <string>

class greedyai {
	public:
		greedyai();
		void setBoard(int* board);
		void setMove();		
		bool color;
		int best[2];
	private:
		double computeValue(int loc);
		int* board;
};

#endif
