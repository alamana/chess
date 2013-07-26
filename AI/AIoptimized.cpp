#include <float.h>
#include <iostream>
#include "AIoptimized.h"
#include "chessmove.h"
#include "../chessoutput.h"

#define SEARCH_DEPTH 5

using namespace std;

AIoptimized::AIoptimized() {
    name = "Optimized AI";
    val = 0;
    //	          P   R   B   N   U   Q   K
    int v[] = {0, 10, 50, 30, 50, 40, 80, 1000};
    for (int i=0; i<8; i++) valuelist[i] = v[i];
    mover = new AIoptimizedmove;
}

AIoptimized::~AIoptimized() {
    delete mover;
}

double AIoptimized::computeValue(const int * board, int color){
    int total = 0;
    int upper = 15, lower = 9;
    if (color == 1) { upper = 7, lower = 1;}
    for (int i=0; i<125; i++){
	if (board[i] >= lower && board[i] <= upper) total += valuelist[board[i]&7];
	else total -= valuelist[board[i]&7];
    }
    return total;
}

int AIoptimized::getNextMove(const int * inboard, const int & color){
    int from[200], to[200];
    int len = 0;
    int upper = 15, lower = 9;
    int posmoves[125];
    int pmovelen;
    if (color == 1) { upper = 7; lower = 1;}
    for (int i=0; i<125; i++)
	if (inboard[i] >= lower && inboard[i] <= upper) {
	    pmovelen = mover->getPossibleMoves(posmoves, inboard, i);
	    for (int k=0; k<pmovelen; k++) {
		from[len] = i;
		to[len++] = posmoves[k];
	    }
	}
    //for (int i=0;i <len; i++) cout << from[i] << ' ' << to[i] << endl;
    for (int k=0; k<125; k++) board[k] = inboard[k];
    val = computeValue(board, 1);
    //cout << val << endl;
    double maxvalue = -DBL_MAX;
    int maxind = 0, save = 0, sign = 1;
    for (int i=0; i<len; i++) {
	save = board[to[i]];
	sign = save > 8 ? -1 : 1;
	val += sign*valuelist[save&7];
	board[to[i]] = board[from[i]];
	board[from[i]] = 0;
	depth = SEARCH_DEPTH;
	double curvalue = -negamax(-DBL_MAX, DBL_MAX, color^1^9);
	//cout << endl<<endl;
	if (curvalue > maxvalue) {
	    maxvalue = curvalue;
	    maxind = i;
	}
	board[from[i]] = board[to[i]];
	board[to[i]] = save;
	val -= sign*valuelist[save&7];
    }
    //cout << to[maxind] << ' ' << from[maxind] << ' ' << maxvalue << endl;
    return 1000*to[maxind]+from[maxind];
}

double AIoptimized::negamax(double alpha, double beta, int color) {
    if (depth == 0) {
	return (color==1) ? -val : val;
    }
    int from[200], to[200];
    int len = 0;
    int upper = 15, lower = 9;
    int posmoves[125];
    int pmovelen;
    if (color == 1) { upper = 7; lower = 1;}
    for (int i=0; i<125; i++)
	if (board[i] >= lower && board[i] <= upper) {
	    pmovelen = mover->getPossibleMoves(posmoves, board, i);
	    for (int k=0; k<pmovelen; k++) {
		from[len] = i;
		to[len++] = posmoves[k];
	    }
	}
    int pawnUpper = 124, pawnLower = 120, inc = 8, pawnval = 9;
    if (color == 1) { pawnUpper = 4; pawnLower = 0; inc = 0; pawnval = 1; }
    int save = 0, sign = color == 1 ? -1 : 1;
    for (int i=0; i<len; i++) {
	// check to see if the move is a pawn promotion
	if ((board[from[i]] == pawnval) && (pawnLower <= to[i]) && (to[i] <= pawnUpper)) {
	    // make the piece a bishop for now
	    board[from[i]] = 4 + inc;
	}
	save = board[to[i]];
	val += sign*valuelist[save&7];
	board[to[i]] = board[from[i]];
	board[from[i]] = 0;
	depth--;
	double value = -negamax(-beta, -alpha, color^1^9);
	depth++;
	board[from[i]] = board[to[i]];
	board[to[i]] = save;
	val -= sign*valuelist[save&7];
	if (value >= beta) return value;
	if (value >= alpha) alpha = value;
    }
    return alpha;
}

int AIoptimized::pawnPromotion(const int*, const int &) { return 4; }
