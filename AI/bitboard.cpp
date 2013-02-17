#include "bitboard.h"

int BOARD_SIZE = 125;

bitboard::bitboard(){
	boardarray[BOARD_SIZE];
	size = 0;
	for (int i = 0; i < BOARD_SIZE; i++){
		boardarray[i] = false;
	}
}

bitboard bitboard::U(bitboard* board){
	bitboard ret;
	for (int i = 0; i < BOARD_SIZE; i++){
		if (boardarray[i] == true || 
				board->boardarray[i] == true){
			ret.boardarray[i] = true;
			ret.size++;
		}
	}
	return ret;
}

bitboard bitboard::I(bitboard* board){
	bitboard ret;
	for (int i = 0; i < BOARD_SIZE; i++){
		if (boardarray[i] == board->boardarray[i] && boardarray[i] == true){
			ret.boardarray[i] = true;
			ret.size++;
		}
	}
	return ret;
}

void bitboard::flip(int index){
	boardarray[index] = !boardarray[index];
	if (boardarray[index]) size++;
	else size--;
}

void bitboard::set(int index, bool val){
	if (boardarray[index] != val){
		if (val) size++;
		else size--;
		boardarray[index] = val;
	}
}

bool bitboard::eq(bitboard *board){
	bool ret = true;
	int i = 0;
	while (ret && i < BOARD_SIZE){
		if (boardarray[i] != board->boardarray[i]) ret = false;
		else i++;
	}
	return ret;
}

bool bitboard::empty(){
	bool ret = false;
	if (size == 0) ret = true;
	return ret;
}

int bitboard::getBool(int index){
	return boardarray[index];
}

