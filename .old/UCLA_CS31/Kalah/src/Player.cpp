#include "Player.h"
#include <string>
#include <iostream>
using namespace std;

#define MAXDEPTH 10
#define INT_MAX 2147483647
#define INT_MIN -2147483648

// Base player
Player::Player(string name)
	: m_name(name) {}
string Player::name() const { return m_name; }
bool Player::isInteractive() const { return false; }
Player::~Player() {}


// ====================
// Human Player
// ====================
HumanPlayer::HumanPlayer(string name): Player(name) {}
HumanPlayer::~HumanPlayer() {}
bool HumanPlayer::isInteractive() const { return true; }

int HumanPlayer::chooseMove(const Board& b, Side s) const {
	//cannot choose move
	if (b.beansInPlay(s) == 0) {
		return -1;
	}
	int hole;
	cout << "Select a hole, " << name() << ": ";
	cin >> hole;
	if (hole < 1 || hole > b.holes() || b.beans(s, hole) == 0) {
		//empty hole
		if (b.beans(s, hole) == 0) {
			cout << "There are no beans in that hole." << endl;
		}
		else {
			//valid holes
			if (b.holes() != 1) {
				cout << "The hole number must be from 1 to " << b.holes() << "." << endl;
			}
			//one hole
			else {
				cout << "The hole number must be 1." << endl;
			}
		}
		return chooseMove(b, s);
	}
	else {
		return hole;
	}
}


// ====================
// Bad Player
// ====================
BadPlayer::BadPlayer(string name): Player(name) {}
BadPlayer::~BadPlayer() {}

int BadPlayer::chooseMove(const Board& b, Side s) const {
	//random move
	for (int i = 1; i <= b.holes(); i++) {
		if (b.beans(s, i) != 0) {
			return i;
		}
	}
	return -1;
}


// ====================
// Smart Player
// ====================
SmartPlayer::SmartPlayer(string name): Player(name) {}

int SmartPlayer::chooseMove(const Board& b, Side s) const {
	int besthole, value, depth = 0;
	chooseMove(b, s, depth, besthole, value);
	return besthole;
}

int SmartPlayer::evaluate(const Board &b) const {
	int sPot = b.beans(SOUTH, 0),
		opPot = b.beans(NORTH, 0);

	// If the game is over
	if (b.beansInPlay(NORTH) == 0 || b.beansInPlay(SOUTH) == 0) {
		// Collate remaining beans
		sPot += b.beansInPlay(SOUTH);
		opPot += b.beansInPlay(NORTH);

		if (sPot > opPot) { return INT_MAX; } // If I win
		else if (sPot < opPot) { return INT_MIN; } // If I lose
		else { return 0; } // If the game is a tie
	}

	return (sPot - opPot) * 100; // Heuristic: pot difference
}

void SmartPlayer::chooseMove(const Board& b, Side s, int depth, int& besthole, int& value) const {
	besthole = -1;
	value = INT_MIN;

	// Base case
	if (b.beansInPlay(s) == 0) {
		besthole = -1;
		value = evaluate(b);
		return;
	}
	if (depth == MAXDEPTH) {
		besthole = -1;
		value = evaluate(b);
		return;
	}

	// Recursive call
	for (int i = 1; i <= b.holes(); i++) {
		if (b.beans(s, i) == 0) { continue; } // Skip empty holes

		Board copy(b);
		Side endSide;
		int endHole;
		copy.sow(s, i, endSide, endHole);

		int nextHole, nextValue;
		Side nextPlayer;
		int nextDepth = depth;
		if (endSide == s && endHole == 0) {
			nextPlayer = s;
		} else {
			nextPlayer = opponent(s);
			nextDepth++;
		}
		chooseMove(copy, nextPlayer, nextDepth, nextHole, nextValue);

		if (nextValue > value) {
			besthole = i;
			value = nextValue;
		}
	}
}

SmartPlayer::~SmartPlayer() {
}
