#ifndef AIOPTIMIZEDMOVE_H
#define AIOPTIMIZEDMOVE_H
#include <iostream>
#include <vector>
#include <set>
#include "chessfunctions.h"
using namespace std;

class List {
    public:
	int value;
        List * next;

	List() { next = NULL; value = -1;};

	~List() { cleanList(); };

	void cleanList() {
	    if (next==NULL) return;
	    else next->cleanList();
	    delete next;
	};
	    
	void insert(int v) {
	    if (value == -1) {
		value = v;
		next = new List;
		return;
	    }
	    next->insert(v);
	};

	void printlist();
};

class AIoptimizedmove {
    public:
	AIoptimizedmove();
	int getPossibleMoves(int *, const int*, const int &);
    private:
	void setPossibleMoves(const int&, const int &);
	void setPawnMoves(const int &);
	void setRookMoves(const int &);
	void setKnightMoves(const int &);
	void setBishopMoves(const int &);
	void setUnicornMoves(const int &);
	void setQueenMoves(const int &);
	void setKingMoves(const int &);

	List * table[125][8][26];
};

#endif
