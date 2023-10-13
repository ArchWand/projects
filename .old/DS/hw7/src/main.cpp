#include <cstdio>
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <set>

#define MOVECOUNT 7
enum MOVE { JAB, FTILT, UTILT, DTILT, FSMASH, USMASH, DSMASH, INVALID};
const std::string move_names[7] = {"jab", "forward-tilt", "up-tilt", "down-tilt", "forward-smash", "up-smash", "down-smash"};

struct Fighter {
	std::string name;
	int move[MOVECOUNT];
	MOVE sort;
};

// Comparison operators for Fighter
bool operator<(const Fighter &a, const Fighter &b) {
	// Error checking
	if (a.sort != b.sort) { return false; }

	switch(a.sort) {
		case JAB: if (a.move[JAB] != b.move[JAB]) { return a.move[JAB] < b.move[JAB]; } break;
		case FTILT: if (a.move[FTILT] != b.move[FTILT]) { return a.move[FTILT] < b.move[FTILT]; } break;
		case UTILT: if (a.move[UTILT] != b.move[UTILT]) { return a.move[UTILT] < b.move[UTILT]; } break;
		case DTILT: if (a.move[DTILT] != b.move[DTILT]) { return a.move[DTILT] < b.move[DTILT]; } break;
		case FSMASH: if (a.move[FSMASH] != b.move[FSMASH]) { return a.move[FSMASH] < b.move[FSMASH]; } break;
		case USMASH: if (a.move[USMASH] != b.move[USMASH]) { return a.move[USMASH] < b.move[USMASH]; } break;
		case DSMASH: if (a.move[DSMASH] != b.move[DSMASH]) { return a.move[DSMASH] < b.move[DSMASH]; } break;
		default: return false;
	}
	return a.name < b.name;
}

void read_data(std::ifstream &database, std::map<std::string, Fighter> &q, std::map<MOVE, std::map<int, std::set<Fighter>>> &fsd) {
	std::string line;
	getline(database, line); // Remove header

	// Loop to the end of the file
	while (database >> line) {
		// Create the Fighter
		Fighter f;
		f.name = line;
		for(int i = 0; i < MOVECOUNT; i++)
		{ database >> f.move[(MOVE)i]; }

		// Add fighter to query map
		q[f.name] = f;

		// Add fighter to map of move speeds
		for (int i = 0; i < MOVECOUNT; i++) {
			f.sort = (MOVE)i;
			fsd[(MOVE)i][f.move[(MOVE)i]].insert(f);
		}
	}
}

MOVE move_from_string(std::string &line) {
	for (int i = 0; i < MOVECOUNT; i++) {
		if (line == move_names[i]) {
			return (MOVE)i;
		}
	}
	return INVALID;
}

void query(std::ofstream &outfile, Fighter fighter, MOVE move, bool all) {
	// Print the fighter's move speed
	if (all) { // Alphabetical
		// O(1) sorting
		outfile << fighter.name << " " << move_names[DSMASH] << ": " << fighter.move[DSMASH] << std::endl;
		outfile << fighter.name << " " << move_names[DTILT]  << ": " << fighter.move[DTILT]  << std::endl;
		outfile << fighter.name << " " << move_names[FSMASH] << ": " << fighter.move[FSMASH] << std::endl;
		outfile << fighter.name << " " << move_names[FTILT]  << ": " << fighter.move[FTILT]  << std::endl;
		outfile << fighter.name << " " << move_names[JAB]    << ": " << fighter.move[JAB]    << std::endl;
		outfile << fighter.name << " " << move_names[USMASH] << ": " << fighter.move[USMASH] << std::endl;
		outfile << fighter.name << " " << move_names[UTILT]  << ": " << fighter.move[UTILT]  << std::endl;
	} else {
		outfile << fighter.name << " " << move_names[move] << ": " << fighter.move[move] << std::endl;
	}
}

