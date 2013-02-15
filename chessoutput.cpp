#include <iostream>
#include <string>
#include <algorithm>
#include <cstdio>
#include "chessoutput.h"

using namespace std;

void printBoard(int* board, int location, set<int> possibles) {
    string background = "\e[0;43m"; //yellow
    string black = "\e[1;30m";
    string white = "\e[1;37m";
    string selectcolor = "\e[0;44m"; // blue
    string possiblecolor = "\e[0;46m"; // cyan
    string normal = "\e[0m";
//    4 RNKNR   4 UBQUB   4 *****   4 *****   4 *****   
//    3 PPPPP   3 PPPPP   3 *****   3 *****   3 *****   
//    2 *****   2 *****   2 *****   2 *****   2 *****   
//    1 *****   1 *****   1 *****   1 PPPPP   1 PPPPP   
//    0 *****   0 *****   0 *****   0 BUQBU   0 RNKNR   
//      abcde     abcde     abcde     abcde     abcde
//	  E         D         C         B         A  

//  01234 is the y coordinate, abcde is the x coordinate, ABCDE is the b coordinate
//  print by x, then b, then y.

    for (int y=4; y>=0; y--) {
	cout << "   ";
	for (int b=4; b>=0; b--) {
	    cout << y;
	    for (int x=0; x<5; x++) {
		int loc = board[ind(b,y,x)];
		cout << background;
		if (possibles.find(ind(b,y,x)) != possibles.end()) cout << possiblecolor;
		else if (b == location / 25 && y == (location/5)%5 && x == location%5) cout << selectcolor;
		if (loc > 8) {
		    cout << black; loc-=8;
		}
		else cout << white;
		switch ( loc ) {
		    case 0:
			cout << '*'; break;
		    case 1:
			cout << 'P'; break;
		    case 2:
			cout << 'R'; break;
		    case 3:
			cout << 'N'; break;
		    case 4:
			cout << 'B'; break;
		    case 5:
			cout << 'U'; break;
		    case 6:
			cout << 'Q'; break;
		    case 7:
			cout << 'K'; break;
		    default:
			cout << ' '; break;
		}
		cout << normal;
	    }
	    cout << "   ";
	}
	cout << endl;
    }
    for (int i=0; i<5; i++) cout << "    abcde";
    cout << endl;
    for (int i=0; i<5; i++) cout << "      " << (char) (69-i) << "  ";
    cout << endl;
}

