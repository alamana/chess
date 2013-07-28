#include <iostream>
#include <string>
#include <stdio.h>
#include <iterator>
#include "chessoutput.h"
#include "AI/chessmove.h"
#include "AI/chessAI.h"
#include <gtk/gtk.h>

using namespace std;

int parseInput(string);
void moveto(int*, int, int);
bool checkConditions(int*, chessAI *, bool);

void gInit(int cellSide);
static gboolean cell_click(GtkWidget*, GdkEvent*, gpointer);
void uncolor(set<int>&);

GtkWidget *mainWindow;
GtkWidget *labels[125];
GtkWidget *eventBoxes[125];
char names[] = {'_', 'P', 'R', 'N', 'B', 'U', 'Q', 'K'};

// Standard starting board.
// 1 = Pawn		5 = Unicorn
// 2 = Rook		6 = Queen 
// 3 = Knight	7 = King
// 4 = Bishop	0 = Empty
// #+8 = Black pieces.
int board[] = {
	2, 3, 7, 3, 2, //  0  1  2  3  4
	1, 1, 1, 1, 1, //  5  6  7  8  9
	0, 0, 0, 0, 0, // 10 11 12 13 14
	0, 0, 0, 0, 0, // 15 16 17 18 19
	0, 0, 0, 0, 0, // 20 21 22 23 24

	4, 5, 6, 4, 5, // 25 26 27 28 29
	1, 1, 1, 1, 1,
	0, 0, 0, 0, 0,
	0, 0, 0, 0, 0,
	0, 0, 0, 0, 0,

	0, 0, 0, 0, 0,
	0, 0, 0, 0, 0,
	0, 0, 0, 0, 0,
	0, 0, 0, 0, 0,
	0, 0, 0, 0, 0,

	0, 0, 0, 0, 0,  // 75 76 77 78 79
	0, 0, 0, 0, 0,  // 80 81 82 83 84
	0, 0, 0, 0, 0,  // 85 86 87 88 89
	9, 9, 9, 9, 9,  // 90 91 92 93 94
	13,12,14,13,12, // 95 96 97 98 99

	0, 0, 0, 0, 0,
	0, 0, 0, 0, 0,
	0, 0, 0, 0, 0,
	9, 9, 9, 9, 9,
	10,11,15,11,10, // 120 121 122 123 124
};

int loc   = -1;
int state =  0;
int save  = -1;
int color = 1; // 1 is white, 9 is black, to exploit the way
// the opponents function works
bool error = false;
bool whuman = true;
bool bhuman = true;

int main(int argc, char** argv) {
	gtk_init(&argc, &argv);
	gInit(40);
	gtk_main();

	string input;
	string statetext[] = {
		"Enter the location of the piece to move",
		"Enter a location to move to",
		"Invalid location, try again",
	};

	// Sets AI
	chessAI wAI;
	chessAI bAI;

	char humanity = 0;
	while (humanity != 'y' && humanity != 'n') {
		cout << "Is white a human player? (y/n): ";
		cin >> humanity;
	}
	whuman = (humanity=='y') ? true : false;
	if (!whuman) {
		cout << "White isn't human!" << endl;
		wAI.setAI();
	}

	humanity = 0;
	while (humanity != 'y' && humanity != 'n') {
		cout << "Is black a human player? (y/n): ";
		cin >> humanity;
	}
	bhuman = (humanity=='y') ? true : false;
	if (!bhuman) {
		cout << "Black isn't human!" << endl;
		bAI.setAI();
	}

	//Gameloop
	while (true) {
		set<int> posmoves = getPossibleMoves(board, loc, true); // enable checking
		printBoard(board, loc,posmoves);
		if ((color==1 && whuman) || (color==9 && bhuman)) {
			cout << "\t" <<(color==1?"WHITE: ":"BLACK: ") << statetext[error?2:state] << ": ";
			cin >> input;
			loc = parseInput(input);
			error = false;
			switch (state) {
				case 0:
					if (loc == -1 || opponents(color, board[loc]) != 0) {
						error = true;
					}
					else {
						state = 1;
						save = loc;
					}
					break;
				case 1:
					if (loc == -1) {
						error = true;
						loc = save;
					}
					else if (opponents(color, board[loc]) == 0) {
						state = 1;
						save = loc;
					}
					else if (posmoves.find(loc) == posmoves.end()) {
						error = true;
						state = 0;
						loc = save;
					}
					else {
						state = 0;
						moveto(board, save, loc);
						loc = -1;
						save = -1;
						//switches color between 9 and 1
						color = 9^1^color;
					}
					break;
			}
			if (checkConditions(board, NULL, false)) break;
		}
		else {
			cout << "\t" <<(color==1?"WHITE ":"BLACK ") << "is a computer, it will move now.\n";
			int computerderp = (color==1) ? wAI.getNextMove(board, color) : bAI.getNextMove(board,color);
			moveto(board, computerderp%1000, computerderp/1000);
			if (checkConditions(board, color==9?(&bAI):(&wAI), true)) break;
			color = 9^1^color;
		}
		cout << "\n\n\n";
	}
	cout << "\n\n";
	printBoard(board, -1, getPossibleMoves(board, -1, true));

	return 0;
}

