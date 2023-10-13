#include <algorithm>
#include <iostream>
#include <cstddef>
#include <fstream>
#include <string>
#include <vector>
#include <set>

#include "prefix_tree.h"

#define DEBUG 0

// ENUMS
enum MODE { ONE, ALL, DONE };
enum DIR {
	NW, N, NE,
	W,      E,
	SW, S, SE,
};

// Global variables. These will be set in main, and do not change from recursion to recursion
int width = 0;
int height = 0;
unsigned max_illegal_len = 0;
MODE mode = ONE;

void print_board(char** board) {
	if (DEBUG) std::cout << "================================================" << std::endl;
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (board[i][j] == '\0') { std::cout << '.'; }
			else { std::cout << board[i][j]; }
		}
		std::cout << std::endl;
	}
	if (DEBUG) std::cout << "================================================" << std::endl;
}

void print_board(std::set<std::string> &output, char** board) {
	std::string s = "Board:";
	for (int i = 0; i < height; i++) {
		s += "\n  ";
		for (int j = 0; j < width; j++) {
			s += board[i][j];
		}
	}
	s += "\n";
	output.insert(s);

	if (DEBUG) std::cout << "################################################" << std::endl;
	if (DEBUG) print_board(board);
}

bool compare_length(const std::string& lhs, const std::string& rhs) {
	return lhs.length() > rhs.length();
}

std::string dir_to_string(DIR dir) {
	switch (dir) {
		case NW: return "NW";
		case N:  return "N ";
		case NE: return "NE";
		case W:  return "W ";
		case E:  return "E ";
		case SW: return "SW";
		case S:  return "S ";
		case SE: return "SE";
		default: return "DIR_ERROR";
	}
}

void get_di_dj(DIR dir, int& di, int& dj) {
	switch (dir) {
		case NW: di = -1; dj = -1; break;
		case N:  di = -1; dj =  0; break;
		case NE: di = -1; dj =  1; break;
		case W:  di =  0; dj = -1; break;
		case E:  di =  0; dj =  1; break;
		case SW: di =  1; dj = -1; break;
		case S:  di =  1; dj =  0; break;
		case SE: di =  1; dj =  1; break;
		default: di =  0; dj =  0; break;
	}
}

bool word_matches_illegal(char** board, PrefixTree* illegal,
		int i, int j, DIR dir) {
	if (DEBUG) std::cout << "Checking word at (" << i << ", " << j << ") in direction " << dir_to_string(dir) << std::endl;

	int di, dj;
	get_di_dj(dir, di, dj);

	// Loop until we know that there is or is not an illegal word
	while (i >= 0 && i < height && j >= 0 && j < width) {
		if (DEBUG) if (board[i][j]) std::cout << "Char: " << board[i][j] << std::endl;

		if (!board[i][j]) { return false; }
		if (!(*illegal)[board[i][j]]) { return false; }

		if (DEBUG) {
			std::cout << "Prefix matches." << std::endl;
			if (DEBUG == 2) {
				std::cout << "Current tree:" << std::endl;
				illegal->print(0);
			}
		}

		if ((*illegal)[board[i][j]]->is_leaf()) { return true; }

		illegal = (*illegal)[board[i][j]];
		i += di;
		j += dj;
	}
	return false;
}

// Variables prefixed with m represent details about the [m]odified region.
// Scan the modified area. We search a radius of max_illegal_len for each
// character along the modified region, starting from (mi, mj).
bool board_has_illegal(char** board, PrefixTree* illegal,
		int mi, int mj, int m_len, DIR m_dir, int max_illegal_len) {
	if (DEBUG) std::cout << "Checking board for illegal words" << std::endl;
	if (DEBUG) std::cout << "Current board:" << std::endl;
	if (DEBUG) print_board(board);

	int si, sj; // Used to step through the length of the word
	get_di_dj(m_dir, si, sj);

	// Loop through the length of the word
	for (int i = 0; i < m_len; i++) {
		// Try each orientation
		for (int d = 0; d < 8; d++) {
			int di, dj; // Used to step through the radius
			get_di_dj((DIR)d, di, dj);
			int xi = mi, xj = mj; // Used as the position for the radius search to start at

			// Loop through the radius
			for (int r = 0; r < max_illegal_len; r++) {
				// Check if the word matches the illegal word
				if (word_matches_illegal(board, illegal, xi, xj, (DIR)d)) {
					if (DEBUG) std::cout << "Found illegal word" << std::endl;
					if (DEBUG) print_board(board);
					return true;
				}
				xi -= di;
				xj -= dj;
			}
		}
		mi += si;
		mj += sj;
	}
	return false;
}

// Check if the word can be placed at (i, j) in direction dir
bool can_place_word(char** board, std::string &word, int i, int j, DIR dir) {
	int di, dj;
	get_di_dj(dir, di, dj);

	// Bounds check
	if (i < 0 || i >= height || j < 0 || j >= width) { return false; }
	int end_i = i+(word.length()-1)*di,
		end_j = j+(word.length()-1)*dj;
	if (end_i < 0 || end_i >= height || end_j < 0 || end_j >= width) { return false; }

	// Letters check
	for (unsigned k = 0; k < word.length(); k++) {
		if (board[i][j] != '\0' && board[i][j] != word[k]) { return false; }
		i += di;
		j += dj;
	}

	return true;
}

void place_word(char** board, std::string &word, int i, int j, DIR dir, bool* placement) {
	int di, dj;
	get_di_dj(dir, di, dj);

	for (unsigned k = 0; k < word.length(); k++) {
		placement[k] = (board[i][j] == '\0');
		board[i][j] = word[k];
		i += di;
		j += dj;
	}
}

