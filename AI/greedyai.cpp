#include "greedyai.h"
#include "chessmove.h"

greedyai::greedyai(){
	color = false; // default to black
	best[0] = 0;
	best[1] = 0;	
}

void greedyai::setBoard(int* board){
	this->board = board;
}

double greedyai::computeValue(int loc){
	int piece = board[loc] % 8;
	int pieceVal = 0;
	switch (piece){
		case 1:
			pieceVal = 1;
			break;
		case 2:
			pieceVal = 5;
			break;
		case 3: 
			pieceVal = 3;
			break;
		case 4: 
			pieceVal = 4;
			break;
		case 5: 
			pieceVal = 6;
			break;
		case 6:
			pieceVal = 10;
			break;
		case 7:
			pieceVal = 8;	
			break;
		default:
			break;	
	}
	return pieceVal;
}

void greedyai::setMove(){
	int upper = 15;
	int lower = 9;
	int deltaVal = 0;
	if (color){ upper = 7; lower = 1;}
	for (int j = 0; j < 125; j++){
		if (board[j] >= lower && board[j] <= upper){
			int val = computeValue(j);
			set<int> posmoves = getPossibleMoves(board, j);
			for (set<int>::iterator i = posmoves.begin(); i != posmoves.end(); i++){
				int elem = *i;
				int elemVal = computeValue(elem);
				if ( (elemVal - val) >= deltaVal ){
					deltaVal = elemVal - val;
					best[0] = j;
					best[1] = elem;
				}
			}
		}
	}
}
