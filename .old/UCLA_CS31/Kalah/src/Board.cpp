#include "Board.h"
#include <iostream>
 
Board::Board(int nHoles, int nInitialBeansPerHole) {
	//set holes value
	if (nHoles > 1) {
		m_holes = nHoles;
	}
	else {
		m_holes = 1;
	}
	//set beans per hole values
	if (nInitialBeansPerHole > -1) {
		m_InitialBeansPerHole = nInitialBeansPerHole;
	}
	else {
		m_InitialBeansPerHole = 0;
	}
	//make two arrays for each side including pot
	m_northHoles = new int[m_holes + 1];
	m_southHoles = new int[m_holes + 1];
	m_northHoles[0] = 0; //track pot in first slot
	m_southHoles[0] = 0; //track pot in first slot
	//put beans in all holes
	for (int i = 1; i <= m_holes; i++) {
		m_northHoles[i] = m_InitialBeansPerHole;
		m_southHoles[i] = m_InitialBeansPerHole;
	}
}

Board::Board(const Board& other) {
	//copy over from other
	m_holes = other.m_holes;
	m_InitialBeansPerHole = other.m_InitialBeansPerHole;
	m_northHoles = new int[m_holes + 1];
	m_southHoles = new int[m_holes + 1];
	//copy elements of other
	for (int i = 0; i <= m_holes; i++) {
		m_northHoles[i] = other.m_northHoles[i];
		m_southHoles[i] = other.m_southHoles[i];
	}
}

Board& Board::operator=(const Board& other) {
	//check aliasing
	if (this != &other) {
		//copy from other
		m_holes = other.m_holes;
		m_InitialBeansPerHole = other.m_InitialBeansPerHole;
		delete[] m_northHoles;
		delete[] m_southHoles;
		m_northHoles = new int[m_holes + 1];
		m_southHoles = new int[m_holes + 1];
		//copy elements of other
		for (int i = 0; i <= m_holes; i++) {
			m_northHoles[i] = other.m_northHoles[i];
			m_southHoles[i] = other.m_southHoles[i];
		}
	}
	return *this;
}

Board::~Board() {
	//destroy both arrays
	delete[] m_northHoles;
	delete[] m_southHoles;
}

int Board::holes() const {
	return m_holes;
}

int Board::beans(Side s, int hole) const {
	//north side
	if (s == NORTH) {
		//hole is valid
		if (hole > -1 && hole <= m_holes) {
			return m_northHoles[hole];
		}
	}
	//south side
	if (s == SOUTH) {
		//hole is valid
		if (hole > -1 && hole <= m_holes) {
			return m_southHoles[hole];
		}
	}
	return -1;
}

int Board::beansInPlay(Side s) const {
	//north side
	if (s == NORTH) {
		int NBeans = 0;
		//count all beans in north
		for (int i = 1; i <= m_holes; i++) {
			NBeans += m_northHoles[i];
		}
		return NBeans;
	}
	//south side
	if (s == SOUTH) {
		int SBeans = 0;
		//count all beans in south
		for (int i = 1; i <= m_holes; i++) {
			SBeans += m_southHoles[i];
		}
		return SBeans;
	}
	return 0;
}

int Board::totalBeans() const {
	int totalBeans = 0;
	//sum all beans in holes and pots
	for (int i = 0; i <= m_holes; i++) {
		totalBeans = totalBeans + m_northHoles[i] + m_southHoles[i];
	}
	return totalBeans;
}

void Board::display() {
	std::cout << "====================" << std::endl;

	//display north side
	std::cout << m_northHoles[0] << " N: ";
	for (int i = 1; i <= m_holes; i++) {
		std::cout << m_northHoles[i] << " ";
	}
	std::cout << std::endl;

	//display south side
	std::cout << m_southHoles[0] << " S: ";
	for (int i = 1; i <= m_holes; i++) {
		std::cout << m_southHoles[i] << " ";
	}
	std::cout << std::endl;
	std::cout << "====================" << std::endl;
}

bool Board::sow(Side s, int hole, Side& endSide, int& endHole) {
	// Invalid hole value
	if (hole > holes() || hole <= 0) {
		return false;
	}

	// Grab the beans
	int hand = beans(s, hole);
	setBeans(s, hole, 0);

	endSide = s;
	endHole = hole;
	while (hand > 0) {
		// Move to next hole
		if (endSide == NORTH) {
			endHole--;
			// Reached end of north side
			if (endHole == 0) {
				// Switch sides
				endSide = SOUTH;
				endHole = 0;

				if (s == NORTH) { // Add to north pot
					m_northHoles[0]++;
					hand--;
				}
				continue;
			}

			m_northHoles[endHole]++;
			hand--;
		} else {
			endHole++;
			// Reached end of south side
			if (endHole > holes()) {
				// Switch sides
				endSide = NORTH;
				endHole = holes()+1;

				if (s == SOUTH) { // Add to south pot
					m_southHoles[0]++;
					hand--;
				}
				continue;
			}

			m_southHoles[endHole]++;
			hand--;
		}
	}

	return true;
}

bool Board::moveToPot(Side s, int hole, Side potOwner) {
	//invalid hole value
	if (hole > m_holes || hole <= 0) {
		return false;
	}
	if (s == NORTH) {
		//add beans to potowner
		if (potOwner == NORTH) {
			m_northHoles[0] += m_northHoles[hole];
		}
		else {
			m_southHoles[0] += m_northHoles[hole];
		}
		//remove beans
		m_northHoles[hole] = 0;
	}
	else {
		//add beans to potowner
		if (potOwner == NORTH) {
			m_northHoles[0] += m_southHoles[hole];
		}
		else {
			m_southHoles[0] += m_southHoles[hole];
		}
		//remove beans
		m_southHoles[hole] = 0;
	}
	return true;
}

bool Board::setBeans(Side s, int hole, int beans) {
	//invalid hole value or bean value
	if (hole > m_holes || hole < 0 || beans < 0) {
		return false;
	}
	if (s == NORTH) {
		//north hole
		if (hole != 0) {
			//same value
			if (this->beans(NORTH, hole) == beans) {
				return true;
			}
			//set beans to hole
			else {
				m_northHoles[hole] = beans;
			}
		}
		//north pot
		else {
			//same value
			if (this->beans(NORTH, 0) == beans) {
				return true;
			}
			//set beans to pot
			else {
				m_northHoles[0] = beans;
			}
		}
	}
	else if (s == SOUTH) {
		//south hole
		if (hole != 0) {
			//same value
			if (this->beans(SOUTH, hole) == beans) {
				return true;
			}
			//set beans to hole
			else {
				m_southHoles[hole] = beans;
			}
		}
		//south pot
		else {
			//same value
			if (this->beans(SOUTH, 0) == beans) {
				return true;
			}
			//set beans to pot
			else {
				m_southHoles[0] = beans;
			}
		}
	}
	return true;
}
