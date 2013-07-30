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
void gPreInit();
static gboolean cell_click(GtkWidget*, GdkEvent*, gpointer);
void uncolor(set<int>&);
void fillCell(GtkWidget*, GtkWidget*, int);
void fill_cell_bg(GtkWidget*, int);
void fill_cell_text(GtkWidget*, int);
static gboolean checkbox_click(GtkWidget*, GdkEvent*, gpointer);
static gboolean confirm_click();
static gboolean make_ai_first_move(gpointer);

GtkWidget *mainWindow;
GtkWidget *labels[125];
GtkWidget *eventBoxes[125];
GtkWidget *whiteAIComboBox, *blackAIComboBox, *introWindow, *whiteAIButton, *blackAIButton;
char names[] = {' ', 'P', 'R', 'N', 'B', 'U', 'Q', 'K'};

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

// Sets AI
chessAI wAI;
chessAI bAI;

int main(int argc, char** argv) {
	gtk_init(&argc, &argv);
	gPreInit();
	//gInit(40);
	gtk_main();

	string input;
	string statetext[] = {
		"Enter the location of the piece to move",
		"Enter a location to move to",
		"Invalid location, try again",
	};

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

void fillCell(GtkWidget *label, GtkWidget *eventBox, int index)
{
	fill_cell_bg(eventBox, index);
	fill_cell_text(label, index);
}

void fill_cell_text(GtkWidget *label, int index)
{
	char buffer[10];
	int val = board[index];
	snprintf(buffer, 10, "%c", names[(val%8)]);
	const char *tcolor = (board[index] > 8) ? "#000000" : "#FFFFFF";
	char *markup = g_markup_printf_escaped("<span face='roman' size='x-large' weight=\"heavy\" foreground=\"%s\">%s</span>", tcolor, buffer);
	gtk_label_set_markup(GTK_LABEL(label), markup);
	g_free(markup);
}

void fill_cell_bg(GtkWidget *eventBox, int index)
{
	GdkColor c;
	gdk_color_parse(((index%25)%2) ? "#f0dab5" : "#b58763", &c);
	gtk_widget_modify_bg(eventBox, GTK_STATE_NORMAL, &c);
}

static gboolean checkbox_click(GtkWidget *widget, GdkEvent *event, gpointer data)
{
	//printf("%p\n", (GtkWidget*) data);
	//printf("%p\n", data);
	//printf("%p\n", (GtkWidget*) widget);
	//printf("%p\n", widget);
	//printf("%p\n", (GtkWidget*) event);
	//printf("%p\n", event);
	/* this shouldn't be the case...but it is. No idea why */
	//printf("%d\n", gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget)));
	gtk_widget_set_sensitive((GtkWidget*) event, gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget)));
	return TRUE;
}

static gboolean confirm_click()
{
	if (gtk_widget_get_sensitive(whiteAIComboBox))
	{
		int whiteAIval = (int) gtk_combo_box_get_active(GTK_COMBO_BOX(whiteAIComboBox));
		printf("whiteAIval = %d\n", whiteAIval);
		if (whiteAIval == -1) return TRUE;
		wAI.setAI(whiteAIval);
		whuman = false;

	}
	if (gtk_widget_get_sensitive(blackAIComboBox))
	{
		int blackAIval = (int) gtk_combo_box_get_active(GTK_COMBO_BOX(blackAIComboBox));
		printf("blackAIval = %d\n", blackAIval);
		if (blackAIval == -1) return TRUE;
		bAI.setAI(blackAIval);
		bhuman = false;
	}
	gtk_widget_set_visible(introWindow, FALSE);
	gtk_widget_show_all(mainWindow);
	if (!whuman)
	{
		//make the first move after 1 second 
		g_timeout_add(1000, make_ai_first_move, (gpointer) 1);
	}
	return TRUE;
}

static gboolean make_ai_first_move(gpointer data)
{
	int ai = (int) ((gint)data);
	printf("%d\n", ai);
	if (ai == 1)
	{
		int computerderp = wAI.getNextMove(board, color);
		moveto(board, computerderp%1000, computerderp/1000);
		//if (checkConditions(board, color==9?(&bAI):(&wAI), true)) break;
		color = 9^1^color;
	}
	return FALSE;
}

