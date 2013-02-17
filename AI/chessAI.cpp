#include <iostream>
#include "chessAI.h"
#include "AIrandom.h"

using namespace std;

chessAI::chessAI () {
    length = 1; // Remember to change this!
    int (*templist[length])(int *, int);
    string tempnames[length];
    
    // SET AIs HERE
    // Random AI
    AIrandom randomAI;
    templist[0] = &(randomAI.getNextMove);
    tempnames[0] = "Random AI";

    // FIN
    AIlist = templist;
    names = tempnames;
    selectedAI = -1;
}

void setAI() {
    int x = -1;
    while (x <0 || x >= length) {
	cout << "Select an AI: " << endl;
	for (int i=0; i<length; i++)
	    cout << i << ".\t"<<names[i]<<endl;
	cin >> x;
	cout << "\n\n\n";
    }
    selectedAI = x;
}

int getNextMove() {
    return AIlist[selectedAI]();
}
