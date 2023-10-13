//
//  Score.cpp
//

#include "Score.h"
#include "Enums.h"
#include "Settings.h"
#include <stdexcept>

namespace cs31 {
	// setup a default score - all WRONG ANSWER's
	Score::Score() {
		for( int i = 0; i < REQUIREDLENGTH; i++ ) {
			array[ i ] = WRONG;
		}
	}

	// Check if the answer should be maybe
	bool has_matched_piece(Move &move, Move &answer, int piece) {
		int count = 0;
		COLOR c = move.getPiece(piece).getColor();

		// Count the number of matching colors in the answer
		for (int i = 0; i < REQUIREDLENGTH; i++) {
			if (c == answer.getPiece(i).getColor()
					&& move.getPiece(i).getColor() != answer.getPiece(i).getColor())
			{ count++; }
		}

		// Subtract the number of occurences of the color
		// in the move, up to but not including the current piece.
		// Exclude any pieces that are correct.
		for (int i = 0; i < piece; i++) {
			if (c == move.getPiece(i).getColor())
			{ count--; }
		}

		return count > 0;
	}

	// TODO comparing the played move to the answer move,
	//      build the ANSWER array of this Score
	Score::Score(Move move, Move answer) {
		for (int i = 0; i < REQUIREDLENGTH; i++) {
			if (move.getPiece(i).getColor() == answer.getPiece(i).getColor()) {
				array[i] = RIGHT;
			} else if (has_matched_piece(move, answer, i)) {
				array[i] = MAYBE;
			} else {
				array[i] = WRONG;
			}
		}
	}

	// trivial getter but throw logic_error if the index is out of range
	ANSWER Score::getAnswer( int i ) {
		if (i >= 0 && i < REQUIREDLENGTH)
			return( array[ i ] );
		throw std::logic_error( "invalid i value" );
	}

	// stringify this Score
	std::string Score::to_string() const {
		std::string s = "";
		int mCount = 0;
		int rCount = 0;
		for (int i = 0; i < REQUIREDLENGTH; i++) {
			switch( array[i] ) {
				case WRONG:
					// wrongs should not be printed at all
					s += "_";
					break;
				case RIGHT:
					rCount++;
					s += "R";
					break;
				case MAYBE:
					mCount++;
					s += "M";
					break;
			}
		}
		return( s );
	}

	// TODO is the ANSWER array all RIGHT ANSWER's?
	bool Score::isExactMatch() const {
		for (int i = 0; i < REQUIREDLENGTH; i++) {
			if (array[i] != RIGHT)
				return false;
		}
		return true;
	}
}

