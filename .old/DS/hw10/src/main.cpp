#include <cstdlib>
#include <cmath>
#include <vector>
#include <iostream>
#include <iomanip>

#include "image.h"
#include "priority_queue.h"

#define sqrt2_dec 0.4142135623730950488016887242097

// ===================================================================================================

// distance field method functions
double NaiveDistanceFieldMethod(Image<Color> &input, Image<DistancePixel> &distance_image);
double ImprovedDistanceFieldMethod(Image<Color> &input, Image<DistancePixel> &distance_image);
double FastMarchingMethod(Image<Color> &input, Image<DistancePixel> &distance_image);
double AccurateMarchingMethod(Image<Color> &input, Image<DistancePixel> &distance_image);

// visualization style helper functions
Color Rainbow(double distance, double max_distance);
Color GreyBands(double distance, double max_distance, int num_bands);
Color HotCold(double distance, double max_distance);

// ===================================================================================================

int main(int argc, char* argv[]) {
	if (argc != 5) {
		std::cerr << "Usage: " << argv[0] << " input.ppm output.ppm distance_field_method visualization_style" << std::endl;
		exit(1);
	}

	// open the input image
	Image<Color> input;
	if (!input.Load(argv[1])) {
		std::cerr << "ERROR: Cannot open input file: " << argv[1] << std::endl;
		exit(1);
	}

	// a place to write the distance values
	Image<DistancePixel> distance_image;
	distance_image.Allocate(input.Width(),input.Height());

	// calculate the distance field (each function returns the maximum distance value)
	double max_distance = 0;
	if (std::string(argv[3]) == std::string("naive_method")) {
		max_distance = NaiveDistanceFieldMethod(input,distance_image);
	} else if (std::string(argv[3]) == std::string("improved_method")) {
		max_distance = ImprovedDistanceFieldMethod(input,distance_image);
	} else if (std::string(argv[3]) == std::string("pq_with_map")) {
		max_distance = FastMarchingMethod(input,distance_image);
	} else if (std::string(argv[3]) == std::string("pq_accurate")) {
		max_distance = AccurateMarchingMethod(input,distance_image);
	} else if (std::string(argv[3]) == std::string("pq_with_hash_table")) {
		// EXTRA CREDIT: implement FastMarchingMethod with a hash table
	} else {
		std::cerr << "ERROR: Unknown distance field method: " << argv[3] << std::endl;
		exit(1);
	}

	// convert distance values to a visualization
	Image<Color> output;
	output.Allocate(input.Width(),input.Height());
	for (int i = 0; i < input.Width(); i++) {
		for (int j = 0; j < input.Height(); j++) {
			double v = distance_image.GetPixel(i,j).getValue();
			if (std::string(argv[4]) == std::string("greyscale")) {
				output.SetPixel(i,j,GreyBands(v,max_distance*1.01,1));
			} else if (std::string(argv[4]) == std::string("grey_bands")) {
				output.SetPixel(i,j,GreyBands(v,max_distance,4));
			} else if (std::string(argv[4]) == std::string("rainbow")) {
				output.SetPixel(i,j,Rainbow(v,max_distance));
			} else if (std::string(argv[4]) == std::string("hot_cold")) {
				output.SetPixel(i,j,HotCold(v,max_distance));
			} else {
				// EXTRA CREDIT: create other visualizations 
				std::cerr << "ERROR: Unknown visualization style" << std::endl;
				exit(0);
			}
		}
	}
	// save output
	if (!output.Save(argv[2])) {
		std::cerr << "ERROR: Cannot save to output file: " << argv[2] << std::endl;
		exit(1);
	}

	// Print distane image
	for (int j = input.Height() - 1; j >= 0; j--) {
		for (int i = 0; i < input.Width(); i++) {
			std::cout << std::fixed << std::setprecision(3) << distance_image.GetPixel(i,j).getValue() << "\t";
		}
		std::cout << std::endl;
	}

	return 0;
}

// ===================================================================================================

double NaiveDistanceFieldMethod(Image<Color> &input, Image<DistancePixel> &distance_image) {
	int w = input.Width();
	int h = input.Height();
	// return the maximum distance value
	double answer = 0;
	// loop over the pixels in the input image
	for (int i = 0; i < w; i++)  {
		for (int j = 0; j < h; j++) {
			double closest = -1;      
			// loop over all other pixels in the input image
			for (int i2 = 0; i2 < w; i2++)  {
				for (int j2 = 0; j2 < h; j2++) {
					const Color& c = input.GetPixel(i2,j2);      
					// skip all pixels that are not black
					if (!c.isBlack()) continue;
					// calculate the distance between the two pixels
					double distance = sqrt((i-i2)*(i-i2) + (j-j2)*(j-j2));
					// store the closest distance to a black pixel
					if (closest < 0 || distance < closest) {
						closest = distance;
					}
				}
			}
			assert (closest >= 0);
			answer = std::max(answer,closest);
			// save the data to the distance image
			DistancePixel& p = distance_image.GetPixel(i,j);
			p.setValue(closest);
		}
	}
	return answer;
}


