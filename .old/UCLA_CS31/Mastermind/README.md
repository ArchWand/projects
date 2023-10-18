In order to understand how the skeleton works, let's look at the COLOR enumeration and the class Piece.  The COLOR enumeration is defined in the file Enums.h and is shown below:
This enumeration defines a value for every available color plus another value for any invalid value that might be entered.  This enumeration is fully defined and needs no changes to be made by CS31 students.

The Piece class represents a single played spot in one round of play in the Mastermind game.  Please note the class diagram shown below:

The constructor of this Piece class enables client code to create a Piece from a single character or from the first letter of a string.  By default, the Piece will have an NOTVALID COLOR value.  Once defined, this class enables client code to access the underlying COLOR or convert that single COLOR value into a matching string representation.  This class is fully defined and needs no changes to be made by CS31 students.  If you scroll down, you will find driver code I have supplied in the assignment instructions that show you how you can work with objects of the Piece class.

An ordered collection of four pieces played in a single round of play in the Mastermind game is represented by the class Move.  A Move is made up of a set of four Pieces, as documented in the UML diagram shown below:

Each Move holds an array of Pieces.  The length of the array is controlled by the constant REQUIREDLENGTH which is defined in the file Settings.h.  By default, each Piece will be NOTVALID.  Client code uses the operation setPiece( ... ) to specify a single piece of a Move object.  The parameter i should be an index value into the array of Pieces between 0 and REQUIREDLENGTH - 1.  If the parameter i is out of bounds, setPiece will throw a std::logic_error back at the calling code, rather than offset outside the valid bounds of the array.  Similarly, the operation getPiece( ... ) allows client code to access one individual Piece of this move.   The parameter i should be an index value into the array of Pieces between 0 and REQUIREDLENGTH - 1.  If the parameter i is out of bounds, getPiece will throw a std::logic_error back at the calling code, rather than offset outside the valid bounds of the array.   The operation to_string( ) returns the four colors that make up this Move as a string of four characters.  NOTVALID Pieces will be returned as the space character.   The operation setPieces( ... ) needs to be completed by CS31 students.  This operation should accept a four-character string and set each Piece of this Move object to the associated COLOR provided in the string parameter.  If the string parameter is not four letters long, this operation should throw a std::logic_error back at the calling code.  Please see the TODO comments in the class for further information.  If you scroll down, you will find driver code I have supplied in the assignment instructions that show you how you can work with objects of the Move class.

Each round of play in the Mastermind game needs to be scored, color-by-color, against the correct answer of the game.  This scoring gets performed by the class Score which works with the enumeration ANSWER.  The ANSWER enumeration is defined in the file Enums.h and is shown below:'

Once scored, each Piece in a Move will either be RIGHT, WRONG or MAYBE.  RIGHT means that exact color is in the same matching place when comparing the Score's Move to the correct answer.  WRONG means that exact color has no place in the correct answer when comparing the Score's Move to the correct answer.  MAYBE means that exact color is found in the correct answer but is currently located in the wrong position of the Score's Move.

Each Score holds an array of ANSWER.  The length of the array is controlled by the constant REQUIREDLENGTH which is defined in the file Settings.h.  Please note the class diagram shown below:

By default, each ANSWER value will be WRONG.  But if supplied two Moves, one for the played word and one for the correct answer, a Score constructor should properly define each ANSWER value accordingly.  This second constructor needs to be completed by CS31 students.  Please see the TODO comments in the class for further information.  Client code uses the operation getAnswer( ... ) to access an individual ANSWER value for the index parameter i.  The parameter i should be an index value into the array of ANSWER between 0 and REQUIREDLENGTH - 1.  If the parameter i is out of bounds, getAnswer( ... ) will throw a std::logic_error back at the calling code, rather than offset outside the valid bounds of the array.  A Score object can be converted into a string by calling tostring( ).  RIGHT answers will be printed as an 'R', WRONG answers will be printed as a '' and MAYBE answers will be printed as an 'M'.  This operation isExactMatch( ) needs to be completed by CS31 students.  It should return true when the ANSWER array holds all RIGHT values.  Please see the TODO comments in the class for further information. If you scroll down, you will find driver code I have supplied in the assignment instructions that show you how you can work with objects of the Score class.

The class Board is repetitively called to print out the state of the Mastermind game in a string table shown with the end of each round of play.  Each Board is made up of a set of Moves and Scores, as documented in the UML diagram shown below:

The length of the arrays of Score and Move is controlled by the constant TOTALROUNDSALLOWED which is defined in the file Settings.h.  Please note the class diagram shown below:

Each Board is tracking the current round and provides a trivial accessor for that member value.  A Move and Score gets supplied to the Board with calls to endRound( ... ) which should copy the two parameters into array data members at the index of the current round and then increment the current round value.

Accessors are available to retrieve a Move or Score.  In each case, the parameter round should be an index value into the array of Move or Score between 0 and TOTALROUNDSALLOWED - 1.  If the parameter round is out of bounds, these two getters should throw a std::logic_error back at the calling code, rather than offset outside the valid bounds of the array.  Please see the TODO comments in the class for further information.  If you scroll down, you will find driver code I have supplied in the assignment instructions that show you how you can work with objects of the Board class.

The Mastermind class plays the game with code found in main.cpp.  At all times, the state of the game will be one of the possible outcomes defined in the enumeration GAMEOUTCOME.  The GAMEOUTCOME enumeration is defined in the file Enums.h and is shown below:

The Mastermind class manages a Board, a winning Move with the correct answer as well as the current Move just recently played, as shown below:

The class Mastermind is used in main.cpp to run the overall game.  If you scroll down, you will find driver code I have supplied in the assignment instructions that show you how you can work with objects of the Mastermind class.  Please note the class diagram shown below:

CS31 Students need to complete determineGameOutcome( ).  Based on the state of the Board, this operation should return the proper GAMEOUTCOME value.  In addition, CS 31 Students need to complete endRound( ... ).  Based on the Move parameter, this operation should create a Score object, increment the round counter and supply this Score to this game's Board, saving this Score as the current score value and returning it back to the calling code.  Please see the TODO comments in the class for further information.

You are free to create additional public and private methods and data members as you see fit.  However, the test cases will only be driving the public methods of the classes provided in the skeleton code originally.

The source files you turn in will be these classes and a main routine. You can have the main routine do whatever you want, because we will rename it to something harmless, never call it, and append our own main routine to your file. Our main routine will thoroughly test your functions. You'll probably want your main routine to do the same. If you wish, you may write functions in addition to those required here. We will not directly call any such additional functions. If you wish, your implementation of a function required here may call other functions required here.