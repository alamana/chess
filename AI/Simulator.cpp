#include "Simulator.h"
#include "chessmove.h"
#include <iostream>

Simulator::Simulator(bool checkingEnabled){
	enabled = checkingEnabled;
}

void Simulator::setBoard(const int* array){
	checkState = false;
	if (enabled){
	wkingloc = -1;
	bkingloc = -1;
	color = 2;
	for (int i = 0; i < 125; i++){
		board[i] = array[i];
		if (board[i] == 7) wkingloc = i;
		else if (board[i] == 15) bkingloc = i;
	}
	}
}

void Simulator::simulateMove(int to, int from){
	//cout << "simulating move..." << endl;
	//cout << "the piece we are moving is a " << board[from] << endl;
	//cout << "color =" << color;
	//cout << " enabled = " << enabled << endl;
	//cout << "to = " << to << " from = " << from << endl;
	//cout << "the white king is at " << wkingloc << " and the black king is at " << bkingloc << endl;

	if (enabled){
	int _to = board[to];
	int _from = board[from];

	// set color
	if (_from < 8) color = 1;
	else color = 9;

	// make move
	board[to] = _from;
	board[from] = 0;
	
	// did we move the king?
	if (_from == 2) wkingloc = to;
	else if (_from == 122) bkingloc = to;

	int upper, lower, kingloc;

	// if it's white's move, check to see if any of the black pieces put the white king in check
	if (color == 1) { 
		upper = 15;
		lower = 9;
		kingloc = wkingloc;
	} else {
		upper = 7;
		lower = 1;
		kingloc = bkingloc;
	}

	// check if the king is in check
	checkState = false;
	for (int j = 0; j < 125; j++){
		if (checkState == true) break;
		if (lower <= board[j] && board[j] <= upper){
			set<int> posmoves = getPossibleMoves(board,j, false); // disable checking to prevent infinite loop
			if (!posmoves.empty()){
				//cout << "looking at a " << board[j] << endl;
				for (set<int>::iterator i = posmoves.begin(); i != posmoves.end(); i++){
					int elem = *i;
					if (elem == kingloc) { checkState = true;
						//cout << "checking spot " << elem << endl;
						//cout << board[elem] << endl; 
						break; 

					}
				}
			} else {
				//cout << "posmoves is empty" << endl;
			}
		}
	}
	//cout << "checkState=" << checkState << endl;
	// reset board since this is a simulation
	board[from] = _from;
	board[to] = _to;
	}
}

void Simulator::makeMove(int to, int from){
	if (enabled){
	board[to] = board[from];
	board[from] = 0;
	}
}
