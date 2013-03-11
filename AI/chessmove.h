#ifndef CHESSMOVE_H
#define CHESSMOVE_H
#include <vector>
#include <set>
#include "chessfunctions.h"
using namespace std;

set<int> getPossibleMoves(int*, const int &);
set<int> getPawnMoves(int*, const int &);
set<int> getRookMoves(int*, const int &);
set<int> getKnightMoves(int*, const int &);
set<int> getBishopMoves(int*, const int &);
set<int> getUnicornMoves(int*, const int &);
set<int> getQueenMoves(int*, const int &);
set<int> getKingMoves(int*, const int &);

#endif
