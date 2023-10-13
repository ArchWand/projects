#include <algorithm>
#include "coz.h"
#include <unordered_set>
#include <set>
#include <fstream>
#include <vector>
#include <list>
#include <iostream>
#include <stdio.h>
#include <bitset>
bool localizedCheckExists(const int & x, const int & y, const int & cx, const int & cy, char* board, const std::vector<std::vector<std::pair<std::string, std::vector<int> > > > & badsByLetter) {
	// std::cout << cx << " " << cy << std::endl;
	bool up, down, left, right, ul, ur, dl, dr;
	for(int i = 0; i < int(badsByLetter[board[cx*y+cy]].size()); i++) {

		for(int q = 0; q < int(badsByLetter[board[cx*y+cy]][i].second.size()); q++) {
			right = cx-badsByLetter[board[cx*y+cy]][i].second[q] >= 0 && cx+int(badsByLetter[tolower(board[cx*y+cy])][i].first.size())-badsByLetter[tolower(board[cx*y+cy])][i].second[q] <= x;
			left = cx+badsByLetter[board[cx*y+cy]][i].second[q] < x && cx-int(badsByLetter[tolower(board[cx*y+cy])][i].first.size())+badsByLetter[tolower(board[cx*y+cy])][i].second[q] >= -1;
			up = cy-badsByLetter[board[cx*y+cy]][i].second[q] >= 0 && cy+int(badsByLetter[tolower(board[cx*y+cy])][i].first.size())-badsByLetter[tolower(board[cx*y+cy])][i].second[q] <= y;
			down = cy+badsByLetter[board[cx*y+cy]][i].second[q] < y && cy-int(badsByLetter[tolower(board[cx*y+cy])][i].first.size())+badsByLetter[tolower(board[cx*y+cy])][i].second[q] >= -1;
			ur = up && right;
			ul = up && left;
			dr = down && right;
			dl = down && left;



			for(int z = 0; z < int(badsByLetter[board[cx*y+cy]][i].first.size()); z++) {
				right = right && badsByLetter[board[cx*y+cy]][i].first.at(z) == tolower(board[(cx+(z-badsByLetter[tolower(board[cx*y+cy])][i].second[q]))*y+cy]);
				left = left && badsByLetter[board[cx*y+cy]][i].first.at(z) == tolower(board[(cx-(z-badsByLetter[tolower(board[cx*y+cy])][i].second[q]))*y+cy]);
				up = up && badsByLetter[board[cx*y+cy]][i].first.at(z) == tolower(board[(cx)*y+cy+(z-badsByLetter[tolower(board[cx*y+cy])][i].second[q])]);
				down = down && badsByLetter[board[cx*y+cy]][i].first.at(z) == tolower(board[(cx)*y+cy-(z-badsByLetter[tolower(board[cx*y+cy])][i].second[q])]);
				ur = ur && badsByLetter[board[cx*y+cy]][i].first.at(z) == tolower(board[(cx+(z-badsByLetter[tolower(board[cx*y+cy])][i].second[q]))*y+cy+(z-badsByLetter[tolower(board[cx*y+cy])][i].second[q])]);
				ul = ul && badsByLetter[board[cx*y+cy]][i].first.at(z) == tolower(board[(cx-(z-badsByLetter[tolower(board[cx*y+cy])][i].second[q]))*y+cy+(z-badsByLetter[tolower(board[cx*y+cy])][i].second[q])]);
				dr = dr && badsByLetter[board[cx*y+cy]][i].first.at(z) == tolower(board[(cx+(z-badsByLetter[tolower(board[cx*y+cy])][i].second[q]))*y+cy-(z-badsByLetter[tolower(board[cx*y+cy])][i].second[q])]);
				dl = dl && badsByLetter[board[cx*y+cy]][i].first.at(z) == tolower(board[(cx-(z-badsByLetter[tolower(board[cx*y+cy])][i].second[q]))*y+cy-(z-badsByLetter[tolower(board[cx*y+cy])][i].second[q])]);
			}
			if(right || left || up || down || ul || ur || dl || dr) {
				// COZ_END("localizedCheckExists")

				COZ_PROGRESS_NAMED("localized check exists")
					return true;
			}
		}
	}
	// COZ_END("localizedCheckExists")
	COZ_PROGRESS_NAMED("localized check exists")
		return false;
}
//
//
// bool newLocalized(const int dirs[8][2], const int & x, const int & y, const int & cx, const int & cy, const char* board, const std::vector<std::vector<std::pair<std::string, std::vector<int> > > > & badsByLetter) {
//   for(unsigned int c = 'a'; c < badsByLetter[board[cx*y+cy]].size(); c++) {
//     if(board[cx*y+cy] == badsByLetter[board[cx*y+cy]][c].first[0]) {
//       if(badsByLetter[board[cx*y+cy]][c].first.size() == 1) return true;
//         // int dirs[8][2] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};
//         for(int d = 0; d < 8; d++) {
//           int dx = dirs[d][0], dy = dirs[d][1];
//           int nx = cx + dx, ny = cy + dy;
//           unsigned int i = 1;
//           for (; i < badsByLetter[board[cx*y+cy]][c].first.size()  && nx >= 0 && nx < x && ny >= 0 && ny < y && board[nx * y + ny] == badsByLetter[board[cx*y+cy]][c].first[i]; i++, nx += dx, ny += dy);
//           if (i == badsByLetter[board[cx*y+cy]][c].first.size()) {
//               return true;
//           }
//
//         }
//     }
//   }
//   return false;
// }

