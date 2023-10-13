// =======================================================================
//
// IMPORTANT NOTE: You should edit this file
//
// =======================================================================

#include <algorithm>
#include <iostream>
#include <iomanip>
#include <string>
#include <cassert>
#include <cmath>
#include <cstdlib>

#include "traincar.h"
#include "traincar_prototypes.h"

// A constant to add to the minimum speed in calculations.
// Ensure that the algorithm has a bit of breathing room.
#define BUFF 20

// =======================================================================
// =======================================================================
//
//  HERE'S WHERE YOU SHOULD IMPLEMENT THE FUNCTIONS YOU PROTOTYPED IN
//  THE "traincar_prototypes.h" FILE.
//

TrainCar* start_of(TrainCar* train) {
	if (train == nullptr) { return nullptr; }
	while (train->prev) {
		train = train->prev;
	}
	return train;
}

TrainCar* end_of(TrainCar* train) {
	if (train == nullptr) { return nullptr; }
	while (train->next) {
		train = train->next;
	}
	return train;
}

int train_weight(TrainCar* train) {
	int weight = 0;
	for (train = start_of(train); train; train = train->next) {
		weight += train->getWeight();
	}
	return weight;
}

void PushBack(TrainCar* &train, TrainCar* newCar) {
	if (train == nullptr) {
		train = newCar;
	} else {
		TrainCar* end = end_of(train);
		end->next = newCar;
		newCar->prev = end;
	}
}

void DeleteAllCars(TrainCar* &trainCar) {
	if (trainCar == nullptr) { return; }

	trainCar = start_of(trainCar);
	// Delete the train
	while (trainCar) {
		TrainCar* next = trainCar->next;
		delete trainCar;
		trainCar = next;
	}
}

void TotalWeightAndCountCars(TrainCar *train,
		int &total_weight, int &num_engines, int &num_freight_cars,
		int &num_passenger_cars, int &num_dining_cars, int &num_sleeping_cars
		) {
	total_weight = num_engines = num_freight_cars = num_passenger_cars = num_dining_cars = num_sleeping_cars = 0;

	for (train = start_of(train); train; train = train->next) {
		total_weight += train->getWeight();
		if (train->isEngine())            { num_engines++; }
		else if (train->isFreightCar())   { num_freight_cars++; }
		else if (train->isPassengerCar()) { num_passenger_cars++; }
		else if (train->isDiningCar())    { num_dining_cars++; }
		else if (train->isSleepingCar())  { num_sleeping_cars++; }
	}
}

int weight_of(TrainCar* train) {
	int weight = 0;
	for (train = start_of(train); train; train = train->next) {
		weight += train->getWeight();
	}
	return weight;
}

float calc_speed(int engine_count, int weight) {
	return 9.375 * engine_count * 3000 / weight;
}

float CalculateSpeed(TrainCar* train) {
	int weight = 0, engine_count = 0;

	for (train = start_of(train); train; train = train->next) {
		engine_count += train->isEngine();
		weight += train->getWeight();
	};

	return calc_speed(engine_count, weight);
}

int weight_for_speed(int engine_count, float speed) {
	return 9.375 * engine_count * 3000 / speed;
}

int DistanceToDiningCar(TrainCar *train) {
	TrainCar *current = train,
			 *next = train->next;
	int min_dist = 2147483647;

	for (int i = 1; next; i++) {
		if (current->isEngine() || current->isFreightCar()) { break; }
		if (next->isDiningCar()) { min_dist = i; }
		current = next;
		next = next->next;
	}

	current = train;
	next = train->prev;

	for (int i = 1; next; i++) {
		if (current->isEngine() || current->isFreightCar()) { break; }
		if (next->isDiningCar() && i < min_dist) { min_dist = i; }
		current = next;
		next = next->prev;
	}

	if (min_dist == 2147483647) { return -1; }
	return min_dist;
}

float AverageDistanceToDiningCar(TrainCar *train) {
	int total_dist = 0, num_cars = 0;
	for (train = start_of(train); train; train = train->next) {
		if (train->isPassengerCar()) {
			total_dist += DistanceToDiningCar(train);
			num_cars++;
		}
	}

	return (float)total_dist / num_cars;
}

int ClosestEngineToSleeperCar(TrainCar *train) {
	int min_dist = 2147483647, dist = 2147483647;

	// Find the first engine or sleeper
	while (!train->isEngine() && !train->isSleepingCar()) { train = train->next; }

	for (bool passed_engine = train->isEngine(); train; train = train->next, dist++) {
		if (train->isEngine()) {
			if (!passed_engine && dist < min_dist) { min_dist = dist; }
			dist = 0;
			passed_engine = true;
		} else if (train->isSleepingCar()) {
			if (passed_engine && dist < min_dist) { min_dist = dist; }
			dist = 0;
			passed_engine = false;
		}
	}

	if (min_dist == 2147483647) { return -1; }
	return min_dist;
}

std::vector<TrainCar*> NaiveShipFreight(TrainCar* &all_engines, TrainCar* &all_freight,
		int min_speed, int max_cars_per_train) {
	std::vector<TrainCar*> out;

	while (all_engines && all_freight) {
		out.push_back(all_engines);
		all_engines = all_engines->next;
		if (all_engines) { // If possible, sever the connections
			all_engines->prev->next = nullptr;
			all_engines->prev = nullptr;
		}

		// Append enough freight cars to reach a limit
		int max_weight = weight_for_speed(1, min_speed);
		int weight = 150, num_cars = 1;
		TrainCar *train = all_freight, *prev = all_freight;
		while (all_freight && weight + all_freight->getWeight() < max_weight && num_cars < max_cars_per_train) {
			prev = all_freight;
			weight += all_freight->getWeight();
			num_cars++;
			all_freight = all_freight->next;
		}
		prev->next = nullptr;
		if (all_freight) { all_freight->prev = nullptr; }

		out.back()->next = train;
		train->prev = out.back();
	}

	return out;
}

