#ifndef CHESSMOVE_H
#define CHESSMOVE_H
#include <vector>
#include <set>
#include "chessfunctions.h"
using namespace std;

set<int> getPossibleMoves(int*, int);
set<int> getPawnMoves(int*, int);
set<int> getRookMoves(int*, int);
set<int> getKnightMoves(int*, int);
set<int> getBishopMoves(int*, int);
set<int> getUnicornMoves(int*, int);
set<int> getQueenMoves(int*, int);
set<int> getKingMoves(int*, int);

#endif
