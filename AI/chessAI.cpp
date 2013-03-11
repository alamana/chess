#include <iostream>
#include <stdlib.h>
#include "chessAI.h"
#include "AIrandom.h"


chessAI::chessAI () {
    // SET AIs HERE
    // Random AI
    AIrandom * randomAI = new AIrandom;
    AIlist.push_back(randomAI);
    names.push_back("Random AI");

    // FIN
    selectedAI = -1;
}

chessAI::~chessAI() {
}

void chessAI::setAI() {
    int x = -1;
    string temp;
    while (x < 1 || x > AIlist.size()) {
	cout << "AI list:" << endl;
	for (int i=0; i<AIlist.size(); i++)
	    cout << i+1 << ".\t"<<names[i]<<endl;
	cout << "Select an AI: ";
	cin >> temp;
	x=atoi(temp.c_str());
	cout << "\n\n\n";
    }
    selectedAI = x-1;
}

int chessAI::getNextMove(int * board, const int & color) {
    return AIlist[selectedAI]->getNextMove(board, color);
}
