#ifndef _TRAIN_H_
#define _TRAIN_H_

// =======================================================================
//
// IMPORTANT NOTE: Do not modify this file
//
// =======================================================================
//
// The TrainCar class is a simple node in a classic doubly-linked list
// data structure.  Each TrainCar has a type (stored as a char), a
// unique ID, a weight, and next & prev pointers to neighboring
// TrainCars.

#include <cstddef>

class TrainCar {
	public:
		enum CarType { ENGINE, FREIGHT, PASSENGER, DINING, SLEEPING };

		// static helper functions for construction
		// (the constructor is private)
		static TrainCar* MakeEngine()               { return new TrainCar(ENGINE,150);     }
		static TrainCar* MakeFreightCar(int weight) { return new TrainCar(FREIGHT,weight); }
		static TrainCar* MakePassengerCar()         { return new TrainCar(PASSENGER,50);   }
		static TrainCar* MakeDiningCar()            { return new TrainCar(DINING,50);      }
		static TrainCar* MakeSleepingCar()          { return new TrainCar(SLEEPING,50);    }

		// ACCESSORS
		int getID() const           { return id; }
		int getWeight() const       { return weight; }

		bool isEngine() const       { return (type == ENGINE);    }
		bool isFreightCar() const   { return (type == FREIGHT);   }
		bool isPassengerCar() const { return (type == PASSENGER); }
		bool isDiningCar() const    { return (type == DINING);    }
		bool isSleepingCar() const  { return (type == SLEEPING);  }

	private:
		// private constructor
		TrainCar(CarType t, int w) : type(t), weight(w), prev(NULL), next(NULL) {
			// each train car has a unique identifer, 
			// numbered sequentially, starting at 100
			static int next_id = 100;
			id = next_id;
			next_id++;
		}

		// REPRESENTATION
		// these three member variables cannot be edited after object construction
		int id;
		CarType type;
		int weight;
	public:
		// these two member variables can be publicly read & edited
		TrainCar* prev;
		TrainCar* next;
};


// =======================================================================
//
// IMPORTANT NOTE: Do not modify this file
//
// =======================================================================

// These helper functions are implemented in main.cpp

void SanityCheck(TrainCar* train);
void PrintTrain(TrainCar* train);

// There are a number of additional functions used in main.cpp that
// you need to declare and implement.  Study main.cpp and the provided
// output to determine the arguments, return type, and overall
// behavior.

// Instead of editing this file directly, place your prototypes for
// additional functions in this file:

#include "traincar_prototypes.h"

// And implement these functions in "traincar.cpp"

// =======================================================================
//
// IMPORTANT NOTE: Do not modify this file
//
// =======================================================================

#endif
