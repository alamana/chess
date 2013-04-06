#include <iostream>
#include <string>
#include <stdio.h>
#include <iterator>
#include "chessoutput.h"
#include "AI/chessmove.h"
#include "AI/chessAI.h"

using namespace std;

int parseInput(string);
void moveto(int*, int, int);
bool checkConditions(int*, chessAI *, bool);

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

    // Sets AI
    chessAI wAI;
    chessAI bAI;

    char humanity = 0;
    while (humanity != 'y' && humanity != 'n') {
	cout << "Is white a human player? (y/n): ";
	cin >> humanity;
    }
    whuman = (humanity=='y') ? true : false;
    if (!whuman) {
	cout << "White isn't human!" << endl;
	wAI.setAI();
    }

    humanity = 0;
    while (humanity != 'y' && humanity != 'n') {
	cout << "Is black a human player? (y/n): ";
	cin >> humanity;
    }
    bhuman = (humanity=='y') ? true : false;
    if (!bhuman) {
	cout << "White isn't human!" << endl;
	bAI.setAI();
    }

    //Gameloop
    while (true) {
	set<int> posmoves = getPossibleMoves(board, loc, true); // enable checking
	printBoard(board, loc,posmoves);
	if ((color==1 && whuman) || (color==9 && bhuman)) {
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
			moveto(board, save, loc);
			loc = -1;
			save = -1;
			//switches color between 9 and 1
			color = 9^1^color;
		    }
		    break;
	    }
	    if (checkConditions(board, NULL, false)) break;
	}
	else {
	    cout << "\t" <<(color==1?"WHITE ":"BLACK ") << "is a computer, it will move now.\n";
	    int computerderp = (color==1) ? wAI.getNextMove(board, color) : bAI.getNextMove(board,color);
	    moveto(board, computerderp%1000, computerderp/1000);
	    if (checkConditions(board, color==9?(&bAI):(&wAI), true)) break;
	    color = 9^1^color;
	}
	cout << "\n\n\n";
    }
    cout << "\n\n";
    printBoard(board, -1, getPossibleMoves(board, -1, true));
    
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

// -1 = invalid move, still in check after move
//  0 = valid move, no check resulting from it
//  1 = valid move, oppenent is in check from it


void moveto(int* board, int from, int to) {
   	board[to] = board[from];
	board[from] = 0;

	// see if a king was moved
	if (from == bkloc) bkloc = to;
	if (from == wkloc) wkloc = to;
}

bool checkConditions(int *board, chessAI *AI, const bool nothuman) {
    //Promote pawn
    for (int i=0; i<5; i++)
	if (board[i] == 9) {
	    int piece=0;
	    if (nothuman) piece = AI->pawnPromotion(board, 9);
	    else while (piece < 1 || piece > 4) {
		cout << "\n\nBlack promotion! What would you like your pawn to become?" << endl;
		cout << "\t1. Rook\n\t2. Knight\n\t3. Bishop\n\t 4. Unicorn\n";
		cin >> piece;
	    }
	    board[i] = piece+1+8;
	}
    for (int i=120; i<125; i++)
	if (board[i] == 1) {
	    int piece=0;
	    if (nothuman) piece = AI->pawnPromotion(board, 1);
	    else while (piece < 1 || piece > 4) {
		cout << "\n\nWhite promotion! What would you like your pawn to become?" << endl;
		cout << "\t1. Rook\n\t2. Knight\n\t3. Bishop\n\t 4. Unicorn\n";
		cin >> piece;
	    }
	    board[i] = piece+1;
	}


    bool wking = false;
    bool bking = false;
    for (int i=0; i<125; i++) {
	if (board[i] == 7) wking = true;
	if (board[i] == 15) bking = true;
    }

    if (!(wking&&bking)) {
	cout << (wking?"White":"Black") << " wins!" << endl;
	return true;
    }
    return false;
}
