#include "AIgreedy.h"
#include "chessmove.h"

AIgreedy::AIgreedy() {
    name = "Greedy sonofabitch";
}

double AIgreedy::computeValue(const int & piece){
    static int valuelist[] = {0, 1, 5, 3, 4, 6, 10, 8};
    return valuelist[piece%8];
}

int AIgreedy::getNextMove(int *board, const int & color){
    int upper = 15;
    int lower = 9;
    int returnval = -1;
    int deltaVal = 0;
    if (color == 9){ upper = 7; lower = 1;}
    for (int j = 0; j < 125; j++){
	if (board[j] >= lower && board[j] <= upper){
	    int val = computeValue(board[j]);
	    set<int> posmoves = getPossibleMoves(board, j);
	    for (set<int>::iterator i = posmoves.begin(); i != posmoves.end(); i++){
		int elem = *i;
		int elemVal = computeValue(elem);
		if ( (elemVal - val) >= deltaVal ){
		    deltaVal = elemVal - val;
		    returnval = 1000*j + elem;
		}
	    }
	}
    }
    return returnval;
}

int AIgreedy::pawnPromotion(int*, const int &) { return 4; }