void gInit(int cellSide)
{
	//GtkCssProvider *gcp = gtk_css_provider_get_default();
	//GError *gerror;
	//GFile *gfile = g_file_new_for_path("./style.css");
	//gtk_css_provider_load_from_file(gcp, gfile, &gerror);
	//if (gerror == NULL) printf("gerror is NULL\n");
	char buffer[10];
	mainWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_default_size(GTK_WINDOW(mainWindow), 25*cellSide, 5*cellSide);
	gtk_window_set_title(GTK_WINDOW(mainWindow), "3D Chess");
	g_signal_connect(mainWindow, "delete-event", G_CALLBACK(gtk_main_quit), NULL);
	GtkWidget *mainBox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);//gtk_hbox_new(FALSE, 10);
	for(int b = 0; b < 5; ++b)
	{
		GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);//gtk_vbox_new(TRUE, 10);
		bool flag = true;
		for(int row = 0; row < 5; ++row)
		{
			GtkWidget *hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0); //gtk_hbox_new(TRUE, 10);
			for(int col = 0; col < 5; ++col)
			{
				int index = 25*b + row*5 + col;
				int val = board[index];
				//printf("%d\n", (val%8));
				snprintf(buffer, 10, "%c", names[(val%8)]);
				GtkWidget *eventBox = gtk_event_box_new();
				gtk_widget_set_size_request(eventBox, cellSide, cellSide);
				GdkColor c;
				gdk_color_parse((flag) ? "#F8F8FF" : "light gray", &c);
				flag = !flag;
				gtk_widget_modify_bg(eventBox, GTK_STATE_NORMAL, &c);
				//gtk_container_set_border_width(GTK_CONTAINER(eventBox), 5);
				//gtk_event_box_set_above_child(GTK_EVENT_BOX(eventBox), TRUE);
				//gtk_event_box_set_visible_window(GTK_EVENT_BOX(eventBox), TRUE);
				GtkWidget *label = gtk_label_new(buffer);
				gtk_container_add(GTK_CONTAINER(eventBox), label);
				gtk_widget_set_events(eventBox, GDK_BUTTON_PRESS_MASK);
				g_signal_connect(eventBox, "button_press_event", G_CALLBACK(cell_click), (gpointer) index);
				gtk_box_pack_start(GTK_BOX(hbox), eventBox, FALSE, TRUE, 0);
				labels[index] = label;
				eventBoxes[index] = eventBox;
			}
			gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, TRUE, 0);
		}
		gtk_box_pack_start(GTK_BOX(mainBox), vbox, FALSE, TRUE, 0);
		GtkWidget *sep = gtk_separator_new(GTK_ORIENTATION_VERTICAL);
		gtk_box_pack_start(GTK_BOX(mainBox), sep, FALSE, TRUE, 0);
	}
	gtk_container_add(GTK_CONTAINER(mainWindow), mainBox);
	gtk_widget_show_all(mainWindow);
}

