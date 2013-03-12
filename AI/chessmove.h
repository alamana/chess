#ifndef CHESSMOVE_H
#define CHESSMOVE_H
#include <vector>
#include <set>
#include "chessfunctions.h"
using namespace std;

set<int> getPossibleMoves(const int*, const int &);
set<int> getPawnMoves(const int*, const int &);
set<int> getRookMoves(const int*, const int &);
set<int> getKnightMoves(const int*, const int &);
set<int> getBishopMoves(const int*, const int &);
set<int> getUnicornMoves(const int*, const int &);
set<int> getQueenMoves(const int*, const int &);
set<int> getKingMoves(const int*, const int &);

#endif
