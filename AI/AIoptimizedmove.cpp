#include <climits>
#include <iostream>
#include "AIoptimizedmove.h"

AIoptimizedmove::AIoptimizedmove() {
    for (int l = 0; l < 125; l++) 
	for (int p = 0; p < 8; p++) 
	    setPossibleMoves(p, l);
}

void AIoptimizedmove::setPossibleMoves(const int & piece, const int & loc) {
    for (int i=0; i<26; i++) table[loc][piece][i] = new List;
    switch ( piece ) {
	case 0:
	    return;
	case 1:
	    setPawnMoves(loc);
	    return;
	case 2:
	    setRookMoves(loc);
	    return;
	case 3:
	    setKnightMoves(loc);
	    return;
	case 4:
	    setBishopMoves(loc);
	    return;
	case 5:
	    setUnicornMoves(loc);
	    return;
	case 6:
	    setQueenMoves(loc);
	    return;
	case 7:
	    setKingMoves(loc);
	    return;
    }
}

void AIoptimizedmove::setPawnMoves(const int & loc) {
    /* table[loc][1][0] = black pawn moves
     *		    [1] = white pawn moves
     *		    [2] = black capture locs
     *		    [3] = white capture locs
     */

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
    for (int sign=-1; sign<2; sign+=2) {
	for (int i=0; i<2; i++) {
	    int l = locAdd(loc, sign*movelist[i][0], sign*movelist[i][1], movelist[i][2]);
	    if (l!=-1) table[loc][1][(sign+1)/2]->insert(l);
	}
    }
    for (int sign=-1; sign<2;sign+=2) {
	for (int i=0; i<5; i++) {
	    int l = locAdd(loc, sign*takelist[i][0], sign*takelist[i][1], takelist[i][2]);
	    if (l!=-1) table[loc][1][(sign+1)/2+2]->insert(l);
	}
    }
}

void AIoptimizedmove::setRookMoves(const int & loc) {
    for (int s=-1; s<2; s+=2)
	for (int i=0; i<3; i++) {
	    int b = i==0?1:0;
	    int y = i==1?1:0;
	    int x = i==2?1:0;
	    int l = loc;
	    while (true) {
		l = locAdd(l, s*b, s*x, s*y);
		if (l==-1) break; //if the piece is invalid space
		table[loc][2][i*2 + (s+1)/2]->insert(l);
	    }
	}
}

void AIoptimizedmove::setKnightMoves(const int & loc) {
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
	    if (l!=-1) //if the piece isn't same color or invalid space
		table[loc][3][0]->insert(l);
	}
    }
}

void AIoptimizedmove::setBishopMoves(const int & loc) {
    static int movelist[][3] = {
	{1, 1, 0},
	{1, -1, 0},
	{1, 0, 1},
	{1, 0, -1},
	{0, 1, 1},
	{0, 1, -1}
    };
    for (int s=-1; s<2; s+=2)
	for (int i=0; i<6; i++) {
	    int b = s*movelist[i][0];
	    int y = s*movelist[i][1];
	    int x = s*movelist[i][2];
	    int l = loc;
	    while (true) {
		l = locAdd(l, b, x, y);
		if (l==-1) break; //if the piece is invalid space
		table[loc][4][i*2+(s+1)/2]->insert(l);
	    }
	}
}


void AIoptimizedmove::setUnicornMoves(const int & loc) {
    static int movelist[][3] = {
	{1, 1, 1},
	{1, 1, -1},
	{1, -1, 1},
	{-1, 1, 1}
    };
    for (int s=-1; s<2; s+=2)
	for (int i=0; i<4; i++) {
	    int b = s*movelist[i][0];
	    int y = s*movelist[i][1];
	    int x = s*movelist[i][2];
	    int l = loc;
	    while (true) {
		l = locAdd(l, b, x, y);
		if (l==-1) break; //if the piece is invalid space
		table[loc][5][i*2+(s+1)/2]->insert(l);
	    }
	}
}


void AIoptimizedmove::setQueenMoves(const int & loc) {
    int ind = 0;
    for (int b=-1; b<=1; b++)
	for (int x=-1; x<=1; x++) {
	    for (int y=-1; y<=1; y++) {
		if (b==0 && x==0 && y==0) continue;
		int l = loc;
		while (true) {
		    l = locAdd(l, b, x, y);
		    if (l==-1) break; //if the piece is invalid space
		    table[loc][6][ind]->insert(l);
		}
		ind++;
	    }
	}
}

void AIoptimizedmove::setKingMoves(const int & loc) {
    for (int b=-1; b<=1; b++) {
	for (int x=-1; x<=1; x++) {
	    for (int y=-1; y<=1; y++) {
		if (b==0 && x==0 && y==0) continue;
		int l = locAdd(loc, b, x, y);
		if (l!=-1) table[loc][7][0]->insert(l);
	    }
	}
    }
}

int AIoptimizedmove::getPossibleMoves(int* arr, const int* board, const int & loc) {
    // Returns the number of moves possible;
    int pos = board[loc] & 7;
    if (loc==-1) pos = 0;
    int looks = 0;
    int ind = 0;
    int c = board[loc] < 8 ? 1 : 0; // c = 1 if white else 0
    switch ( pos ) {
	case 0:
	    return 0;
	case 1:
	    {
		// Pawn
		/* table[loc][1][0] = black pawn moves
		 *		    [1] = white pawn moves
		 *		    [2] = black capture locs
		 *		    [3] = white capture locs
		 */
		List * l = table[loc][1][c];
		while (l->value != -1) {
		    if (board[l->value] == 0) arr[ind++] = l->value;
		    l=l->next;
		}
		l = table[loc][1][c+2];
		while (l->value != -1) {
		    if ((board[l->value]!=0) && ((c ^ (board[l->value] < 8)))) arr[ind++] = l->value;
		    l=l->next;
		}
		return ind;
	    }
	case 2:
	    {
		// Rook
		looks = 6;
		break;
	    }
	case 3:
	    {
		// Knight
		List * l = table[loc][3][0];
		while (l->value != -1) {
		    if ((board[l->value]==0) || (c ^ (board[l->value] < 8))) arr[ind++] = l->value;
		    l=l->next;
		}
		return ind;
	    }
	case 4:
	    {
		//Bishop
		looks = 12;
		break;
	    }
	case 5:
	    {
		// Unicorn
		looks = 8;
		break;
	    }
	case 6:
	    {
		// Queen
		looks = 26;
		break;
	    }
	case 7:
	    {
		// King
		List * l = table[loc][7][0];
		while (l->value != -1) {
		    if ((board[l->value]==0) || (c ^ (board[l->value] < 8))) arr[ind++] = l->value;
		    l=l->next;
		}
		return ind;
	    }
    }
    for (int i=0; i<looks; i++) {
	List * l = table[loc][pos][i];
	while (l->value != -1) {
	    if ((board[l->value]!=0) && (c ^ (board[l->value] > 8))) break;
	    else arr[ind++] = l->value;
	    if ((board[l->value]!=0) && (c ^ (board[l->value] < 8))) break;
	    l=l->next;
	}
    }
    return ind;
}

void List::printlist() {
    if (next == NULL) cout << value << endl;
    else {
	cout << value << " ";
	next->printlist();
    }
}
