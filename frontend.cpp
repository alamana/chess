#include <iostream>
#include <string>
#include <stdio.h>
#include <iterator>
#include "chessoutput.h"
#include "chessmove.h"
#include "bitboard.h"

using namespace std;

int parseInput(string);
void moveto(int*, int, int, int);

bool inCheck = false;

int main() {
    // Standard starting board.
    // 1 = Pawn		5 = Unicorn
    // 2 = Rook		6 = King
    // 3 = Knight	7 = Queen
    // 4 = Bishop	0 = Empty
    // #+8 = Black pieces.
    int board[] = {
	2, 3, 7, 3, 2,
	1, 1, 1, 1, 1,
	0, 0, 0, 0, 0,
	0, 0, 0, 0, 0,
	0, 0, 0, 0, 0,

	4, 5, 6, 4, 5,
	1, 1, 1, 1, 1,
	0, 0, 0, 0, 0,
	0, 0, 0, 0, 0,
	0, 0, 0, 0, 0,

	0, 0, 0, 0, 0,
	0, 0, 0, 0, 0,
	0, 0, 0, 0, 0,
	0, 0, 0, 0, 0,
	0, 0, 0, 0, 0,

	0, 0, 0, 0, 0,
	0, 0, 0, 0, 0,
	0, 0, 0, 0, 0,
	9, 9, 9, 9, 9,
	13,12,14,13,12,

	0, 0, 0, 0, 0,
	0, 0, 0, 0, 0,
	0, 0, 0, 0, 0,
	9, 9, 9, 9, 9,
	10,11,15,11,10,
    };

    string input;
    string statetext[] = {
	"Enter the location of the piece to move",
	"Enter a location to move to",
	"Invalid location, try again",
    };
    int loc   = -1;
    int state =  0;
    int save  = -1;
    int color = 1; // 1 is white, 9 is black, to exploit the way
		   // the opponents function works
    bool error = false;
    bool whuman = true;
    bool bhuman = true;

    while (true) {
	set<int> posmoves = getPossibleMoves(board, loc);
	printBoard(board, loc,posmoves); 
	cout << "\t" <<(color==1?"WHITE: ":"BLACK: ") << statetext[error?2:state] << ": ";
	cin >> input;
	loc = parseInput(input);
	error = false;
	switch (state) {
	    case 0:
		if (loc == -1 || opponents(color, board[loc]) != 0) {
		    error = true;
		}
		else {
		    state = 1;
		    save = loc;
		}
		break;
	    case 1:
		if (loc == -1) {
		    error = true;
		    loc = save;
		}
		else if (opponents(color, board[loc]) == 0) {
		    state = 1;
		    save = loc;
		}
		else if (posmoves.find(loc) == posmoves.end()) {
		    error = true;
		    state = 0;
		    loc = save;
		}
		else {
		    state = 0;
		    moveto(board, save, loc, color);
		    loc = -1;
		    save = -1;
		    //switches color between 9 and 1
		    color = 9^1^color;
		}
		break;
	}
	cout << "\n\n\n";
    }
    
    return 0;
}

int parseInput (string input) {
    // Tests every possible combination of letters and checks for validity
    if (input.size() < 3) return -1;
    int b = input[0]-65;
    int y = input[1]-48; //012
    int x = input[2]-97;
    int n = locAdd(0, b, y, x);
    if (n != -1) return n;
    b = input[2]-65;
    y = input[0]-48; //201
    x = input[1]-97;
    n = locAdd(0, b, y, x);
    if (n != -1) return n;
    b = input[1]-65;
    y = input[0]-48; //102
    x = input[2]-97;
    n = locAdd(0, b, y, x);
    if (n != -1) return n;
    b = input[1]-65;
    y = input[2]-48; //120
    x = input[0]-97;
    n = locAdd(0, b, y, x);
    if (n != -1) return n;
    b = input[2]-65;
    y = input[1]-48; //210
    x = input[0]-97;
    n = locAdd(0, b, y, x);
    if (n != -1) return n;
    b = input[0]-65;
    y = input[2]-48; //021
    x = input[1]-97;
    n = locAdd(0, b, y, x);
    return n;
}

// starting positions
int bkloc = 122;
int wkloc = 3;

void moveto(int* board, int from, int to, int color) {
    board[to] = board[from];
    board[from] = 0;

    // see if a king was moved
    if (from == bkloc) bkloc = to;
    if (from == wkloc) wkloc = to;
    
 
    int kingloc = bkloc;
    if (color == 1) kingloc = wkloc;
    int upper = 7;
    int lower = 1;
    if (board[to] > 8){ upper = 15; lower = 9;}
    bool inCheck = false;
    int i = 0;
    while (!inCheck && i < 125){
	    if (board[i] >= lower && board[i] <= upper){
	    	set<int> posmoves = getPossibleMoves(board, i);
		if (!posmoves.empty()){
			for (set<int>::iterator i = posmoves.begin(); i != posmoves.end(); i++){
				int elem = *i;
				if (elem == kingloc) inCheck = true;				
			}	
		}
	    }
	    i++;
    }
}