void gPreInit()
{
	gInit(40);
	introWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	g_signal_connect(introWindow, "delete-event", G_CALLBACK(gtk_main_quit), NULL);
	//gtk_window_set_default_size(GTK_WINDOW(introWindow), 100, 100);
	gtk_window_set_position(GTK_WINDOW(introWindow), GTK_WIN_POS_CENTER);
	gtk_window_set_title(GTK_WINDOW(introWindow), "3D Chess");	
	gtk_window_set_resizable(GTK_WINDOW(introWindow), false);

	GtkWidget *grid = gtk_grid_new();
	whiteAIButton = gtk_check_button_new_with_label("White AI");
	blackAIButton = gtk_check_button_new_with_label("Black AI");
	whiteAIComboBox = gtk_combo_box_text_new();
	//printf("%p\n", whiteAIButton);
	g_signal_connect(whiteAIButton, "toggled", G_CALLBACK(checkbox_click), (gpointer) whiteAIComboBox);
	blackAIComboBox = gtk_combo_box_text_new();
	g_signal_connect(blackAIButton, "toggled", G_CALLBACK(checkbox_click), (gpointer) blackAIComboBox);
	gtk_widget_set_sensitive(whiteAIComboBox, false);
	gtk_widget_set_sensitive(blackAIComboBox, false);
	vector<string> AINames = wAI.getAIList();
	for (unsigned int i = 0; i < AINames.size(); ++i)
	{
		gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(whiteAIComboBox), AINames[i].c_str()); 
		gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(blackAIComboBox), AINames[i].c_str());	
	}
	gtk_combo_box_set_active(GTK_COMBO_BOX(whiteAIComboBox), 0);
	gtk_combo_box_set_active(GTK_COMBO_BOX(blackAIComboBox), 0);

	GtkWidget *button = gtk_button_new_with_label("Confirm");
	g_signal_connect(button, "clicked", G_CALLBACK(confirm_click), NULL);
	gtk_grid_attach(GTK_GRID(grid), button, 0, 180, 10, 90);
	gtk_grid_attach(GTK_GRID(grid), whiteAIButton, 0, 0, 10, 90);
	gtk_grid_attach(GTK_GRID(grid), blackAIButton, 0, 90, 10, 90);
	gtk_grid_attach_next_to(GTK_GRID(grid), whiteAIComboBox, whiteAIButton, GTK_POS_RIGHT, 10, 90);
	gtk_grid_attach_next_to(GTK_GRID(grid), blackAIComboBox, blackAIButton, GTK_POS_RIGHT, 10, 90);
	gtk_container_add(GTK_CONTAINER(introWindow), grid);
	gtk_widget_show_all(introWindow);
	//printf("%p\n", whiteAIComboBox);
}

void gInit(int cellSide)
{
	mainWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_default_size(GTK_WINDOW(mainWindow), 25*cellSide, 5*cellSide);
	gtk_window_set_title(GTK_WINDOW(mainWindow), "3D Chess");
	gtk_window_set_resizable(GTK_WINDOW(mainWindow), false);
	g_signal_connect(mainWindow, "delete-event", G_CALLBACK(gtk_main_quit), NULL);
	GtkWidget *mainBox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
	for(int b = 0; b < 5; ++b)
	{
		GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
		for(int row = 0; row < 5; ++row)
		{
			GtkWidget *hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
			for(int col = 0; col < 5; ++col)
			{
				int index = 25*b + row*5 + col;
				GtkWidget *eventBox = gtk_event_box_new();
				gtk_widget_set_size_request(eventBox, cellSide, cellSide);
				GtkWidget *label = gtk_label_new(NULL);
				fillCell(label, eventBox, index);
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
		if (b < 4)
		{
			GtkWidget *sep = gtk_separator_new(GTK_ORIENTATION_VERTICAL);
			gtk_box_pack_start(GTK_BOX(mainBox), sep, FALSE, TRUE, 0);
		}
	}
	gtk_container_add(GTK_CONTAINER(mainWindow), mainBox);
	//gtk_widget_set_visible(mainWindow, FALSE);
	//gtk_widget_show_all(mainWindow);
}

bool parity = true;
set<int> posmoves;
static gboolean cell_click(GtkWidget *w, GdkEvent *e, gpointer data)
{
	printf("---------------\n");
	GdkColor gcolor;
	loc = (int) ((gint)data);
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
			//printf("itr=%d\n", *itr);
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
			fill_cell_bg(eventBoxes[save], save);
			posmoves = getPossibleMoves(board, loc, true);
			gdk_color_parse("green", &gcolor);
			printf("loc=%d\n", loc);
			gtk_widget_modify_bg(GTK_WIDGET(eventBoxes[loc]), GTK_STATE_NORMAL, &gcolor);
			gdk_color_parse("red", &gcolor);
			for (std::set<int>::iterator itr = posmoves.begin(); itr != posmoves.end(); ++itr)
			{
				if (*itr != -1)
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
				printf("restoring\n");
				/* restore loc and do nothing */
				loc = save;
				parity = false;
			}
			else
			{
				printf("uncoloring\n");
				uncolor(posmoves);
				fill_cell_bg(eventBoxes[save], save);
				color = 9^1^color;
				moveto(board, save, loc);
				parity = true;
			}
		}
	}
	if ((color == 1) ? !whuman : !bhuman)
	{
		chessAI *ai = (color == 1) ? &wAI : &bAI;
		int computerderp = ai->getNextMove(board, color);
		moveto(board, computerderp%1000, computerderp/1000);
		//if (checkConditions(board, color==9?(&bAI):(&wAI), true)) break;
		color = 9^1^color;
	}
	return TRUE;
}

void uncolor(set<int> &Set)
{
	for (std::set<int>::iterator itr = Set.begin(); itr != Set.end(); ++itr)
	{
		int v = *itr;
		if (v != -1)
			fill_cell_bg(eventBoxes[v], v);
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
	board[from] = 0;
	fill_cell_text(labels[to], to);
	fill_cell_text(labels[from], from);

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
