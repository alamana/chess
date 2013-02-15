#include "bitboard.h"
#include <iostream>
using namespace std;

int main(){
	bitboard b1(0xaaaaaaaa);
	bitboard b2(0x55555555);

	bitboard b3 = b1.intersect(&b2);
	cout << "b1 = " << b1.boardvalue << endl;
	cout << "b2 = " << b2.boardvalue << endl;
	cout << "val = " << b3.boardvalue << endl;

	return 0;
}
