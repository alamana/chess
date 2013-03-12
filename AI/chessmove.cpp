#include <climits>
#include <iostream>
#include "chessmove.h"

set<int> getPossibleMoves(const int* board, const int & loc) {
    int pos = board[loc];
    if (pos > 8)  pos -= 8;
    switch ( pos ) {
	case 0:
	    return set<int>();
	case 1:
	    return getPawnMoves(board, loc);
	case 2:
	    return getRookMoves(board, loc);
	case 3:
	    return getKnightMoves(board, loc);
	case 4:
	    return getBishopMoves(board, loc);
	case 5:
	    return getUnicornMoves(board, loc);
	case 6:
	    return getQueenMoves(board, loc);
	case 7:
	    return getKingMoves(board, loc);
    }
    return set<int>();
}

set<int> getPawnMoves(const int* board, const int & loc) {
    set<int> moves;
    //cout << "**" << loc << endl;
    int sign = 1;
    int movelist[][3] = {
	{1, 0, 0},
	{0, 1, 0},
    };
    int takelist[][3] = {
	{1, 0, -1},
	{1, 0, 1 },
	{0, 1, 1 },
	{0, 1, -1},
	{1, 1, 0 }
    };
    if (board[loc] > 8) sign = -1;
    for (int i=0; i<2; i++) {
	int l = locAdd(loc, sign*movelist[i][0], sign*movelist[i][1], movelist[i][2]);
	if (l!=-1 && opponents(board[l], board[loc]) == -1) moves.insert(l);
    }
    for (int i=0; i<5; i++) {
	int l = locAdd(loc, sign*takelist[i][0], sign*takelist[i][1], takelist[i][2]);
	if (l!=-1 && opponents(board[l], board[loc]) == 1)
	    moves.insert(l);
    }
    return moves;
}

set<int> getRookMoves(const int* board, const int & loc) {
    set<int> moves;
    for (int s=-1; s<2; s+=2) {
	for (int i=0; i<3; i++) {
	    int b = i%3==0?1:0;
	    int y = i%3==1?1:0;
	    int x = i%3==2?1:0;
	    int l = loc;
	    int op;
	    do {
		l = locAdd(l, s*b, s*x, s*y);
		op = opponents(board[loc], board[l]);
		if (op == 0 || l==-1) break; //if the piece is same color or invalid space
		moves.insert(l);
	    } while(op == -1); //loop if square is empty
	}
    }
    return moves;
}

set<int> getKnightMoves(const int* board, const int & loc) {
    set<int> moves;
    int movelist[][3] = {
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
	    if (!(op == 0 || l==-1)) //if the piece isn't same color or invalid space
		moves.insert(l);
	}
    }
    return moves;
}

set<int> getBishopMoves(const int* board, const int & loc) {
    set<int> moves;
    int movelist[][3] = {
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
		moves.insert(l);
	    } while(op == -1); //loop if square is empty
	}
    }

    return moves;
}


set<int> getUnicornMoves(const int* board, const int & loc) {
    set<int> moves;
    int movelist[][3] = {
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
		moves.insert(l);
	    } while(op == -1); //loop if square is empty
	}
    }
    return moves;
}


set<int> getQueenMoves(const int* board, const int & loc) {
    set<int> r = getRookMoves(board, loc);
    set<int> b = getBishopMoves(board, loc);
    set<int> u = getUnicornMoves(board, loc);

    for (set<int>::iterator it=b.begin(); it!=b.end(); ++it) {
	r.insert(*it);
    }
    for (set<int>::iterator it=u.begin(); it!=u.end(); ++it) {
	r.insert(*it);
    }
    return r;
}

set<int> getKingMoves(const int* board, const int & loc) {
    set<int> moves;
    for (int s=-1; s<2; s+=2) {
	for (int i=0; i<3; i++) {
	    int b = i%3==0?1:0;
	    int y = i%3==1?1:0;
	    int x = i%3==2?1:0;
	    int l = locAdd(loc, s*b, s*x, s*y);
	    int op = opponents(board[loc], board[l]);
	    if (op != 0) //if opponent is not same color
		moves.insert(l);
	}
    }
    return moves;
}
