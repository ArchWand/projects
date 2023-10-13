#include <bits/stdc++.h>
#include <fstream>
#include <unordered_set>
using namespace std;

#define DEBUG 0

enum DIR{ UP, DOWN, LEFT, RIGHT, NONE };

int w = 0;

struct coord {
	coord(): x(0), y(0) {};
	coord(int i, int j): x(i), y(j) {};
	int x;
	int y;
	bool operator==(const coord& that) const {
		return this->x == that.x && this->y == that.y;
	}
	bool operator<(const coord& that) const{
		int a = this->x + this->y*(w+2);
		int b =  that.x +  that.y*(w+2);
		return a < b;
	}
	string to_string() const {
		return ::to_string(x) + " " + ::to_string(y);
	}
	string out_string() const {
		return ::to_string(y) + " " + ::to_string(x);
	}
};

void update_coords(vector<vector<DIR>> board, coord& c) {
	DIR d = board[c.x][c.y];
	switch (d) {
		case UP:    c.y--; break;
		case DOWN:  c.y++; break;
		case LEFT:  c.x--; break;
		case RIGHT: c.x++; break;
		case NONE:
		default:
			break;
	}
}

bool on_edge(const coord& c, int h, int w) {
	return c.x == 0 || c.y == 0 || c.x == w+1 || c.y == h+1;
}

typedef unordered_set<coord> cset;

int main() {
	int h, q;
	cin >> h >> w >> q;

	vector<vector<DIR>> board;
	for (int i = 0; i < h+2; i++) {
		for (int j = 0; j < w+2; j++) {
			board.emplace_back(vector<DIR>(h+2, NONE));
		}
	}

	// Read in the board
	for (int i = 1; i <= h; i++) {
		for (int j = 1; j <= w; j++) {
			char c;
			cin >> c;
			switch (c) {
				case 'U': board[j][i] =    UP; break;
				case 'D': board[j][i] =  DOWN; break;
				case 'L': board[j][i] =  LEFT; break;
				case 'R': board[j][i] = RIGHT; break;
			}
		}
	}

	// Map out all possible paths
	vector<coord> prefix[h+2][w+2];
	vector<coord> loop[h+2][w+2];
	for (int i = 1; i <= h; i++) {
		for (int j = 1; j <= w; j++) {
			set<coord> curr_set;
			vector<coord> curr_vector;
			int loop_start = -1;

			coord curr(j, i);
			curr_set.insert(curr);
			curr_vector.push_back(curr);

			// Follow execution until we find a loop or reach the edge of the board
			while(!on_edge(curr, h, w)) {
				update_coords(board, curr);

				// If we encounter a tile we've been on, set loop_start and break
				if (curr_set.find(curr) != curr_set.end()) {
					for (unsigned k = 0; k < curr_vector.size(); k++) {
						if (curr_vector[k] == curr) {
							loop_start = k;
							break;
						}
					}
					break;
				}

				curr_set.insert(curr);
				curr_vector.push_back(curr);
			}

			if (loop_start == -1) {
				prefix[j][i] = curr_vector;
				loop[j][i] = vector<coord>();
			} else {
				prefix[j][i] = vector<coord>(curr_vector.begin(), curr_vector.begin() + loop_start);
				loop[j][i] = vector<coord>(curr_vector.begin() + loop_start, curr_vector.end());
			}
		}
	}

	// Find the queries
	vector<coord> query;
	vector<int> times;
	for (int i = 0; i < q; i++) {
		int x, y;
		unsigned t;
		cin >> y >> x >> t;

		vector<coord> p = prefix[x][y];
		vector<coord> l = loop[x][y];

		// DEBUG
		if (DEBUG) {
			cout << endl;
			cout << "Finding: (" << x << ", " << y << ") " << t << endl;
			cout << "prefix:";
			if (p.size() == 0) {
				cout << " none" << endl;
			} else {
				cout << endl;
				for (auto c : p) {
					cout << c.to_string() << endl;
				}
			}
			cout << "loop:";
			if (l.size() == 0) {
				cout << " none" << endl;
			} else {
				cout << endl;
				for (auto c : l) {
					cout << c.to_string() << endl;
				}
			}
			cout << "===" << endl;
			cout << "Board:" << endl;
			vector<vector<bool>> b;
			for (int i = 0; i < h+2; i++) {
				b.emplace_back(vector<bool>(w+2, false));
			}
			for (auto c : p) {
				b[c.x][c.y] = true;
			}
			for (auto c : l) {
				b[c.x][c.y] = true;
			}
			for (int i = 0; i < h+2; i++) {
				for (int j = 0; j < w+2; j++) {
					if (b[j][i]) {
						cout << "X";
					} else {
						if (i == 0 || i == h+1 || j == 0 || j == w+1) {
							cout << "#";
						} else {
							cout << " ";
						}
					}
				}
				cout << endl;
			}
		}

		if (t < p.size()) {
			cout << p[t].out_string() << endl;
		} else {
			if (l.size() == 0) {
				cout << p.back().out_string() << endl;
			} else {
				t -= p.size();
				t %= l.size();
				cout << l[t].out_string() << endl;
			}
		}
	}
}