// Print the fighters at the ends of the spectrum
template<typename IT>
void fast_slow(std::ofstream &outfile, int limit, IT start, IT end) {
	if (!limit) return;
	do {
		std::set<Fighter>::iterator it = start->second.begin();
		while (limit && it != start->second.end()) {
			outfile << it->name << " " << it->move[it->sort] << std::endl;
			limit--;
			it++;
		}
		start++;
	} while (limit && start != end);
}

void duration(std::ofstream &outfile, const std::set<Fighter> &frame_set) {
	// Print the fighters with the given move duration
	for (std::set<Fighter>::iterator it = frame_set.begin(); it != frame_set.end(); it++) {
		outfile << it->name << std::endl;
	}
}

int main(int argc, char** argv) {
	// Argument parsing
	if (argc != 4) {
		std::cerr << "Proper usage is " << argv[0] << " [database file] [input file] [output file]" << std::endl;
		return -1;
	}

	std::ifstream dbfile(argv[1]);
	if (!dbfile) { std::cerr << "Failed to open database " << argv[1] << " for reading." << std::endl; }

	std::ifstream infile(argv[2]);
	if (!infile) { std::cerr << "Failed to open input " << argv[2] << " for reading." << std::endl; }

	std::ofstream outfile(argv[3]);
	if (!outfile) { std::cerr << "Failed to open output " << argv[3] << " for writing." << std::endl; }

	std::map<std::string, Fighter> q;
	std::map<MOVE, std::map<int, std::set<Fighter>>> fsd;
	read_data(dbfile, q, fsd);
	dbfile.close();

	// Parse query file
	std::string line;
	char cmd;
	while (infile >> cmd) {
		if (cmd != '-') { return 1; }
		infile >> cmd;

		Fighter fighter;
		MOVE move;
		int num;
		switch (cmd) {
			case 'q':
				// Get the fighter
				infile >> line;
				// Check for existence
				if (q.find(line) == q.end()) {
					outfile << "Invalid character name: " << line << std::endl;
					break;
				}
				fighter = q.find(line)->second;

				// Get the move
				infile >> line;
				move = move_from_string(line);
				// Check for existence
				if (line != "all" && move == INVALID) {
					outfile << "Invalid move name: " << line << std::endl;
					break;
				}

				if (line == "all") { query(outfile, fighter, move, true); }
				else { query(outfile, fighter, move, false); }
				outfile << std::endl;
				break;

			case 'f':
				// Get the move
				infile >> line;
				move = move_from_string(line);
				// Get the limit
				infile >> num;

				// Check for existence
				if (move == INVALID) {
					outfile << "Invalid move name: " << line << std::endl;
					break;
				}

				// Print command
				outfile << "-f " << line << " " << num << std::endl;
				fast_slow<std::map<int, std::set<Fighter>>::iterator>(outfile, num, fsd.find(move)->second.begin(), fsd.find(move)->second.end());
				outfile << std::endl;
				break;

			case 's':
				// Get the move
				infile >> line;
				move = move_from_string(line);
				// Get the limit
				infile >> num;

				// Check for existence
				if (move == INVALID) {
					outfile << "Invalid move name: " << line << std::endl;
					break;
				}

				// Print command
				outfile << "-s " << line << " " << num << std::endl;
				fast_slow<std::map<int, std::set<Fighter>>::reverse_iterator>(outfile, num, fsd.find(move)->second.rbegin(), fsd.find(move)->second.rend());
				outfile << std::endl;
				break;

			case 'd':
				// Get the move
				infile >> line;
				move = move_from_string(line);
				// Check for existence
				if (move == INVALID) {
					outfile << "Invalid move name: " << line << std::endl;
					break;
				}

				// Get the startup frame
				infile >> num;

				outfile << "-d " << line << " " << num << std::endl;
				duration(outfile, fsd.find(move)->second.find(num)->second);
				outfile << std::endl;
				break;

			default:
				continue;
		}
	}

	return 0;
}