bool globalCheckExists(const int& x, const int& y, const char* board, const std::string& word) {
	int wordLen = int(word.length());
	for (int cx = 0; cx < x; cx++) {
		for (int cy = 0; cy < y; cy++) {
			if (board[cx * y + cy] == word[0]) {
				if (wordLen == 1) {
					return true;
				}
				int dirs[8][2] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};
				for (int d = 0; d < 8; d++){
					int dx = dirs[d][0], dy = dirs[d][1];
					int nx = cx + dx, ny = cy + dy;
					int i = 1;
					for (; i < wordLen && nx >= 0 && nx < x && ny >= 0 && ny < y && board[nx * y + ny] == word[i]; i++, nx += dx, ny += dy);
					if (i == wordLen) {
						return true;
					}
				}
			}
		}
	}
	return false;
}


//NOTE: idea for faster all solutions, would also work for one solution.
//instead of going in each direction, go in each simultaneuously, doing on the fly error checking,
//and then go through each direction one by one. way less memory access, but might be slower hard to say. also allows us to
//cut out the z=0 case because we can do it as an initial check at each point
//also running just the if statements without editing the board *should* reduce net executions cuz can do it without if
//statements after (if it passed the case it doesn't need to check its not overwriting stuff)
//only concern is booleans. cant pass by reference because they're unique to each iter.

