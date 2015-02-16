/**
 * -one life, upon new game the player spawns as a new character.
 * -old char's corpse remains in game and can be looted
 * -upon death, on the death pos a ghost spawns which has to be fought in order
 *  to loot the corpse
 * -4 directional movement to start //may switch to omnidirectional later
 * -create the toolmaker to be able to build maps in game
 * -don't skip on the random map generation algorithm though
 * -build the structure simple at first, using ascii //colored though/w(ncurses)
 * -threads
 * -simple but non-generic start menu
 * -possibly implement a savegame feature
 * -unforgiving bosses with stun/mind control abilities
 * -player character as an ethereal?(made of magic light, wrapped in bandages(?))
 * -turn based rpg on a chessboard? could be an idea
 * -boss that gains xp with player deaths, so as he kills more player characters it becomes harder and harder to defeat
 *    -upon death the boss could give the player character all of the acumulated xp gained until that moment
 *    -lvl 10 creature killed at level 10 to give 100 xp, killed at level 9 giving 125 and at 11, only 75
 * -AI character that gains the same xp as the player that the player would have to defeat at the end of the game(secret character maybe(?))
 * -
 */

#include <ncurses.h>
/**
 * "erase" character definition, use an empty character for cleaning a cell or a
 * visible character for showing the trace of a game character
 */

void erase (int y, int x) {
	mvaddch(y, x, '#');
}

//ncurses initialization
void init() {
	initscr();
	clear();
	noecho();
	cbreak();
	keypad(stdscr, TRUE);
	curs_set(0);
}

//game loop
void game_loop(char main_char, int row, int col, int ch) {
	//continue or quit check
	if(ch == 'q' || ch =='Q') return;

	//main char print
	mvaddch(row, col, main_char);
	refresh();

	for(;;) {
		ch = getch();

		if(ch == KEY_LEFT) {
			erase(row, col);
			col = col - 1;
			mvaddch(row, col, main_char);
			refresh();
		}
		else if(ch == KEY_RIGHT) {
			erase(row, col);
			col = col + 1;
			mvaddch(row, col, main_char);
			refresh();
		}
		else if(ch == KEY_UP) {
			erase(row, col);
			row = row - 1;
			mvaddch(row, col, main_char);
			refresh();
		}
		else if(ch == KEY_DOWN) {
			erase(row, col);
			row = row + 1;
			mvaddch(row, col, main_char);
			refresh();
		}
		else if(ch == 'q' || ch == 'Q') {
			break;
		}
	}
}

//entry function
int main() {
	//main character symbol and initial position
	int row = 10, col = 10;
	char main_char = '@';
	
	//ncurses init
	init();
	
	printw("Welcome to Muspellheimr, a world of  and cranky weasels.\nPress any key to start.\nTo quit press \"q\" or \"Q\"");
	int ch = getch();
	clear();
	game_loop(main_char, row, col, ch);

	//clear ncurses data structures
	endwin();
	return 0;
}
