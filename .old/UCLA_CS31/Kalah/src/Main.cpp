#include "Player.h"
#include "Board.h"
#include "Side.h"
#include "Game.h"

#include <iostream>
#include <cassert>
using namespace std;

void doPlayerTests() {
	HumanPlayer hp("Marge");
	assert(hp.name() == "Marge" && hp.isInteractive());
	BadPlayer bp("Homer");
	assert(bp.name() == "Homer" && !bp.isInteractive());
	Board b(3, 2);
	b.setBeans(SOUTH, 2, 0);
	cout << "=========" << endl;
	int n = hp.chooseMove(b, SOUTH);
	cout << "=========" << endl;
	assert(n == 1 || n == 3);
	n = bp.chooseMove(b, SOUTH);
	assert(n == 1 || n == 3);
}

void doGameTests() {
	BadPlayer bp1("Bart");
	BadPlayer bp2("Homer");
	Board b(3, 0);
	b.setBeans(SOUTH, 1, 2);
	b.setBeans(NORTH, 2, 1);
	b.setBeans(NORTH, 3, 2);
	Game g(b, &bp1, &bp2);
	bool over;
	bool hasWinner;
	Side winner;
	//    Homer
	//   0  1  2
	// 0         0
	//   2  0  0
	//    Bart
	g.status(over, hasWinner, winner);
	assert(!over && g.beans(NORTH, POT) == 0 && g.beans(SOUTH, POT) == 0 &&
			g.beans(NORTH, 1) == 0 && g.beans(NORTH, 2) == 1 && g.beans(NORTH, 3) == 2 &&
			g.beans(SOUTH, 1) == 2 && g.beans(SOUTH, 2) == 0 && g.beans(SOUTH, 3) == 0);

	g.move(SOUTH);
	//   0  1  0
	// 0         3
	//   0  1  0
	g.status(over, hasWinner, winner);
	assert(!over && g.beans(NORTH, POT) == 0 && g.beans(SOUTH, POT) == 3 &&
			g.beans(NORTH, 1) == 0 && g.beans(NORTH, 2) == 1 && g.beans(NORTH, 3) == 0 &&
			g.beans(SOUTH, 1) == 0 && g.beans(SOUTH, 2) == 1 && g.beans(SOUTH, 3) == 0);

	g.move(NORTH);
	//   1  0  0
	// 0         3
	//   0  1  0
	g.status(over, hasWinner, winner);
	assert(!over && g.beans(NORTH, POT) == 0 && g.beans(SOUTH, POT) == 3 &&
			g.beans(NORTH, 1) == 1 && g.beans(NORTH, 2) == 0 && g.beans(NORTH, 3) == 0 &&
			g.beans(SOUTH, 1) == 0 && g.beans(SOUTH, 2) == 1 && g.beans(SOUTH, 3) == 0);

	g.move(SOUTH);
	//   1  0  0
	// 0         3
	//   0  0  1
	g.status(over, hasWinner, winner);
	assert(!over && g.beans(NORTH, POT) == 0 && g.beans(SOUTH, POT) == 3 &&
			g.beans(NORTH, 1) == 1 && g.beans(NORTH, 2) == 0 && g.beans(NORTH, 3) == 0 &&
			g.beans(SOUTH, 1) == 0 && g.beans(SOUTH, 2) == 0 && g.beans(SOUTH, 3) == 1);

	g.move(NORTH);
	//   0  0  0
	// 1         4
	//   0  0  0
	g.status(over, hasWinner, winner);
	assert(over && g.beans(NORTH, POT) == 1 && g.beans(SOUTH, POT) == 4 &&
			g.beans(NORTH, 1) == 0 && g.beans(NORTH, 2) == 0 && g.beans(NORTH, 3) == 0 &&
			g.beans(SOUTH, 1) == 0 && g.beans(SOUTH, 2) == 0 && g.beans(SOUTH, 3) == 0);
	assert(hasWinner && winner == SOUTH);
}