void better_all_solutions(const bool & eachTime, const int & x, const int & y,  const std::vector<std::string> & good, const std::vector<std::vector<std::pair<std::string, std::vector<int> > > > & badsByLetter, const std::vector<std::string> & bad, char* board, unsigned int & currentWord, std::unordered_set<std::string> & solutions) {

	// for(int i = 0; i < x*y; i++) {
	//   std::cout << board[i] << " ";
	// }
	// std::cout << std::endl;

	if(currentWord == good.size()) {
		for(int i = 0; i < int(bad.size()); i++) {
			if(globalCheckExists(x, y, board, bad[i])) return;
		}
		//COZ_BEGIN("final state")
		// std::cout << std::endl;
		int lastInstanceX = 0;
		int firstInstanceX = 100;

		bool goodBoard = true;
		for(int i = x-1; i >= 0; i--) {
			for(int j = y-1; j >= 0; j--) {
				if(board[i*y+j] == 0) {
					board[i*y+j] = 'A';
					firstInstanceX = i;
					if(lastInstanceX == 0) {
						lastInstanceX = i;
					}
					if(localizedCheckExists(x, y, i, j, board, badsByLetter)) goodBoard= false;
				}
			}
		}


		bool done = true;
		while(true) {

			if(goodBoard){
				//adding to set
				std::string temp = "Board:\n";
				for(int j = 0; j < y; j++) {
					temp += "  ";
					for(int i = 0; i < x; i++) {
						temp+=board[i*y+j];
					}
					temp += "\n";
				}
				solutions.insert(temp);
				temp = "Board:\n";
				for(int j = 0; j < y; j++) {
					temp += "  ";
					for(int i = 0; i < x; i++) {
						temp+=board[(x-i-1*y+j]);
					}
					temp += "\n";
				}
				solutions.insert(temp);
				temp = "Board:\n";
				for(int j = 0; j < y; j++) {
					temp += "  ";
					for(int i = 0; i < x; i++) {
						temp+=board[i*y+y-j-1];
					}
					temp += "\n";
				}
				solutions.insert(temp);
				temp = "Board:\n";
				for(int j = 0; j < y; j++) {
					temp += "  ";
					for(int i = 0; i < x; i++) {
						temp+=board[(x-i-1*y+y-j-1]);
					}
					temp += "\n";
				}
				solutions.insert(temp);
			}
			do {
				done = true;
				goodBoard = true;
				// std::cout << "iter";
				//increment
				for(int i = 0; i < x && done; i++) {
					for(int j = 0; j < y; j++) {
						if(board[i*y+j] == 'Z') {
							board[i*y+j] = 'A';
						} else if(isupper(board[i*y+j])) {
							board[i*y+j]++;
							done = false;
							break;
						}
					}
				}


				//check if good
				for(int i = firstInstanceX; i <= lastInstanceX && goodBoard; i++) {
					for(int j = 0; j < y; j++) {
						if(isupper(board[i*y+j]) && localizedCheckExists(x, y, i, j, board, badsByLetter)) {
							goodBoard = false;
							break;
						}
					}
				}

			} while(!goodBoard & !done);

			if(done) break;
		}
		for(int i = 0; i < x*y; i++) {
			if(isupper(board[i])) board[i] = 0;
		}
		COZ_PROGRESS
			return;
	}

	if(globalCheckExists(x, y, board, good[currentWord])) {
		++currentWord;
		better_all_solutions(eachTime, x, y, good, badsByLetter, bad, board, currentWord, solutions);
		--currentWord;
		COZ_PROGRESS
			return;
	}


	//DIRECTIONS:
	//UP   0
	//DOWN 1
	//RIGHT 2
	//LEFT  3
	//UP RIGHT 4
	//UP LEFT  5
	//DOWN RIGHT 6
	//DOWN LEFT  7
	std::bitset<8> directions;
	std::bitset<16> crossings;
	bool originZero;

	for(int i = 0; i < x; i++) {
		for(int j = 0; j < y; j++) {
			if(board[i*y+j] != 0 && board[i*y+j] != good[currentWord][0]) continue;
			directions = 0b11111111;
			if(i+int(good[currentWord].size()) > x) {
				directions[0] = 0;
				directions[4] = 0;
				directions[5] = 0;
			}
			if(i-int(good[currentWord].size()) <  -1) {
				directions[1] = 0;
				directions[6] = 0;
				directions[7] = 0;
			}
			if(j+int(good[currentWord].size()) > y) {
				directions[2] = 0;
				directions[4] = 0;
				directions[6] = 0;
			}
			if(j-int(good[currentWord].size()) <  -1) {
				directions[3] = 0;
				directions[5] = 0;
				directions[7] = 0;
			}

			// std:: cout << directions << std::endl;


			for(int z = 1; z < int(good[currentWord].size()); z++) {
				directions[0] = directions[0] && (board[(i+z)*y+j] == 0 || board[(i+z)*y+j] == good[currentWord][z]);
				directions[1] = directions[1] && (board[(i-z)*y+j] == 0 || board[(i-z)*y+j] == good[currentWord][z]);
				directions[2] = directions[2] && (board[i*y+j+z] == 0 || board[i*y+j+z] == good[currentWord][z]);
				directions[3] = directions[3] && (board[i*y+j-z] == 0 || board[i*y+j-z] == good[currentWord][z]);


				directions[4] = directions[4] && (board[(i+z)*y+j+z] == 0 || board[(i+z)*y+j+z] == good[currentWord][z]);
				directions[5] = directions[5] && (board[(i+z)*y+j-z] == 0 || board[(i+z)*y+j-z] == good[currentWord][z]);
				directions[6] = directions[6] && (board[(i-z)*y+j+z] == 0 || board[(i-z)*y+j+z] == good[currentWord][z]);
				directions[7] = directions[7] && (board[(i-z)*y+j-z] == 0 || board[(i-z)*y+j-z] == good[currentWord][z]);
				//NOTE: test this on and off
				if(directions == 0b00000000) break;
			}
			// std:: cout << directions.to_string() << std::endl << std::endl;
			originZero = board[i*y+j] == 0;
			board[i*y+j] = good[currentWord][0];
			bool shouldRecurse = true;
			if(directions[0]) {
				crossings = 0b0000000000000000;
				for(unsigned int z = 1; z < good[currentWord].size(); z++) {
					crossings[z] = board[(i+z)*y + j] == 0;
					board[(i+z)*y+j] = good[currentWord][z];
					if(eachTime && localizedCheckExists(x, y, i+z, j, board, badsByLetter)) {
						shouldRecurse = false;
						break;
					}
				}
				if(shouldRecurse) {
					++currentWord;
					better_all_solutions(eachTime, x, y, good, badsByLetter, bad, board, currentWord, solutions);
					--currentWord;
				}
				for(unsigned int z = 1; z < good[currentWord].size(); z++) {
					if(crossings.test(z)) board[(i+z)*y+j] = 0;
				}
			}
			if(directions[1]) {
				shouldRecurse = true;
				crossings = 0b0000000000000000;
				for(unsigned int z = 1; z < good[currentWord].size(); z++) {
					crossings[z] = board[(i-z)*y + j] == 0;
					board[(i-z)*y+j] = good[currentWord][z];
					if(eachTime && localizedCheckExists(x, y, i-z, j, board, badsByLetter)) {
						shouldRecurse = false;
						break;
					}

				}
				if(shouldRecurse) {
					++currentWord;
					better_all_solutions(eachTime, x, y, good, badsByLetter, bad, board, currentWord, solutions);
					--currentWord;
				}         for(unsigned int z = 1; z < good[currentWord].size(); z++) {
					if(crossings.test(z)) board[(i-z)*y+j] = 0;
				}
			}
			if(directions[2]) {
				shouldRecurse = true;
				crossings = 0b0000000000000000;
				for(unsigned int z = 1; z < good[currentWord].size(); z++) {
					crossings[z] = board[i*y + j + z] == 0;
					board[i*y+j+z] = good[currentWord][z];
					if(eachTime && localizedCheckExists(x, y, i, j+z, board, badsByLetter)) {
						shouldRecurse = false;
						break;
					}


				}
				if(shouldRecurse) {
					++currentWord;
					better_all_solutions(eachTime, x, y, good, badsByLetter, bad, board, currentWord, solutions);
					--currentWord;
				}
				for(unsigned int z = 1; z < good[currentWord].size(); z++) {
					if(crossings.test(z)) board[i*y+j+z] = 0;
				}
			}
			if(directions[3]) {
				shouldRecurse = true;
				crossings = 0b0000000000000000;
				for(unsigned int z = 1; z < good[currentWord].size(); z++) {
					crossings[z] = board[i*y + j - z] == 0;
					board[i*y+j-z] = good[currentWord][z];
					if(eachTime && localizedCheckExists(x, y, i, j-z, board, badsByLetter)) {
						shouldRecurse = false;
						break;
					}

				}
				if(shouldRecurse) {
					++currentWord;
					better_all_solutions(eachTime, x, y, good, badsByLetter, bad, board, currentWord, solutions);
					--currentWord;
				}
				for(unsigned int z = 1; z < good[currentWord].size(); z++) {
					if(crossings.test(z)) board[i*y+j-z] = 0;
				}
			}
			if(directions[4]) {
				shouldRecurse = true;
				crossings = 0b0000000000000000;
				for(unsigned int z = 1; z < good[currentWord].size(); z++) {
					crossings[z] = board[(i+z)*y+j+z] == 0;
					board[(i+z)*y+j+z] = good[currentWord][z];
					if(eachTime && localizedCheckExists(x, y, i+z, j+z, board, badsByLetter)) {
						shouldRecurse = false;
						break;
					}

				}
				if(shouldRecurse) {
					++currentWord;
					better_all_solutions(eachTime, x, y, good, badsByLetter, bad, board, currentWord, solutions);
					--currentWord;
				}
				for(unsigned int z = 1; z < good[currentWord].size(); z++) {
					if(crossings.test(z)) board[(i+z)*y+j+z] = 0;
				}
			}
			if(directions[5]) {
				shouldRecurse = true;
				crossings = 0b0000000000000000;
				for(unsigned int z = 1; z < good[currentWord].size(); z++) {
					crossings[z] = board[(i+z)*y+j-z] == 0;
					board[(i+z)*y+j-z] = good[currentWord][z];
					if(eachTime && localizedCheckExists(x, y, i+z, j-z, board, badsByLetter)) {
						shouldRecurse = false;
						break;
					}

				}
				if(shouldRecurse) {
					++currentWord;
					better_all_solutions(eachTime, x, y, good, badsByLetter, bad, board, currentWord, solutions);
					--currentWord;
				}
				for(unsigned int z = 1; z < good[currentWord].size(); z++) {
					if(crossings.test(z)) board[(i+z)*y+j-z] = 0;
				}
			}
			if(directions[6]) {
				shouldRecurse = true;
				crossings = 0b0000000000000000;
				for(unsigned int z = 1; z < good[currentWord].size(); z++) {
					crossings[z] = board[(i-z)*y+j+z] == 0;
					board[(i-z)*y+j+z] = good[currentWord][z];
					if(eachTime && localizedCheckExists(x, y, i-z, j+z, board, badsByLetter)) {
						shouldRecurse = false;
						break;
					}

				}
				if(shouldRecurse) {
					++currentWord;
					better_all_solutions(eachTime, x, y, good, badsByLetter, bad, board, currentWord, solutions);
					--currentWord;
				}
				for(unsigned int z = 1; z < good[currentWord].size(); z++) {
					if(crossings.test(z)) board[(i-z)*y+j+z] = 0;
				}
			}
			if(directions[7]) {
				shouldRecurse = true;
				crossings = 0b0000000000000000;
				for(unsigned int z = 1; z < good[currentWord].size(); z++) {
					crossings[z] = board[(i-z)*y+j-z] == 0;
					board[(i-z)*y+j-z] = good[currentWord][z];
					if(eachTime && localizedCheckExists(x, y, i-z, j-z, board, badsByLetter)) {
						shouldRecurse = false;
						break;
					}
				}
				if(shouldRecurse) {
					++currentWord;
					better_all_solutions(eachTime, x, y, good, badsByLetter, bad, board, currentWord, solutions);
					--currentWord;
				}
				for(unsigned int z = 1; z < good[currentWord].size(); z++) {
					if(crossings.test(z)) board[(i-z)*y+j-z] = 0;
				}
			}
			if(originZero) board[i*y+j] = 0;
		}
	}
	COZ_PROGRESS
}

