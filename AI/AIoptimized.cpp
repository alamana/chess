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
	// check for pawns
	if (rmax || bmax || umax || kmax) {
		if (rmax) { 
			board[from[i]] = (color == 1) ? 2 : 9;
			return 1000*to[i]+from[i]; // this will break
		} else if (bmax){
			board[from[i]] = (color == 1) ? 4 : 12;
			return 1000*to[i]+from[i];
		} else if (umax){
			board[from[i]] = (color == 1) ? 5 : 13;
			return 1000*to[i]+from[i];
		} else { // knight
			board[from[i]] = (color == 1) ? 3 : 11;
			return 1000*to[i]+from[i];
		}
	} else {
		//cout << endl<<endl;
		if (curvalue > maxvalue) {
	    		maxvalue = curvalue;
	    		maxind = i;
		}
		board[from[i]] = board[to[i]];
		board[to[i]] = save;
		val -= sign*valuelist[save&7];
		//cout << to[maxind] << ' ' << from[maxind] << ' ' << maxvalue << endl;
		return 1000*to[maxind]+from[maxind];
	}
}

bool rmax, bmax, umax, kmax;

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
    

    int save = 0, sign = color == 1 ? -1 : 1;
    for (int i=0; i<len; i++) {
	save = board[to[i]];
	// pawn check
	if (board[from[i]]&7 == 1){
		int high = (color == 1) ? 4 : 124;
		int low = (color == 1) ? 0 : 120;
		if (low <= to[i] && t[i] <= high){
			int rook = (color == 1) ? 2 : 10;
			int bishop = (color == 1) ? 4 : 12;
			int unicorn = (color == 1) ? 5 : 13;
			int knight = (color == 1) ? 3 : 11;
			
			// go through each of the options 
			board[from[i]] = 0;
			
			// save depth
			int depthSave = depth;
			
			// rook
			board[to[i]] = rook
			val += sign*valuelist[rook&7];
			depth = 2;
			double rookVal = -negamax(-beta, -alpha, color^1^9);
			val -= sign*valuelist[rook&7];
			
			// bishop
			board[to[i]] = bishop; // just have to change the to[i] piece now
			val += sign*valuelist[bishop&7];
			depth = 2;
			double bishopVal = -negamax(-beta, -alpha, color^1^9);
			val -= sign*valuelist[bishop&7];
			
			// unicorn
			board[to[i]] = unicorn;
			val += sign*valuelist[unicorn&7];
			depth = 2;
			double unicornVal = -negamax(-beta, -alpha, color^1^9);
			val -= sign*valuelist[unicorn&7];
			
			// knight
			board[to[i]] = knight;
			val += sign*valuelist[knight&7];
			depth = 2;
			double knightVal = -negamax(-beta, -alpha, color^1^9);
			val -= sign*valuelist[knight&7];
			
			// restore
			depth = depthSave;
			board[from[i]] = (color == 1) ? 1 : 9; // restore pawn
			board[to[i]] = save;
			
			// take the max
			umax = false;
			kmax = false;
			rmax = false;
			bmax = false;
			double max = (rookVal > bishopVal) ? rookVal : bishopVal;
			max = (knightVal > max) ? knightVal : max;
			max = (unicornVal > max) ? unicornVal : max;
			if (max == unicornVal) umax = true;
			else if (max == knightVal) kmax = true;
			else if (max == bishopVal) bmax = true;
			else rmax = true;	
		}
	} else {
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
    }
    return alpha;
}

int AIoptimized::pawnPromotion(const int*, const int &) { return 4; }