void customTests() {
   Board h(5,3); //board with 5 holes each with 3 beans
   assert(h.holes()==5); //test if holes work correctly
   assert(h.beans(Side::NORTH, 0)==0); //check for initial number of beans in pot to be zero
   assert(h.beans(Side::SOUTH, 0)==0);
   assert(h.beans(Side::NORTH, 1)==3); //check holes for initial bean number to be 3
   assert(h.beans(Side::NORTH, 3)==3);
   assert(h.beans(Side::NORTH, 5)==3);
   assert(h.beans(Side::NORTH, 6)==-1); //check when looking for beans in an invalid hole
   assert(h.beansInPlay(Side::NORTH)==15); //correct beansInPlay number
   assert(h.beansInPlay(Side::SOUTH)==15);
   assert(h.totalBeans()==30); //correct total beans number
   Side s;
   int end;
   Board z(6,15);
   z.sow(Side::NORTH, 1, s, end); //check for sowing
   assert(z.beans(Side::SOUTH, 0)==0); //test for if sowed correctly
   assert(z.beans(Side::NORTH, 0)==2);
   assert(end==1); //test for the right end spot
   assert(s==Side::SOUTH); //test for the right end side
   assert(z.beans(Side::NORTH, 1)==1); //test for correct number of beans sowed
   assert(z.beans(Side::NORTH, 4)==16);
   assert(z.beans(Side::SOUTH, 1)==17);
   Board c(6,20); //check for sowing with large number
   c.sow(Side::SOUTH, 2, s, end);
   assert(c.beans(Side::NORTH, 0)==0); //no beans should be sowed into north's pot
   assert(end==5); //check for correct sowing
   assert(s==Side::NORTH);
   assert(c.beans(Side::NORTH, 3)==21);
   assert(c.beans(Side::SOUTH, 2)==1);
   Board d(5, 4);
   assert(d.moveToPot(Side::NORTH, 1, Side::SOUTH)==true); //test for moveToPot
   assert(d.beans(Side::NORTH, 1)==0);
   assert(d.beans(Side::SOUTH,0)==4);
   assert(d.moveToPot(Side::NORTH, 0, Side::SOUTH)==false); //test for moveToPot faulty
   assert(d.beans(Side::NORTH, 1)==0); //nothing should be changed
   assert(d.beans(Side::SOUTH,0)==4);
   assert(d.moveToPot(Side::NORTH, 1, Side::SOUTH)==true); //test for moveToPot
   assert(d.beans(Side::NORTH, 1)==0); //no beans should be moved
   assert(d.beans(Side::SOUTH,0)==4);
   assert(d.setBeans(Side::SOUTH, 0, -10)==false); //test invalid num for set beans
   assert(d.setBeans(Side::SOUTH, 0, 0)==true); //valid set bean number
   assert(d.beans(Side::SOUTH,0)==0);
   assert(d.setBeans(Side::SOUTH, 6, 5)==false); //test invalid num for set beans
   Board aa(d); //check if copy constructor works correctly
   assert(aa.totalBeans()==36); //check if number of beans corresponds to board d
   assert(aa.beansInPlay(Side::SOUTH)==20);
   assert(aa.beansInPlay(Side::NORTH)==16);
   assert(aa.beans(Side::SOUTH, 0)==0);
   assert(aa.moveToPot(Side::SOUTH, 1, Side::NORTH));
   assert(aa.beans(Side::NORTH, 0)==4); //should be changed
   assert(d.beans(Side::NORTH, 0)==0); //should not be changed
   c = aa; //test if assignment operator works properly
   assert(c.beans(Side::NORTH, 0)==4); //should be the same as aa
   assert(c.setBeans(Side::NORTH, 1, 10)==true);
   assert(c.beans(Side::NORTH, 1)==10); //c should be updated
   assert(aa.beans(Side::NORTH, 1)==0); //aa should not change

   //test cases for player
   HumanPlayer e("Josh");
   assert(e.isInteractive()==true); //human player should be interactive
   assert(e.name()=="Josh"); //test if name works correctly
   BadPlayer f("Josh");
   assert(f.isInteractive()==false); //bad player should not be interactive
   assert(f.name()=="Josh"); //test if name works correctly
   assert(f.chooseMove(d, Side::NORTH)>1&&f.chooseMove(d, Side::NORTH)<=5); //choose move needs to choose move within range
   SmartPlayer g("Josh");
   assert(g.isInteractive()==false); //smart player should not be interactive
   assert(g.name()=="Josh"); //test if name works correctly
   assert(g.chooseMove(d, Side::NORTH)>1&&g.chooseMove(d, Side::NORTH)<=5); //choose move needs to choose move within range

   //test cases for Game
   Game i(c, &f, &g);
   bool over, haswinner=false;
   Side winner;
   i.status(over, haswinner, winner); //test for status
   assert(over==false);
   assert(haswinner==false);
   c.setBeans(Side::SOUTH, 0, 4); //set up for a tied scenario
   for(int k=0; k<c.holes(); k++){
	   c.setBeans(Side::NORTH, k+1, 0);
	   c.setBeans(Side::SOUTH, k+1, 0);
   }
   Game j(c, &f, &g);
   j.status(over, haswinner, winner); //check status on tied scenario
   assert(over==true);
   assert(haswinner==false); //should be no winners
   c.setBeans(Side::SOUTH, 0, 5); //set up for scenario where there is a winner
   Game k(c, &f, &g);
   k.status(over, haswinner, winner); //check status on no tied scenario
   assert(over==true);
   assert(haswinner==true); //should be a winner
   assert(winner==Side::SOUTH);
   c.setBeans(Side::NORTH, 1, 5);
   Game l(c, &f, &g);
   l.display();
}

