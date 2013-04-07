#include <climits>
#include <iostream>
#include "chessmove.h"
#include "Simulator.h"

<<<<<<< HEAD
set<int> getPossibleMoves(const int* board, const int & loc) {
    int pos = board[loc] & 7;
=======
set<int> getPossibleMoves(const int* board, const int & loc, bool checkingEnabled) {
	Simulator sim(checkingEnabled);
	sim.setBoard(board);
    int pos = board[loc];
    if (pos > 8) { pos -= 8; }
>>>>>>> bf769b0944482f17bdc17694ea0a47f45c835bde
    switch ( pos ) {
	case 0:
	    return set<int>();
	case 1:
	    return getPawnMoves(board, loc, sim, checkingEnabled);
	case 2:
	    return getRookMoves(board, loc, sim, checkingEnabled);
	case 3:
	    return getKnightMoves(board, loc, sim, checkingEnabled);
	case 4:
	    return getBishopMoves(board, loc, sim, checkingEnabled);
	case 5:
	    return getUnicornMoves(board, loc, sim, checkingEnabled);
	case 6:
	    return getQueenMoves(board, loc, sim, checkingEnabled);
	case 7:
	    return getKingMoves(board, loc, sim, checkingEnabled);
    }
    return set<int>();
}

set<int> getPawnMoves(const int* board, const int & loc, Simulator& sim, bool enable) {
    set<int> moves;
    //cout << "**" << loc << endl;
    int sign = 1;
    static int movelist[][3] = {
	{1, 0, 0},
	{0, 1, 0},
    };
    static int takelist[][3] = {
	{1, 0, -1},
	{1, 0, 1 },
	{0, 1, 1 },
	{0, 1, -1},
	{1, 1, 0 }
    };
    if (board[loc] > 8) sign = -1;
    for (int i=0; i<2; i++) {
	int l = locAdd(loc, sign*movelist[i][0], sign*movelist[i][1], movelist[i][2]);
	if (l!=-1 && opponents(board[l], board[loc]) == -1){
		if (enable) {
			sim.simulateMove(l, loc);
			if (!sim.checkState) { moves.insert(l); }
		} else {
			moves.insert(l);
		}
	}
    }
    for (int i=0; i<5; i++) {
	int l = locAdd(loc, sign*takelist[i][0], sign*takelist[i][1], takelist[i][2]);
	if (l!=-1 && opponents(board[l], board[loc]) == 1){
		if (enable) {
			sim.simulateMove(l, loc);
			if (!sim.checkState) { moves.insert(l); }
		} else {
			moves.insert(l);
		}
	}
    }
    return moves;
}

set<int> getRookMoves(const int* board, const int & loc, Simulator& sim, bool enable) {
    set<int> moves;
    for (int s=-1; s<2; s+=2) {
	for (int i=0; i<3; i++) {
	    int b = i==0?1:0;
	    int y = i==1?1:0;
	    int x = i==2?1:0;
	    int l = loc;
	    int op;
	    do {
		l = locAdd(l, s*b, s*x, s*y);
		op = opponents(board[loc], board[l]);
		if (op == 0 || l==-1) break; //if the piece is same color or invalid space
		if (enable) {
			sim.simulateMove(l, loc);
			if (!sim.checkState) { moves.insert(l); }
		} else {
			moves.insert(l);
		}
	    } while(op == -1); //loop if square is empty
	}
    }
    return moves;
}

set<int> getKnightMoves(const int* board, const int & loc, Simulator &sim, bool enable) {
    set<int> moves;
    static int movelist[][3] = {
	{0, 1, 2},
	{0, -1, 2},
	{1, 0, 2},
	{-1, 0, 2},
	{1, 2, 0},
	{-1, 2, 0},
	{2, 1, 0},
	{-2, 1, 0},
	{0, 2, 1},
	{0, -2, 1},
	{2, 0, 1},
	{-2, 0, 1}
    };
    for (int s=-1; s<2; s+=2) {
	for (int i=0; i<12; i++) {
	    int b = s*movelist[i][0];
	    int y = s*movelist[i][1];
	    int x = s*movelist[i][2];
	    int l = locAdd(loc, b, x, y);
	    int op = opponents(board[loc], board[l]);
	    if (!(op == 0 || l==-1)) {//if the piece isn't same color or invalid space
		if (enable){
			sim.simulateMove(l, loc);
		    	if (!sim.checkState) { moves.insert(l); }
		} else {
			moves.insert(l);
		}
	    }
	}
    }
    return moves;
}

set<int> getBishopMoves(const int* board, const int & loc, Simulator& sim, bool enable) {
    set<int> moves;
    static int movelist[][3] = {
	{1, 1, 0},
	{1, -1, 0},
	{1, 0, 1},
	{1, 0, -1},
	{0, 1, 1},
	{0, 1, -1}
    };
    for (int s=-1; s<2; s+=2) {
	for (int i=0; i<6; i++) {
	    int b = s*movelist[i][0];
	    int y = s*movelist[i][1];
	    int x = s*movelist[i][2];
	    int l = loc;
	    int op;
	    do {
		l = locAdd(l, b, x, y);
		op = opponents(board[loc], board[l]);
		if (op == 0 || l==-1) break; //if the piece is same color or invalid space
		if (enable){
			sim.simulateMove(l, loc);
			if (!sim.checkState) { moves.insert(l); }
		} else {
			moves.insert(l);
		}
	    } while(op == -1); //loop if square is empty
	}
    }
    return moves;
}


set<int> getUnicornMoves(const int* board, const int & loc, Simulator &sim, bool enable) {
    set<int> moves;
    static int movelist[][3] = {
	{1, 1, 1},
	{1, 1, -1},
	{1, -1, 1},
	{-1, 1, 1}
    };
    for (int s=-1; s<2; s+=2) {
	for (int i=0; i<4; i++) {
	    int b = s*movelist[i][0];
	    int y = s*movelist[i][1];
	    int x = s*movelist[i][2];
	    int l = loc;
	    int op;
	    do {
		l = locAdd(l, b, x, y);
		op = opponents(board[loc], board[l]);
		if (op == 0 || l==-1) break; //if the piece is same color or invalid space
		if (enable) {
			sim.simulateMove(l, loc);
			if (!sim.checkState) { moves.insert(l); }
		} else { 
			moves.insert(l);
		}
	    } while(op == -1); //loop if square is empty
	}
    }
    return moves;
}


set<int> getQueenMoves(const int* board, const int & loc, Simulator& sim, bool enable) {
    set<int> r = getRookMoves(board, loc, sim, enable);
    set<int> b = getBishopMoves(board, loc, sim, enable);
    set<int> u = getUnicornMoves(board, loc, sim, enable);

    for (set<int>::iterator it=b.begin(); it!=b.end(); ++it) {
	r.insert(*it);
    }
    for (set<int>::iterator it=u.begin(); it!=u.end(); ++it) {
	r.insert(*it);
    }
    return r;
}

set<int> getKingMoves(const int* board, const int & loc, Simulator &sim, bool enable) {
    set<int> moves;
<<<<<<< HEAD
    for (int b=-1; b<=1; b++) {
	for (int x=-1; x<=1; x++) {
	    for (int y=-1; y<=1; y++) {
		int l = locAdd(loc, b, x, y);
		int op = opponents(board[loc], board[l]);
		if (op != 0) //if opponent is not same color
		    moves.insert(l);
=======
    for (int s=-1; s<2; s+=2) {
	for (int i=0; i<3; i++) {
	    int b = i%3==0?1:0;
	    int y = i%3==1?1:0;
	    int x = i%3==2?1:0;
	    int l = locAdd(loc, s*b, s*x, s*y);
	    int op = opponents(board[loc], board[l]);
	    if (op != 0) { //if opponent is not same color
		if (enable) {
			sim.simulateMove(l, loc);
			if (!sim.checkState) { moves.insert(l); }
		} else {
			moves.insert(l);
		}
>>>>>>> bf769b0944482f17bdc17694ea0a47f45c835bde
	    }
	}
    }
    return moves;
}
