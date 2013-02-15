#include "bitboard.h"

int BOARD_SIZE = 25;

bitboard::bitboard(){
	boardvalue = 0x00000000;
	// 	       1  4   8
}

bitboard::bitboard(bitboard* otherboard){
	unsigned int othervalue = otherboard->boardvalue;
	boardvalue = othervalue;
}

bitboard::bitboard(unsigned int val){
	boardvalue = val;
}

bitboard bitboard::U(bitboard* board){
	unsigned int unionValue = boardvalue | (board->boardvalue);
	return bitboard(unionValue);
}	

bitboard bitboard::intersect(bitboard* board){
	unsigned int intercectionValue = (this->boardvalue) & (board->boardvalue);
	return bitboard(intercectionValue);
}

void bitboard::flip(int n){
	/* flips the nth bit, there the bitboard is represented as b_24 b_23 ... b_n ... b_2 b_1 b_0*/
	int flipboard = 1;
	flipboard << n;
	boardvalue = boardvalue ^ flipboard;
}

bool bitboard::empty(){
	bool ret = false;
	if (boardvalue == 0x00000000){
		ret = true;
	}
	return ret;
}

int bitboard::getSum(){
	int ret = 0;
	for (int i = 0; i < BOARD_SIZE; i++){
		ret += getBit(i);
	}
	return ret;
}

int bitboard::getBit(int n){
	n = n % 25;
	int ret = 0;
	int shift = 1 << n;
	int temp = boardvalue & shift;
	if (temp != 0)
		ret = 1;
	return ret;
}