void full_all_solutions(const int & x, const int & y, std::vector<std::string> & good, const std::vector<std::vector<std::pair<std::string, std::vector<int> > > > & badsByLetter, const std::vector<std::string> & bad, const std::string & fileout) {

	std::unordered_set<std::string> solutions;
	char board[x*y];
	for(int i = 0; i < x*y; i++) board[i] = 0;
	unsigned int currentWord = 0;
	bool eachTime = bad.size() != 0;
	int z;
	for(int i = 0; i < (x - int(good[currentWord].size())+1)/2+(x - int(good[currentWord].size())+1)%2; i++) {
		for(int j = 0; j < y/2+y%2; j++) {
			for(z = 0; z < int(good[currentWord].size()); z++) {
				board[(i+z)*y+j] = good[currentWord][z];
			}
			currentWord++;
			better_all_solutions(eachTime, x,y,good,badsByLetter, bad, board, currentWord, solutions);
			currentWord--;
			for(z = 0; z < int(good[currentWord].size()); z++) {
				board[(i+z)*y+j] = 0;
			}
		}
	}
	for(int i = 0; i < x/2+x%2; i++) {
		for(int j = 0; j < (y - int(good[currentWord].size()) +1)/2+(y - int(good[currentWord].size()) +1)%2; j++) {
			for(z = 0; z < int(good[currentWord].size()); z++) {
				board[i*y+j+z] = good[currentWord][z];
			}
			currentWord++;
			better_all_solutions(eachTime, x,y,good,badsByLetter, bad, board, currentWord, solutions);
			currentWord--;
			for(z = 0; z < int(good[currentWord].size()); z++) {
				board[i*y+j+z] = 0;
			}
		}
	}

	//diagonals
	for(int i = 0; i < (x - int(good[currentWord].size())+1)/2+(x - int(good[currentWord].size())+1)%2; i++) {
		for(int j = 0; j < y - int(good[currentWord].size()) + 1; j++) {
			for(z = 0; z < int(good[currentWord].size()); z++) {
				board[(i+z)*y+j+z] = good[currentWord][z];
			}
			currentWord++;
			better_all_solutions(eachTime, x,y,good,badsByLetter, bad, board, currentWord, solutions);
			currentWord--;
		}
	}

	std::ofstream out(fileout);
	if(solutions.size() == 0) out << "No solutions found";
	else out << solutions.size() << " solution(s)\n";
	for(std::unordered_set<std::string>::const_iterator iter = solutions.begin(); iter != solutions.end(); ++iter) {
		out << *iter;
	}
	COZ_PROGRESS
}
bool vecCmp(const std::string & A, const std::string & B) {
	return A.size() > B.size();
}
bool negCmp(const std::string & A, const std::string & B) {
	return A.size() < B.size();
}