double ImprovedDistanceFieldMethod(Image<Color> &input, Image<DistancePixel> &distance_image) {
	std::vector<std::pair<int, int>> black_pixels;
	double max_distance = 0;

	for (int i = 0; i < input.Width(); i++) {
		for (int j = 0; j < input.Height(); j++) {
			if (input.GetPixel(i, j).isBlack()) {
				black_pixels.push_back(std::make_pair(i, j));
			}
		}
	}

	// Loop over all pixels, and calculate the distance to the closest black pixel
	for (int i = 0; i < input.Width(); i++) {
		for (int j = 0; j < input.Height(); j++) {
			double closest = -1;
			for (unsigned k = 0; k < black_pixels.size(); k++) {
				int x = black_pixels[k].first,
					y = black_pixels[k].second;
				double distance = sqrt((i-x)*(i-x) + (j-y)*(j-y));
				if (closest < 0 || distance < closest) {
					closest = distance;
				}
			}
			max_distance = std::max(max_distance, closest);

			// Save the data to the distance image
			DistancePixel& p = distance_image.GetPixel(i, j);
			p.setValue(closest);
		}
	}

	return max_distance;
}

typedef DistancePixel_PriorityQueue pqueue;

void print_queue(pqueue q, int x, int y) {
	bool in_queue[30][30] = {0};

	q.print_queue_vec();

	while (!q.empty()) {
		const DistancePixel* p = q.top();
		q.pop();
		in_queue[p->getX()][p->getY()] = true;
	}

	for (int j = 29; j >= 0; j--) {
		for (int i = 0; i < 30; i++) {
			if (i == x && j == y) {
				std::cout << "O";
			} else if (in_queue[i][j]) {
				std::cout << "X";
			} else {
				std::cout << ".";
			}
		}
		std::cout << std::endl;
	}
	std::cout << "(" << x << ", " << y << ")" << std::endl;
	std::cout << std::endl;
}

void print_queue(pqueue q) { print_queue(q, -1, -1); }

double FastMarchingMethod(Image<Color> &input, Image<DistancePixel> &distance_image) {
	double max_distance = 0;
	bool **fixed = new bool*[input.Width()];
	for (int i = 0; i < input.Width(); i++) {
		fixed[i] = new bool[input.Height()];
	}

	// Tell each distance pixel where it is
	for (int i = 0; i < input.Width(); i++) {
		for (int j = 0; j < input.Height(); j++) {
			DistancePixel& p = distance_image.GetPixel(i, j);
			p.setX(i);
			p.setY(j);
		}
	}

	// Place all black pixels in a priority queue
	std::vector<DistancePixel*> black_pixels;
	for (int i = 0; i < input.Width(); i++) {
		for (int j = 0; j < input.Height(); j++) {
			DistancePixel& p = distance_image.GetPixel(i, j);
			if (input.GetPixel(i, j).isBlack()) {
				p.setValue(0);
				black_pixels.push_back(&p);
				fixed[i][j] = true;
			} else { // initialize distances to infinity
				p.setValue(std::numeric_limits<double>::max());
				fixed[i][j] = false;
			}
		}
	}

	pqueue queue(black_pixels);

	// March until the queue is empty
	while (!queue.empty()) {

		const DistancePixel* p = queue.top();
		queue.pop();

		int x = p->getX(),
			y = p->getY();
		double cur_dist = p->getValue();
		max_distance = std::max(max_distance, cur_dist);
		fixed[x][y] = true;

		// Update the neighbors
		for (int i = -1; i <= 1; i++) {
			for (int j = -1; j <= 1; j++) {
				if (i == 0 && j == 0) continue;

				int x2 = x + i,
					y2 = y + j;
				// Bounds check
				if (x2 < 0 || x2 >= input.Width() || y2 < 0 || y2 >= input.Height()) continue;
				if (fixed[x2][y2]) continue;

				DistancePixel& p2 = distance_image.GetPixel(x2, y2);
				double next_dist = p2.getValue();
				double new_dist = cur_dist + 1 + std::abs(i*j*sqrt2_dec);
				if (new_dist < next_dist) {
					p2.setValue(new_dist);
					if (queue.in_heap(&p2)) {
						queue.update_position(&p2);
					} else {
						queue.push(&p2);
					}
				}
			}
		}
	}

	for (int i = 0; i < input.Width(); i++) {
		delete[] fixed[i];
	}
	delete[] fixed;

	return max_distance;
}