void remove_word(char** board, std::string &word, int i, int j, DIR dir, bool* placement) {
	if (DEBUG) std::cout << "Removing word: " << word << std::endl;

	int di, dj;
	get_di_dj(dir, di, dj);

	for (unsigned k = 0; k < word.length(); k++) {
		if (placement[k]) { board[i][j] = '\0'; }
		i += di;
		j += dj;
	}
}

// Permutate the board and print the solutions
void fill_board(std::set<std::string> &output, char** board,
		const std::vector<int> &empty, unsigned ind, PrefixTree* illegal) {
	if (DEBUG) std::cout << "Filling board" << std::endl;

	// If we are done, print the board
	if (ind == empty.size()) {
		print_board(output, board);
		return;
	}

	// Get the coordinates of the empty space
	int i = empty[ind] / width,
		j = empty[ind] % width;

	// Loop through the alphabet
	for (char c = 'a'; c <= 'z'; c++) {
		// Check if the board has an illegal word
		board[i][j] = c;
		if (board_has_illegal(board, illegal, i, j, 1, (DIR)0, max_illegal_len)) {
			board[i][j] = '\0';
			continue;
		}

		if (DEBUG) std::cout << "Placing " << c << " at (" << i << ", " << j << ")" << std::endl;

		// If we aren't done yet, recurse
		fill_board(output, board, empty, ind + 1, illegal);
		board[i][j] = '\0';
	}
}

void solve(std::set<std::string> &output, char** board, unsigned ind,
		const std::vector<std::string> &words, PrefixTree* illegal) {
	if (DEBUG) std::cout << "Solving " << ind+1 << " of " << words.size() << std::endl;

	if (mode == DONE) { return; }

	std::string word = words[ind];
	// Array to remove word after placing
	bool placement[word.length()];

	// Loop through the board
	for (int i = 0; i < height; i++)
	for (int j = 0; j < width;  j++) {
	if (DEBUG) std::cout << "(i, j): (" << i << ", " << j << ")" << std::endl;
	// And try all 8 directions
	for (int d = 0; d < 8; d++) {

		// Check if the word can be placed
		if (!can_place_word(board, word, i, j, (DIR)d)) { continue; }

		// Place the word
		place_word(board, word, i, j, (DIR)d, placement);

		// Check if the board has an illegal word
		if (board_has_illegal(board, illegal, i, j, word.length(), (DIR)d, max_illegal_len)) {
			remove_word(board, word, i, j, (DIR)d, placement);
			continue;
		}

		// If we aren't done yet, recurse
		if (ind < words.size() - 1) {
			solve(output, board, ind + 1, words, illegal);
			if (mode == DONE) { return; }
		} else { // Print solutions
			// Generate coordinates of empty spaces
			std::vector<int> empty;
			for (int i = 0; i < height; i++) for (int j = 0; j < width;  j++) {
				if (board[i][j] == '\0') { empty.push_back(i*width + j); }
			}

			// If the board is filled
			if (empty.size() == 0) {
				// Print the board
				print_board(output, board);
				if (mode == ONE) {
					mode = DONE;
					return;
				}
			} else if (mode == ONE) {
				// Fill the empty spaces with 'a'
				for (unsigned k = 0; k < empty.size(); k++) {
					int i = empty[k] / width,
						j = empty[k] % width;
					board[i][j] = 'a';
				}
				// Print the board
				print_board(output, board);
				mode = DONE;
				return;
			} else {
				// Permute the empty spaces and print the solutions
				fill_board(output, board, empty, 0, illegal);
			}
		}

		// Remove the word
		remove_word(board, word, i, j, (DIR)d, placement);
	}}
}

int main(int argc, char* argv[]) {
	if (argc != 4) { return 1; }

	// Process command line arguments
	std::ifstream input_file(argv[1]);
	std::ofstream output_file(argv[2]);
	if (std::string(argv[3]) == "one_solution") { mode = ONE; }
	else if (std::string(argv[3]) == "all_solutions") { mode = ALL; }
	else { return 1; }

	input_file >> width >> height;
	// Allocate and zero the board
	char** board = new char* [height];
	for (int i = 0; i < height; i++) {
		board[i] = new char[width];
		for (int j = 0; j < width; j++) {
			board[i][j] = '\0';
		}
	}

	// Find the required and illegal words
	std::vector<std::string> words;
	PrefixTree* illegal = new PrefixTree();

	for (char pre; input_file >> pre;) {
		std::string line;
		input_file >> line;
		switch (pre) {
		case '+':
			words.push_back(line);
			break;
		case '-':
			illegal->add(line, 0);
			if (line.length() > max_illegal_len)
			{ max_illegal_len = line.length(); }
			break;
		default:
			return 2;
		}
	}

	// NOTE: potential improvement with DFS to find true max_illegal_len

	// NOTE: potential improvement from sorting vector by length
	std::sort(words.begin(), words.end(), compare_length);

	if (DEBUG) illegal->print(0);
	if (DEBUG) std::cout << "Max Illegal Length: " << max_illegal_len << std::endl;

	if (DEBUG) {
		std::cout << "Words: " << std::endl;
		for (unsigned i = 0; i < words.size(); i++) {
			std::cout << words[i] << std::endl;
		}
	}

	// Find the output
	std::set<std::string> output;
	solve(output, board, 0, words, illegal);

	output_file << output.size() << " solution(s)\n";
	for (std::set<std::string>::iterator it = output.begin(); it != output.end(); it++) {
		output_file << *it;
	}

	if (DEBUG) output_file << "solution_count: " << output.size() << std::endl;
	output_file.close();

	return 0;
}
