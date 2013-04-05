#include <float.h>
#include <iostream>
#include "AInegascout.h"
#include "chessmove.h"

#define SEARCH_DEPTH 3

AInegascout::AInegascout() {
    name = "Negascout AI";
}

double AInegascout::computeValue(const int * board, int color){
    //			               P   R   B   N   U   Q   K
    static int const valuelist[] = {0, 10, 50, 30, 50, 70, 200, 1000};
    int total = 0;
    int upper = 15, lower = 9;
    if (color == 1) { upper = 7, lower = 1;}
    for (int i=0; i<125; i++)
	if (board[i] >= lower && board[i] <= upper) total += valuelist[board[i]&7];
	else total -= valuelist[board[i]&7];
    return total;
}

int AInegascout::getNextMove(const int *board, const int & color){
    int from[200], to[200];
    int len = 0;
    int upper = 15, lower = 9;
    if (color == 1) { upper = 7; lower = 1;}
    for (int i=0; i<125; i++)
	if (board[i] >= lower && board[i] <= upper) {
	    set<int> posmoves = getPossibleMoves(board, i);
	    for (set<int>::iterator itr = posmoves.begin(); itr != posmoves.end(); itr++) {
		if (*itr == -1) continue;
		from[len] = i;
		to[len++] = *itr;
	    }
	}
    //for (int i=0;i <len; i++) cout << from[i] << ' ' << to[i] << endl;
    double maxvalue = -DBL_MAX;
    int maxind = 0;
    for (int i=0; i<len; i++) {
	int newboard[125];
	for (int k=0; k<125; k++) newboard[k] = board[k];
	newboard[to[i]] = newboard[from[i]];
	newboard[from[i]] = 0;
	double curvalue = -negascout(newboard, SEARCH_DEPTH, -DBL_MAX, DBL_MAX, 1, color^1^9);
	if (curvalue > maxvalue) {
	    maxvalue = curvalue;
	    maxind = i;
	}
    }
    //cout << to[maxind] << ' ' << from[maxind] << ' ' << maxind << endl;
    return 1000*to[maxind]+from[maxind];
}

int AInegascout::pawnPromotion(const int*, const int &) { return 4; }

double AInegascout::negascout(int * board, int depth, double alpha, double beta, int player, int color) {
	if (depth == 0) return computeValue(board, color);
	int from[200], to[200];
	int len = 0;
	int upper = 15, lower = 9;
	if (color == 1) { upper = 7; lower = 1; }
	for (int i = 0; i < 125; i++){
		if (board[i] >= lower && board[i] <= upper) {
			set<int> posmoves = getPossibleMoves(board, i);
			for (set<int>::iterator itr = posmoves.begin(); itr != posmoves.end(); itr++) {
					if (*itr == -1) continue;
					from[len] = i;
					to[len++] = *itr;
			}
		}
	}
	double b = beta;
	double a = alpha;
	double t;
	for (int i = 0; i < len; i++){
		int newboard[125];
		for (int k = 0; k < 125; k++) newboard[k] = board[k];
		newboard[to[i]] = newboard[from[i]];
		newboard[from[i]] = 0;
		t = -negascout(newboard, depth - 1, -b, -alpha, -player, color^1^9);
		if ( (t > a) && (t < beta) )
			t = -negascout(newboard, depth-1, -beta, -alpha, -player, color^1^9);
		alpha = (alpha > t) ? alpha : t;
		if (alpha >= beta) return alpha;
		b = alpha + 1;
	}
	return alpha;
}