double AccurateMarchingMethod(Image<Color> &input, Image<DistancePixel> &distance_image) {
	double max_distance = 0;
	bool **fixed = new bool*[input.Width()];
	for (int i = 0; i < input.Width(); i++) {
		fixed[i] = new bool[input.Height()];
	}

	// Initialize pixels and priority queue
	std::vector<DistancePixel*> black_pixels;
	for (int i = 0; i < input.Width(); i++) {
		for (int j = 0; j < input.Height(); j++) {
			DistancePixel& p = distance_image.GetPixel(i, j);
			p.setX(i);
			p.setY(j);

			if (input.GetPixel(i, j).isBlack()) {
				p.setValue(0);
				black_pixels.push_back(&p);
				fixed[i][j] = true;
				p.bi = i;
				p.bj = j;
			} else { // initialize distances to infinity
				p.setValue(std::numeric_limits<double>::max());
				fixed[i][j] = false;
				p.bi = -1;
				p.bj = -1;
			}
		}
	}

	pqueue queue(black_pixels);

	// March until the queue is empty
	while (!queue.empty()) {

		const DistancePixel* p = queue.top();
		queue.pop();

		int x = p->getX(),
			y = p->getY();
		double cur_dist = p->getValue();
		max_distance = std::max(max_distance, cur_dist);
		fixed[x][y] = true;

		// Update the neighbors
		for (int i = -1; i <= 1; i++) {
			for (int j = -1; j <= 1; j++) {
				if (i == 0 && j == 0) continue;

				int x2 = x + i,
					y2 = y + j;
				// Bounds check
				if (x2 < 0 || x2 >= input.Width() || y2 < 0 || y2 >= input.Height()) continue;
				if (fixed[x2][y2]) continue;

				DistancePixel& p2 = distance_image.GetPixel(x2, y2);
				double next_dist = p2.getValue();
				double new_dist = sqrt((x2 - p->bi)*(x2 - p->bi) + (y2 - p->bj)*(y2 - p->bj));
				if (new_dist < next_dist) {
					p2.setValue(new_dist);
					p2.bi = p->bi;
					p2.bj = p->bj;
					if (queue.in_heap(&p2)) {
						queue.update_position(&p2);
					} else {
						queue.push(&p2);
					}
				}
			}
		}
	}

	for (int i = 0; i < input.Width(); i++) {
		delete[] fixed[i];
	}
	delete[] fixed;

	return max_distance;
}

// ===================================================================================================

Color Rainbow(double distance, double max_distance) {
	Color answer;
	if (distance < 0.001) {
		// black
		answer.r = 0; answer.g = 0; answer.b = 0;
	} else if (distance < 0.2*max_distance) {
		// blue -> cyan
		double tmp = distance * 5.0 / max_distance;
		answer.r = 0;
		answer.g = tmp*255;
		answer.b = 255;
	} else if (distance < 0.4*max_distance) {
		// cyan -> green
		double tmp = (distance-0.2*max_distance) * 5.0 / max_distance;
		answer.r = 0;
		answer.g = 255;
		answer.b = (1-tmp*tmp)*255;
	} else if (distance < 0.6*max_distance) {
		// green -> yellow
		double tmp = (distance-0.4*max_distance) * 5.0 / max_distance;
		answer.r = sqrt(tmp)*255;
		answer.g = 255;
		answer.b = 0;
	} else if (distance < 0.8*max_distance) {
		// yellow -> red
		double tmp = (distance-0.6*max_distance) * 5.0 / max_distance;
		answer.r = 255;
		answer.g = (1-tmp*tmp)*255;
		answer.b = 0;
	} else if (distance < max_distance) {
		// red -> white
		double tmp = (distance-0.8*max_distance) * 5.0 / max_distance;
		answer.r = 255;
		answer.g = tmp*255;
		answer.b = tmp*255;
	} else {
		// white
		answer.r = answer.g = answer.b = 255;
	}  
	return answer;
}

Color GreyBands(double distance, double max_value, int num_bands) {
	Color answer;
	if (distance < 0.001) {
		// red
		answer.r = 255; answer.g = 0; answer.b = 0;
	} else {
		// shades of grey
		answer.r = answer.g = answer.b = int(num_bands*256*distance/double(max_value)) % 256;
	}  
	return answer;
}

Color HotCold(double distance, double max_distance) {
	Color answer;
	if (distance < 0.001) {
		// black
		answer.r = 0; answer.g = 0; answer.b = 0;
	} else if (distance < 0.497*max_distance) {
		// red -> white
		double tmp = distance * 2.0 / max_distance;
		answer.r = 255;
		answer.g = tmp*255;
		answer.b = tmp*255;
	} else if (distance > 0.503*max_distance) {
		// white -> blue
		double tmp = distance * 2.0 / max_distance;
		answer.r = (1-tmp)*255;
		answer.g = (1-tmp)*255;
		answer.b = 255;
	} else {
		// white
		answer.r = answer.g = answer.b = 255;
	}
	return answer;
}

// ===================================================================================================
