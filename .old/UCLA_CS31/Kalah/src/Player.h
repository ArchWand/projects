#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <string>

#include "Board.h"
#include "Side.h"
using namespace std;

class Player {
	public:
		Player(string name);
		//Create a Player with the indicated name.
			string name() const;
		//Return the name of the player.
			virtual bool isInteractive() const;
		//Return false if the player is a computer player.Return true if the player is human.Most kinds of players will be computer players.
			virtual int chooseMove(const Board & b, Side s) const = 0;
		//Every concrete class derived from this class must implement this function so that if the player were to be playing side sand had to make a move given board b, the function returns the move the player would choose.If no move is possible, return −1.
			virtual ~Player();
		//Since this class is designed as a base class, it should have a virtual destructor.

	private:
		string m_name;
};

class HumanPlayer : public Player {
	public:
		HumanPlayer(string name);
		bool isInteractive() const;
		int chooseMove(const Board& b, Side s) const;
		~HumanPlayer();
};

class BadPlayer : public Player {
	public:
		BadPlayer(string name);
		int chooseMove(const Board& b, Side s) const;
		~BadPlayer();
};

class SmartPlayer: public Player {
	public:
		SmartPlayer(string name);
		int chooseMove(const Board& b, Side s) const;
		~SmartPlayer();
	private:
		int evaluate(const Board& b) const;
		void chooseMove(const Board& b, Side s, int depth, int& besthole, int& value) const;
};
#endif
