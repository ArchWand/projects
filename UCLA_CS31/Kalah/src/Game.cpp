#include "Game.h"
#include "Board.h"
#include "Player.h"
#include "Side.h"

#include <iostream>
#include <string>

using namespace std;

Game::Game(const Board& b, Player* south, Player* north)
	: m_board(b), m_north(north), m_south(south) {}

void Game::display() const {
    int holes = m_board.holes();
    //north name
    cout << "\t " << m_north->name() << endl << "    ";
    //display north holes
    for (int i = 1; i <= holes; i++) {
        cout << beans(NORTH, i) << "  ";
    }
    //display north pot
    cout << endl << "  " << beans(NORTH, 0); 
    for (int i = 0; i < holes; i++) {
        cout << "   ";
    }
    //display south pot
    cout << beans(SOUTH, 0) << endl << "    "; 
    //display south holes
    for (int i = 1; i <= holes; i++) {
        cout << beans(SOUTH, i) << "  ";
    }
    //south name
    cout << endl << "\t " << m_south->name() << endl;
}

void Game::status(bool& over, bool& hasWinner, Side& winner) const {
    //game is not over
    if (m_board.beansInPlay(NORTH) > 0 && m_board.beansInPlay(SOUTH) > 0) {
        over = false;
        return;
    }
    //tied game
    if (m_board.beans(NORTH, 0) + m_board.beansInPlay(NORTH) == m_board.beans(SOUTH, 0) + m_board.beansInPlay(SOUTH)) {
        over = true;
        hasWinner = false;
        return;
    }
    //north wins
    if (m_board.beans(NORTH, 0) + m_board.beansInPlay(NORTH) > m_board.beans(SOUTH, 0) + m_board.beansInPlay(SOUTH)) {
        over = true;
        hasWinner = true;
        winner = NORTH;
        return;
    }
    //south wins
    if (m_board.beans(NORTH, 0) + m_board.beansInPlay(NORTH) < m_board.beans(SOUTH, 0) + m_board.beansInPlay(SOUTH)) {
        over = true;
        hasWinner = true;
        winner = SOUTH;
        return;
    }
}

bool Game::move(Side s) {
    Player *P1, *P2;
    int move, eh;
    Side es;
    //north side
    if (s == NORTH) {
        P1 = m_north;
        P2 = m_south;
        move = m_north->chooseMove(m_board, s);
    }
    //south side
    else {
        P1 = m_south;
        P2 = m_north;
        move = m_south->chooseMove(m_board, s);
    }
    //implement the move
    m_board.sow(s, move, es, eh); 
    //no beans to play
    if (m_board.beansInPlay(s) == 0) {
        cout << P1->name() << " has no beans left to sow." << endl << "Sweeping remainimg beans into " << P2->name() << "'s pot." << endl;
        //move opponents beans to pot
        for (int i = 1; i <= m_board.holes(); i++) {
            m_board.moveToPot(opponent(s), i, opponent(s));
        }
        return false;
    }
    //last bean placed in pot
    if (es == s && eh == 0) {
        display();
        //gets another turn
        if (s == NORTH) {
            cout << m_north->name() << " gets another turn." << endl;
        }
        else {
            cout << m_south->name() << " gets another turn." << endl;
        }
    }
    //move items to pot if capture
    if (es == s && m_board.beans(s, eh) == 1 && beans(opponent(s), eh) != 0) {
        m_board.moveToPot(s, eh, s);
        m_board.moveToPot(opponent(s), eh, s);
    }
    return true;
}

void Game::play() {
    Side s = SOUTH, winner;
    bool over, hasWinner;
    display();
    move(s);
    display();
    status(over, hasWinner, winner);
    //game is still going
    while (!over) {
        //prompt players with enter
        if (!(m_north->isInteractive()) && !(m_south->isInteractive())) {
            cout << "Press ENTER to continue";
            cin.ignore(10000, '\n');
        }
        s = opponent(s);
        move(s);
        display();
        status(over, hasWinner, winner);
    }
    //if game is not tied
    if (hasWinner) {
        //print correct winner
        if (winner == NORTH) {
            cout << "The winner is " << m_north->name() << "." << endl;
        }
        else {
            cout << "The winner is " << m_south->name() << "." << endl;
        }
    }
    //tied game
    else {
        cout << "The game resulted in a tie." << endl;
    }
}

int Game::beans(Side s, int hole) const {
    return m_board.beans(s, hole);
}
