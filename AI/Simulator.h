#ifndef SIMULATOR_H
#define SIMULATOR_H

using namespace std;

class Simulator{
	public:
		Simulator(bool);
		void setBoard(const int* board); // should only be called once
		bool checkState; // 0 = not in check, 1 = in check
		int wkingloc, bkingloc; // needs to be set by caller
		int color; // 1 = white, 9 = black, needs to be set by caller
		void simulateMove(int to, int from);
		void makeMove(int to, int from); // keeps the board up to date so that we don't have to keep setting it
	private:
		int board[125];
		bool enabled;
};
#endif