// Returns freight that cannot be reasonably shipped in a separate train
TrainCar* parse_valid_freight(TrainCar* &all_freight, int weight, int engines_needed, float min_speed) {
	TrainCar* unshipped_freight = nullptr;
	int weight_delta = weight - weight_for_speed(engines_needed, min_speed + BUFF);

	// Move cars to unshipped_freight until we are light enough
	while (all_freight && weight_delta > 0) {
		// Set next_unshipped to the car in all_freight that will minimize the weight delta
		TrainCar* next_unshipped = nullptr;
		int min_delta = weight_delta;
		for (TrainCar* current = all_freight; current; current = current->next) {
			int delta = weight_delta - current->getWeight();
			if (abs(delta) < abs(min_delta) || (delta < 0 && min_delta > 0)) {
				min_delta = delta;
				next_unshipped = current;
			}
		}
		weight_delta = min_delta;


		if (next_unshipped) {
			// Remove the next_unshipped car from all_freight
			if (next_unshipped->prev == nullptr) {
				all_freight = next_unshipped->next;
			} else {
				next_unshipped->prev->next = next_unshipped->next;
			}
			if (next_unshipped->next) {
				next_unshipped->next->prev = next_unshipped->prev;
			}

			// Add the next_unshipped car to the unshipped freight
			next_unshipped->next = nullptr;
			next_unshipped->prev = unshipped_freight;
			if (unshipped_freight) { unshipped_freight->next = next_unshipped; }
			unshipped_freight = next_unshipped;
		}
	}

	return start_of(unshipped_freight);
}

std::vector<TrainCar*> ShipFreight(TrainCar* &all_engines, TrainCar* &all_freight,
		int min_speed, int max_cars_per_train) {
	std::vector<TrainCar*> out;

	int weight = 0, freight_count = 0, engines_available = 0, engines_needed;
	for (TrainCar* current = all_freight; current; current = current->next) {
		weight += current->getWeight();
		freight_count++;
	}
	weight += 150; // Add the weight of the engine
	for (TrainCar* current = all_engines; current; current = current->next) {
		engines_available++;
	}
	// Find the number of engines needed.
	for (engines_needed = 1; engines_needed <= engines_available; engines_needed++) {
		if (weight_for_speed(engines_needed, min_speed + BUFF) >= weight) { break; }
		// Makes sure that the algorithm will be better able to fit everything
	}
	engines_needed = std::min(engines_needed, engines_available);

	TrainCar* unshipped_freight =
		parse_valid_freight(all_freight, weight, engines_needed, min_speed);

	// We know that it is possible to ship any remaining freight using num_engines engines
	// Distribute the correct number of engines into the output vector
	for (int i = 0; i < engines_needed; i++) {
		out.push_back(all_engines);
		all_engines = all_engines->next;
		if (all_engines) { // If possible, sever the connections
			all_engines->prev->next = nullptr;
			all_engines->prev = nullptr;
		}
	}
	assert(out.size() == engines_needed);

	// Distribute cars into the trains as evenly as possible until we either run out,
	// or reach the max cars per train
	for (int i = 0; i < engines_needed && all_freight; i++) {
		int add_num_cars = freight_count / engines_needed;
		if (i < freight_count % engines_needed) { add_num_cars++; }
		out[i]->next = all_freight;
		all_freight->prev = out[i];

		for (int j = 0; j < add_num_cars && all_freight; j++)
		{ all_freight = all_freight->next; }
		if (all_freight) { // If possible, sever the connections
			all_freight->prev->next = nullptr;
			all_freight->prev = nullptr;
		}
	}
	// If any freight remains, add it to the unshipped_freight
	if (all_freight) {
		TrainCar* end = end_of(unshipped_freight);
		if (end) { end->next = all_freight; }
		else { unshipped_freight = all_freight; }
		all_freight->prev = end;
	}

	all_engines = nullptr;
	all_freight = unshipped_freight;
	return out;
}

void Separate(TrainCar* &orig, TrainCar* &train1, TrainCar* &train2) {
	if (!orig) { return; }
	DeleteAllCars(train1);
	DeleteAllCars(train2);

	int engine_count = 0, train_len = 0;
		// speed_orig = CalculateSpeed(orig);
	for (TrainCar* current = orig; current; current = current->next) {
		if (current->isEngine()) { engine_count++; }
		train_len++;
	}

	// Split the trains
	int engine_count_1 = engine_count / 2; // num engines in train1
	train1 = train2 = orig;
	for (int i = 0; i < engine_count_1; i++) {
		train2 = train2->next;
	}
	// Sever
	train2->prev->next = nullptr;
	train2->prev = nullptr;

	float speed1 = CalculateSpeed(train1),
		  speed2 = CalculateSpeed(train2);
	while (speed1 < speed2) {
		// Move the last car in train1 to the start of train2
		TrainCar* last = end_of(train1);
		last->prev->next = nullptr;
		last->prev = nullptr;
		last->next = train2;
		train2->prev = last;
		train2 = last;

		speed1 = CalculateSpeed(train1);
		speed2 = CalculateSpeed(train2);
	}

	while (speed1 > speed2) {
		// Move the first car in train2 to the end of train1
		TrainCar* first = start_of(train2);
		first->next->prev = nullptr;
		first->next = nullptr;
		first->prev = end_of(train1);
		end_of(train1)->next = first;
		train1 = first;

		speed1 = CalculateSpeed(train1);
		speed2 = CalculateSpeed(train2);
	}
}

