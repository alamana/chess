#ifndef CHESSMOVE_H
#define CHESSMOVE_H
#include <vector>
#include <set>
#include "chessfunctions.h"
#include "Simulator.h"
using namespace std;

set<int> getPossibleMoves(const int*, const int &, bool);
set<int> getPawnMoves(const int*, const int &, Simulator &, bool);
set<int> getRookMoves(const int*, const int &, Simulator &, bool);
set<int> getKnightMoves(const int*, const int &, Simulator &, bool);
set<int> getBishopMoves(const int*, const int &, Simulator &, bool);
set<int> getUnicornMoves(const int*, const int &, Simulator &, bool);
set<int> getQueenMoves(const int*, const int &, Simulator &, bool);
set<int> getKingMoves(const int*, const int &, Simulator &, bool);

#endif
