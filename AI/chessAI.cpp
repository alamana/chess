#include <iostream>
#include <stdlib.h>
#include "chessAI.h"
#include "AIrandom.h"


chessAI::chessAI () {
    length = 1; // Remember to change this!
    AIlist = new AIgeneric * [length];
    names = new string[length];
    
    // SET AIs HERE
    // Random AI
    AIrandom randomAI;
    AIlist[0] = & (randomAI);
    names[0] = "Random AI";

    // FIN
    selectedAI = -1;
}

chessAI::~chessAI() {
    for (int i=0; i<length; i++) delete AIlist[i];
}

void chessAI::setAI() {
    int x = -1;
    string temp;
    while (x < 1 || x > length) {
	cout << "AI list:" << endl;
	for (int i=0; i<length; i++)
	    cout << i+1 << ".\t"<<names[i]<<endl;
	cout << "Select an AI: ";
	cin >> temp;
	x=atoi(temp.c_str());
	cout << "\n\n\n";
    }
    selectedAI = x-1;
}

int chessAI::getNextMove(int * board, const int & color) {
    0;
    return AIlist[selectedAI]->getNextMove(board, color);
}
