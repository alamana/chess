#include <iostream>
#include <stdlib.h>
#include "chessAI.h"
#include "AIrandom.h"
#include "AIgreedy.h"
#include "AIabpruning.h"
#include "AIoptimized.h"
#include "AInegascout.h"

chessAI::chessAI () {
    // SET AIs HERE
    // Random AI
    AIrandom * randomAI = new AIrandom;
    AIlist.push_back(randomAI);
    names.push_back(randomAI->name);

    AIgreedy * greedyAI = new AIgreedy;
    AIlist.push_back(greedyAI);
    names.push_back(greedyAI->name);

    AIabpruning * abAI = new AIabpruning;
    AIlist.push_back(abAI);
    names.push_back(abAI->name);

    AIoptimized * opAI = new AIoptimized;
    AIlist.push_back(opAI);
    names.push_back(opAI->name);

    AInegascout * nsAI = new AInegascout;
    AIlist.push_back(nsAI);
    names.push_back(nsAI->name);

    // FIN
    selectedAI = -1;
}

chessAI::~chessAI() {
    for (int i=AIlist.size()-1; i>=0; i--) delete AIlist[i];
}

void chessAI::setAI() {
    int x = -1;
    string temp;
    int length = AIlist.size();
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

vector<string> chessAI::getAIList()
{
	return names;
}

void chessAI::setAI(int n)
{
	selectedAI = n;
}

int chessAI::getNextMove(int * board, const int & color) {
    return AIlist[selectedAI]->getNextMove(board, color);
}

int chessAI::pawnPromotion(int *board, const int & color) {
    return AIlist[selectedAI]->pawnPromotion(board, color);
}