int main(int argc, char** argv) {
	if(argc < 3) return 1;
	std::ifstream in_str(argv[1]);
	int x, y;
	in_str >> x >> y;
	std::vector<std::string> good;
	std::vector<std::string> bad;
	char pm;
	std::string in;
	while(!in_str.eof()) {
		in_str >> pm;
		in_str >> in;
		if((good.size() != 0 && in == good.back()) || (bad.size() != 0 && in == bad.back())) break;
		if(pm == '+') good.push_back(in);
		else bad.push_back(in);
	}

	std::sort(bad.begin(), bad.end(), negCmp);
	std::vector<std::vector<std::pair<std::string, std::vector<int> > > > badsByLetter('z'+1);
	for(unsigned int i = 0; i < bad.size(); i++) {
		for(int z = 0; z < int(bad[i].size()); z++) {
			bool found = false;
			for(unsigned int q = 0; q < badsByLetter[z].size(); q++) {
				if(badsByLetter[bad[i][z]][q].first == bad[i]) {
					found = true;
					badsByLetter[z][q].second.push_back(z);
					break;
				}
			}
			if(!found) {
				badsByLetter[bad[i][z]].push_back(std::pair<std::string, std::vector<int> >(bad[i], std::vector<int>(1, z)));
			}
		}
	}
	std::sort(good.begin(), good.end(), vecCmp);
	// for (int i = 0; i < good.size(); i++) {
	//   std::cout << good[i] << std::endl;
	// }
	// std::cout << "hi\n";
	// for(int i = 0; i < bad.size(); i++) {
	//   std::cout << bad[i] << std::endl;
	// }


	// for(int i = 0; i < good.size(); i++) std::cout << good[i] << std::endl;
	if(std::string(argv[3]) ==std::string("one_solution")) {
		// one_solution(x, y, good, bad, badsByLetter, argv[2]);
	} else {
		full_all_solutions(x, y, good, badsByLetter, bad, argv[2]);
	}
	return 0;
}




