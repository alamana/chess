#include <set>
#include <stdlib.h>
#include <iostream>
#include <ctime>
#include "AIrandom.h"
#include "AIgeneric.h"

using namespace std;

AIrandom::AIrandom() {
    name = "Random AI";
}

int AIrandom::getNextMove(int* board, const int & color) {
    set<int> posmoves;
    int pieces[20];
    int n;
    while (posmoves.empty()) {
	int length = 0;
	for (int i=0; i<125; i++) {
	    if (opponents(color, board[i]) == 0)
		pieces[length++] = i;
	}
	srand(time(NULL));
	n = rand()%length;
	posmoves = getPossibleMoves(board, pieces[n]);
    }
    int e = rand()%(posmoves.size());
    set<int>::iterator itr = posmoves.begin();
    for (int i=0; i<e; i++) itr++;
    return 1000*(*itr) + pieces[n]; //1000 * MOVETO + MOVEFROM
}
	
int AIrandom::pawnPromotion(int*, const int &) {
    return rand()%4;
}
