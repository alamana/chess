#include "AIgreedy.h"
#include "chessmove.h"
#include <iostream>
using namespace std;


AIgreedy::AIgreedy() {
    name = "Greedy sonofabitch";
}

double AIgreedy::computeValue(const int & piece){
    //			         P   R   B   N   U   Q   K
    static int valuelist[] = {0, 1 , 5 , 3 , 4 , 6 , 8 , 100};
    return valuelist[piece%8];
}

int AIgreedy::getNextMove(const int *board, const int & color){
  cout << color << endl;
  int upper = 15;
  int lower = 9;
  int returnval = -1;
  int deltaVal = -10000;
  if (color == 1){ upper = 7; lower = 1;}
  cout << upper << " " << lower << endl;
  for (int j = 0; j < 125; j++){
    if (board[j] >= lower && board[j] <= upper){
      int val = computeValue(board[j]);
      set<int> posmoves = getPossibleMoves(board, j, true);
      for (set<int>::iterator i = posmoves.begin(); i != posmoves.end(); i++){
	int elem = *i;
	cout << "j=" << j << " elem=" << elem << endl;
	if((elem < lower || elem > upper) && elem != -1){
	    int elemVal = computeValue(board[elem]);
	    if ( (elemVal - val) >= deltaVal ){
	      deltaVal = elemVal - val;
	      returnval = 1000*elem + j;
	    }
	  }
      }
    }
  }
  cout << "returnval=" << returnval << endl;
  return returnval;
}

int AIgreedy::pawnPromotion(const int*, const int &) { return 4; }