bool parity = true;
set<int> posmoves;
static gboolean cell_click(GtkWidget *w, GdkEvent *e, gpointer data)
{
	printf("---------------\n");
	GdkColor gcolor;
	loc = (int) ((gint) data);
	printf("loc=%d\n", loc);
	printf("color=%d\n", color);
	/* parity = true, click to select a cell */
	/* get possible moves and color them, unless the cell is empty or an opponents */
	if (parity)
	{
		if (opponents(color, board[loc]) != 0) return TRUE;
		/* color the square that was clicked */
		gdk_color_parse("green", &gcolor);
		gtk_widget_modify_bg(GTK_WIDGET(eventBoxes[loc]), GTK_STATE_NORMAL, &gcolor);
		/* Get set of possible moves and color them */
		posmoves = getPossibleMoves(board, loc, true);
		gdk_color_parse("red", &gcolor);
		for (std::set<int>::iterator itr = posmoves.begin(); itr != posmoves.end(); ++itr)
		{
			gtk_widget_modify_bg(GTK_WIDGET(eventBoxes[*itr]), GTK_STATE_NORMAL, &gcolor);
		}
		save = loc;
		parity = false;
	}
	else
	{
		printf("entering else\n");
		/* check to see if the second cell clicked is a valid click */
		if (opponents(color, board[loc]) == 0)
		{
			printf("opponents(color, board[loc]) == 0\n");
			uncolor(posmoves);
			gtk_widget_modify_bg(GTK_WIDGET(eventBoxes[save]), GTK_STATE_NORMAL, NULL);	
			posmoves = getPossibleMoves(board, loc, true);
			gdk_color_parse("green", &gcolor);
			gtk_widget_modify_bg(GTK_WIDGET(eventBoxes[loc]), GTK_STATE_NORMAL, &gcolor);
			gdk_color_parse("red", &gcolor);
			for (std::set<int>::iterator itr = posmoves.begin(); itr != posmoves.end(); ++itr)
			{
				gtk_widget_modify_bg(GTK_WIDGET(eventBoxes[*itr]), GTK_STATE_NORMAL, &gcolor);
			}
			save = loc;
			parity = false;
		}
		else 
		{
			printf("entering second else\n");
			set<int> moveset = getPossibleMoves(board, save, true);
			if (moveset.find(loc) == moveset.end())
			{
				/* restore loc and do nothing */
				loc = save;
				parity = false;
			}
			else
			{
				uncolor(posmoves);
				gtk_widget_modify_bg(GTK_WIDGET(eventBoxes[save]), GTK_STATE_NORMAL, NULL);
				color = 9^1^color;
				moveto(board, save, loc);
				parity = true;
			}
		}
	}
	return TRUE;
}

void uncolor(set<int> &Set)
{
	for (std::set<int>::iterator itr = Set.begin(); itr != Set.end(); ++itr)
	{
		gtk_widget_modify_bg(GTK_WIDGET(eventBoxes[*itr]), GTK_STATE_NORMAL, NULL);
	}
}

int parseInput (string input) {
	// Tests every possible combination of letters and checks for validity
	if (input.size() < 3) return -1;
	int b = input[0]-65;
	int y = input[1]-48; //012
	int x = input[2]-97;
	int n = locAdd(0, b, y, x);
	if (n != -1) return n;
	b = input[2]-65;
	y = input[0]-48; //201
	x = input[1]-97;
	n = locAdd(0, b, y, x);
	if (n != -1) return n;
	b = input[1]-65;
	y = input[0]-48; //102
	x = input[2]-97;
	n = locAdd(0, b, y, x);
	if (n != -1) return n;
	b = input[1]-65;
	y = input[2]-48; //120
	x = input[0]-97;
	n = locAdd(0, b, y, x);
	if (n != -1) return n;
	b = input[2]-65;
	y = input[1]-48; //210
	x = input[0]-97;
	n = locAdd(0, b, y, x);
	if (n != -1) return n;
	b = input[0]-65;
	y = input[2]-48; //021
	x = input[1]-97;
	n = locAdd(0, b, y, x);
	return n;
}

// starting positions
int bkloc = 122;
int wkloc = 3;

// -1 = invalid move, still in check after move
//  0 = valid move, no check resulting from it
//  1 = valid move, oppenent is in check from it


void moveto(int* board, int from, int to) {
	board[to] = board[from];
	gtk_label_set_text(GTK_LABEL(labels[to]), gtk_label_get_text(GTK_LABEL(labels[from])));
	gtk_label_set_text(GTK_LABEL(labels[from]), "_");
	board[from] = 0;

	// see if a king was moved
	if (from == bkloc) bkloc = to;
	if (from == wkloc) wkloc = to;
}

bool checkConditions(int *board, chessAI *AI, const bool nothuman) {
	//Promote pawn
	for (int i=0; i<5; i++)
		if (board[i] == 9) {
			int piece=0;
			if (nothuman) piece = AI->pawnPromotion(board, 9);
			else while (piece < 1 || piece > 4) {
				cout << "\n\nBlack promotion! What would you like your pawn to become?" << endl;
				cout << "\t1. Rook\n\t2. Knight\n\t3. Bishop\n\t 4. Unicorn\n";
				cin >> piece;
			}
			board[i] = piece+1+8;
		}
	for (int i=120; i<125; i++)
		if (board[i] == 1) {
			int piece=0;
			if (nothuman) piece = AI->pawnPromotion(board, 1);
			else while (piece < 1 || piece > 4) {
				cout << "\n\nWhite promotion! What would you like your pawn to become?" << endl;
				cout << "\t1. Rook\n\t2. Knight\n\t3. Bishop\n\t 4. Unicorn\n";
				cin >> piece;
			}
			board[i] = piece+1;
		}


	bool wking = false;
	bool bking = false;
	for (int i=0; i<125; i++) {
		if (board[i] == 7) wking = true;
		if (board[i] == 15) bking = true;
	}

	if (!(wking&&bking)) {
		cout << (wking?"White":"Black") << " wins!" << endl;
		return true;
	}
	return false;
}