// Test BadPlayer
void dumbTests() {
	// (BadPlayer always chooses the leftmost option)
	// Board generated randomly, by fair dice roll
	Board b(6, 4);
	b.setBeans(Side::NORTH, 0, 4);
	b.setBeans(Side::NORTH, 1, 6);
	b.setBeans(Side::NORTH, 2, 1);
	b.setBeans(Side::NORTH, 3, 3);
	b.setBeans(Side::NORTH, 4, 4);
	b.setBeans(Side::NORTH, 5, 4);
	b.setBeans(Side::SOUTH, 0, 3);
	b.setBeans(Side::SOUTH, 1, 6);
	b.setBeans(Side::SOUTH, 2, 5);
	b.setBeans(Side::SOUTH, 3, 4);
	b.setBeans(Side::SOUTH, 4, 4);
	b.setBeans(Side::SOUTH, 5, 4);

	SmartPlayer p1("dunce1");
	SmartPlayer p2("dunce2");
	Game g(b, &p1, &p2);
	g.display();

	g.move(SOUTH);
	g.display();
	/* assert(g.beans(SOUTH, 1) == 0); */
	g.move(NORTH);
	g.display();
	/* assert(g.beans(NORTH, 1) == 0); */
	g.move(SOUTH);
	g.display();
	/* assert(g.beans(SOUTH, 1) == 0); */
	g.move(NORTH);
	g.display();
	/* assert(g.beans(NORTH, 2) == 0); */
	g.move(SOUTH);
	g.display();
	/* assert(g.beans(SOUTH, 2) == 0); */
	g.move(NORTH);
	g.display();
	/* assert(g.beans(NORTH, 1) == 0); */
	g.move(SOUTH);
	g.display();
	/* assert(g.beans(SOUTH, 3) == 0); */
	g.move(NORTH);
	g.display();
	/* assert(g.beans(NORTH, 3) == 0); */
	g.play();
}

// Test SmartPlayer
void smartTests() {
	Board b(6, 0);
	// Game tree in spec sheet
	b.setBeans(Side::NORTH, 0, 22);
	b.setBeans(Side::NORTH, 2, 1);
	b.setBeans(Side::NORTH, 5, 2);
	b.setBeans(Side::SOUTH, 0, 20);
	b.setBeans(Side::SOUTH, 3, 2);
	b.setBeans(Side::SOUTH, 5, 1);
	SmartPlayer p1("p1");
	SmartPlayer p2("p2");
	Game g(b, &p1, &p2);
	g.move(SOUTH);
	g.display();
	assert(g.beans(SOUTH, 3) == 0);
	assert(g.beans(SOUTH, 4) == 1);
	assert(g.beans(SOUTH, 5) == 2);
	g.move(NORTH);
	g.display();
	assert(g.beans(NORTH, 1) == 1);
	assert(g.beans(NORTH, 2) == 0);
	g.move(SOUTH);
	g.display();
}

int main() {
	// doPlayerTests();
	doGameTests();
	customTests();
	dumbTests();
	smartTests();
	cout << "Passed all tests" << endl;
}
