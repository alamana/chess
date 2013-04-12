#include <float.h>
#include <iostream>
#include "AIoptimized.h"
#include "chessmove.h"
#include "../chessoutput.h"

#define SEARCH_DEPTH 4

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
    for (int i=0; i<125; i++)
	if (board[i] >= lower && board[i] <= upper) total += valuelist[board[i]&7];
	else total -= valuelist[board[i]&7];
    return total;
}

int AIoptimized::getNextMove(const int *board, const int & color){
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
    //for (int i=0;i <len; i++) cout << from[i] << ' ' << to[i] << endl;
    int newboard[125];
    for (int k=0; k<125; k++) newboard[k] = board[k];
    val = computeValue(newboard, 1);
    //cout << val << endl;
    double maxvalue = -DBL_MAX;
    int maxind = 0, save = 0, sign = 1;
    for (int i=0; i<len; i++) {
	save = newboard[to[i]];
	sign = save > 8 ? -1 : 1;
	val += sign*valuelist[save&7];
	newboard[to[i]] = newboard[from[i]];
	newboard[from[i]] = 0;
	indextest = 0;
	double curvalue = -negamax(newboard, SEARCH_DEPTH, -DBL_MAX, DBL_MAX, color^1^9);
	//cout << endl<<endl;
	if (curvalue > maxvalue) {
	    maxvalue = curvalue;
	    maxind = i;
	}
	newboard[from[i]] = newboard[to[i]];
	newboard[to[i]] = save;
	val -= sign*valuelist[save&7];
    }
    //cout << to[maxind] << ' ' << from[maxind] << ' ' << maxvalue << endl;
    return 1000*to[maxind]+from[maxind];
}

double AIoptimized::negamax(int * board, int depth, double alpha, double beta, int color) {
    //if (depth > 4) {
    //cout << depth << '\n';
    //printBoard(board, -1);
    //}
    if (depth == 0) {
	//return computeValue(board,color);
	int compute = computeValue(board, color);
	if (compute != ( (color==1) ? val : -val ) ) cout << compute << ' ' << ((color==1)?val:-val) << endl;
	return (color==1) ? val : -val;
    }
    int from[200], to[200];
    int len = 0;
    int upper = 15, lower = 9;
    int posmoves[125];
    int pmovelen;
    if (color == 1) { upper = 7; lower = 1;}
    //cout << "\n\n\n\n\n" << color << "\n"; 
    for (int i=0; i<125; i++)
	if (board[i] >= lower && board[i] <= upper) {
	    pmovelen = mover->getPossibleMoves(posmoves, board, i);
	    //if (depth == 8) {
		//cout << "(" << pmovelen <<") \n";
		//printBoard(board, i);
	    //}
	    for (int k=0; k<pmovelen; k++) {
		from[len] = i;
		to[len++] = posmoves[k];
	    }
	}
    

    int save = 0, sign = color == 9 ? -1 : 1;
    for (int i=0; i<len; i++) {
	save = board[to[i]];
	val += sign*valuelist[save&7];
	board[to[i]] = board[from[i]];
	board[from[i]] = 0;
	//printBoard(board, to[i]);
	//cout << color << ' ' << val << endl;
	double value = -negamax(board, depth-1, -beta, -alpha, color^1^9);
	//cout << value << ' ' << alpha << ' ' << beta << ' ' << depth << endl;
	board[from[i]] = board[to[i]];
	board[to[i]] = save;
	val -= sign*valuelist[save&7];
	if (value >= beta) return value;
	if (value >= alpha) alpha = value;
	//printBoard(board, from[i]);
	//cout << color << ' ' << val << endl;
    }
    indextest++;
    return alpha;
}

int AIoptimized::pawnPromotion(const int*, const int &) { return 4; }

