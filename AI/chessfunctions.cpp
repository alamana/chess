#include "chessfunctions.h"

using namespace std;

// Converts byx coordinates into a integer location
int ind(int b, int y, int x) { return b*25+y*5+x; }

// Adds byx to an integer location, returns -1 if invalid.
int locAdd(int loc, int b, int y, int x) {
    int bcur = loc/25;
    int ycur = (loc/5)%5;
    int xcur = loc%5;
    if (b+bcur >4 || b+bcur < 0) return -1;
    if (y+ycur >4 || y+ycur < 0) return -1;
    if (x+xcur >4 || x+xcur < 0) return -1;
    return ind(b+bcur, y+ycur, x+xcur);
}

// Return -1 if empty square, 1 if diff color, 0 if same colors
int opponents(int a, int b) {
    if (a==0 || b==0) return -1;
    return ((a-8)<0)^((b-8)<0)?1:0; //a and b are diff colors ? 1 : 0;
}
