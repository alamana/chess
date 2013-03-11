#include <set>
#include <stdlib.h>
#include <iostream>
#include "AIrandom.h"
#include "AIgeneric.h"

using namespace std;

AIrandom::AIrandom() {marker = 123;}

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
	n = rand()%length;
	posmoves = getPossibleMoves(board, n);
    }
    int e = rand()%(posmoves.size());
    set<int>::iterator itr = posmoves.begin();
    for (int i=0; i<e; i++) itr++;
    return 1000*(*itr) + n; //1000 * MOVETO + MOVEFROM
}
