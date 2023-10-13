#include <cstdlib>
#include <cmath>
#include <vector>
#include <iostream>

#include "image.h"
#include "priority_queue.h"

// ===================================================================================================

// distance field method functions
double NaiveDistanceFieldMethod(Image < Color > & input, Image < DistancePixel > & distance_image);
double ImprovedDistanceFieldMethod(Image < Color > & input, Image < DistancePixel > & distance_image);
double FastMarchingMethod(Image < Color > & input, Image < DistancePixel > & distance_image);

// visualization style helper functions
Color Rainbow(double distance, double max_distance);
Color GreyBands(double distance, double max_distance, int num_bands);
Color ExtraCredit(double distance, double max_value);
Color HotCold(double distance, double max_distance);

// ===================================================================================================

int main(int argc, char * argv[]) {
	if (argc != 5) {
		std::cerr << "Usage: " << argv[0] << " input.ppm output.ppm distance_field_method visualization_style" << std::endl;
		exit(1);
	}

	// open the input image
	Image < Color > input;
	if (!input.Load(argv[1])) {
		std::cerr << "ERROR: Cannot open input file: " << argv[1] << std::endl;
		exit(1);
	}

	// a place to write the distance values
	Image < DistancePixel > distance_image;
	distance_image.Allocate(input.Width(), input.Height());

	// calculate the distance field (each function returns the maximum distance value)
	double max_distance = 0;
	if (std::string(argv[3]) == std::string("naive_method")) {
		max_distance = NaiveDistanceFieldMethod(input, distance_image);
	} else if (std::string(argv[3]) == std::string("improved_method")) {
		max_distance = ImprovedDistanceFieldMethod(input, distance_image);
	} else if (std::string(argv[3]) == std::string("pq_with_map")) {
		max_distance = FastMarchingMethod(input, distance_image);
	} else if (std::string(argv[3]) == std::string("pq_with_hash_table")) {
		// EXTRA CREDIT: implement FastMarchingMethod with a hash table
	} else {
		std::cerr << "ERROR: Unknown distance field method: " << argv[3] << std::endl;
		exit(1);
	}

	// convert distance values to a visualization
	Image < Color > output;
	output.Allocate(input.Width(), input.Height());
	for (int i = 0; i < input.Width(); i++) {
		for (int j = 0; j < input.Height(); j++) {
			double v = distance_image.GetPixel(i, j).getValue();
			if (std::string(argv[4]) == std::string("greyscale")) {
				output.SetPixel(i, j, GreyBands(v, max_distance * 1.01, 1));
			} else if (std::string(argv[4]) == std::string("grey_bands")) {
				output.SetPixel(i, j, GreyBands(v, max_distance, 4));
			} else if (std::string(argv[4]) == std::string("rainbow")) {
				output.SetPixel(i, j, Rainbow(v, max_distance));
			} 
			else if (std::string(argv[4]) == std::string("ExtraCredit")) {
				output.SetPixel(i, j, ExtraCredit(v, max_distance));
			} else if (std::string(argv[4]) == std::string("hot_cold")) {
				output.SetPixel(i,j,HotCold(v,max_distance));
			}
			else {
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

	return 0;
}

// ===================================================================================================

double NaiveDistanceFieldMethod(Image < Color > & input, Image < DistancePixel > & distance_image) {
	int w = input.Width();
	int h = input.Height();
	// return the maximum distance value
	double answer = 0;
	// loop over the pixels in the input image
	for (int i = 0; i < w; i++) {
		for (int j = 0; j < h; j++) {
			double closest = -1;
			// loop over all other pixels in the input image
			for (int i2 = 0; i2 < w; i2++) {
				for (int j2 = 0; j2 < h; j2++) {
					const Color & c = input.GetPixel(i2, j2);
					// skip all pixels that are not black
					if (!c.isBlack()) continue;

					// calculate the distance between the two pixels
					double distance = sqrt((i - i2) * (i - i2) + (j - j2) * (j - j2));
					// store the closest distance to a black pixel
					if (closest < 0 || distance < closest) {
						closest = distance;
					}
				}
			}
			assert(closest >= 0);
			answer = std::max(answer, closest);
			// save the data to the distance image
			DistancePixel & p = distance_image.GetPixel(i, j);
			p.setValue(closest);
		}
	}
	return answer;
}




double ImprovedDistanceFieldMethod(Image < Color > & input, Image < DistancePixel > & distance_image) {
	int w = input.Width();
	int h = input.Height();
	// return the maximum distance value
	double answer = 0;

	std::vector < int > x_value;
	std::vector < int > y_value;

	for (int i = 0; i < w; i++) {
		for (int j = 0; j < h; j++) {
			const Color & c = input.GetPixel(i, j);
			if (c.isBlack()) {
				x_value.push_back(i);
				y_value.push_back(j);
			}
		}
	}

	for (int i = 0; i < w; i++) {
		for (int j = 0; j < h; j++) {
			double closest = -1;
			// loop over all other pixels in the input image
			for (unsigned int i2 = 0; i2 < x_value.size(); i2++) {

				// calculate the distance between the two pixels
				double distance = sqrt((i - x_value[i2]) * (i - x_value[i2]) + (j - y_value[i2]) * (j - y_value[i2]));
				// store the closest distance to a black pixel
				if (closest < 0 || distance < closest) {
					closest = distance;
				}
			}
			assert(closest >= 0);
			answer = std::max(answer, closest);
			// save the data to the distance image
			DistancePixel & p = distance_image.GetPixel(i, j);
			p.setValue(closest);
		}
	}

	return answer;
}




void insert_only(int x, int y, int x2, int y2, Image < DistancePixel > & distance_image,
		DistancePixel_PriorityQueue & queue) {

	//Find the distance from the current pixel to the next pixel
	double distance = sqrt((x - x2) * (x - x2) + (y - y2) * (y - y2));

	//Get a pointer to the neighboring pixle
	DistancePixel & p = distance_image.GetPixel(x2, y2);

	//If the value of the neighboring pixle is larger then the calculated distance, set the value of that pixel equal to the calculated distance
	if (p.getValue() != 0 && p.getValue() > (distance)) {
		p.setValue(distance);

		//Add the pixle to the queue
		DistancePixel * temp = & p;
		if (queue.in_heap(temp) == false) {
			queue.push(temp);

		}
	}
}

void insert_or_update(int x, int y, int x2, int y2, const DistancePixel * poped_value,
		Image < DistancePixel > & distance_image, DistancePixel_PriorityQueue & queue) {

	//Calculate the distance of the nieghboring pixle to the nearest black pixel
	double distance = sqrt((x - x2) * (x - x2) + (y - y2) * (y - y2)) + poped_value -> getValue();

	//Get the neighboring pixel
	DistancePixel & p = distance_image.GetPixel(x2, y2);

	//If the pixels current value is larger than the distance value calculated, replace it with the distance value
	if (p.getValue() != 0 && p.getValue() > (distance)) {
		p.setValue(distance);
		DistancePixel * temp = & p;

		//If not in the heap, add it
		if (queue.in_heap(temp) == false) {
			queue.push(temp);

			//If it is in the heap, update it
		} else {
			queue.update_position(temp);
		}
	}
}



double FastMarchingMethod(Image < Color > & input, Image < DistancePixel > & distance_image) {

	DistancePixel_PriorityQueue queue;
	int max = 10000;

	int w = input.Width();
	int h = input.Height();
	// return the maximum distance value
	double answer = 0;

	//Initalizing every point so they can be compared against in the future
	std::vector < DistancePixel > black_pixels;
	for (int i = 0; i < w; i++) {
		for (int j = 0; j < h; j++) {
			const Color & c = input.GetPixel(i, j);
			//If the point is black, add it to the vector of black points and assign its values
			if (c.isBlack()) {
				DistancePixel & p = distance_image.GetPixel(i, j);
				p.setValue(0);
				p.setX(i);
				p.setY(j);
				black_pixels.push_back(p);
			}
			//Otherwise, simply initalize its values and add it to no vector
			else {
				DistancePixel & p = distance_image.GetPixel(i, j);
				p.setX(i);
				p.setY(j);
				p.setValue(max);
			}
		}
	}

	//While looping through the vector of all black pixels
	for (unsigned int i2 = 0; i2 < black_pixels.size(); i2++) {
		//Get the x and y cords of that given black pixel
		int x = black_pixels[i2].getX();
		int y = black_pixels[i2].getY();
		int x2 = x;
		int y2 = y;

		//Check the pixel to the right
		if (x < w - 1) {
			y2 = y;
			x2 = x + 1;
			insert_only(x, y, x2, y2, distance_image, queue);
		}

		//Check the pixel to the left
		if (x > 0) {
			x2 = x - 1;
			y2 = y;
			insert_only(x, y, x2, y2, distance_image, queue);
		}

		//Check the pixel bellow
		if (y < h - 1) {
			y2 = y + 1;
			x2 = x;
			insert_only(x, y, x2, y2, distance_image, queue);
		}

		//Check the pixel above
		if (y > 0) {
			y2 = y - 1;
			x2 = x;
			insert_only(x, y, x2, y2, distance_image, queue);
		}

		//Check the pixel to the lower right
		if (y < h - 1 && x < w - 1) {
			y2 = y + 1;
			x2 = x + 1;
			insert_only(x, y, x2, y2, distance_image, queue);
		}

		//Check the pixel to the upper left
		if (y > 0 && x > 0) {
			y2 = y - 1;
			x2 = x - 1;
			insert_only(x, y, x2, y2, distance_image, queue);
		}

		//Check the pixel to the upper right
		if (y > 0 && x < w - 1) {
			y2 = y - 1;
			x2 = x + 1;
			insert_only(x, y, x2, y2, distance_image, queue);
		}

		//Check the pixel to the lower left
		if (y < h - 1 && x > 0) {
			y2 = y + 1;
			x2 = x - 1;
			insert_only(x, y, x2, y2, distance_image, queue);
		}

	}



	//Now, instead of looking through your vector of black pixles, you will look at the pixel at the top of the priority queue
	while (queue.size() != 0) {
		//Get the value at the top of the priority queue
		const DistancePixel * poped_value = queue.top();

		//If the pixels current value is higher than the stored max value, set the max value equal to this positions current value
		if (poped_value -> getValue() > answer) {
			answer = poped_value -> getValue();
		}

		//Remove from the top of the priority queue
		queue.pop();

		//Get the x and y for the pixel
		int x = poped_value -> getX();
		int y = poped_value -> getY();
		int x2 = x;
		int y2 = y;

		//Check the pixel to the right
		if (x < w - 1) {
			y2 = y;
			x2 = x + 1;
			insert_or_update(x, y, x2, y2, poped_value, distance_image, queue);
		}

		//Check the pixel to the left
		if (x > 0) {
			y2 = y;
			x2 = x - 1;
			insert_or_update(x, y, x2, y2, poped_value, distance_image, queue);
		}

		//Check the pixel bellow
		if (y < h - 1) {
			y2 = y + 1;
			x2 = x;
			insert_or_update(x, y, x2, y2, poped_value, distance_image, queue);
		}

		//Check the pixel above
		if (y > 0) {
			y2 = y - 1;
			x2 = x;
			insert_or_update(x, y, x2, y2, poped_value, distance_image, queue);
		}

		//Check the pixel to the upper left
		if (y > 0 && x > 0) {
			y2 = y - 1;
			x2 = x - 1;
			insert_or_update(x, y, x2, y2, poped_value, distance_image, queue);
		}

		//Check the pixel to the lower right
		if (y < h - 1 && x < w - 1) {
			y2 = y + 1;
			x2 = x + 1;
			insert_or_update(x, y, x2, y2, poped_value, distance_image, queue);
		}

		//Check the pixel to the upper right
		if (y > 0 && x < w - 1) {
			y2 = y - 1;
			x2 = x + 1;
			insert_or_update(x, y, x2, y2, poped_value, distance_image, queue);
		}

		//Check the pixel to the lower left
		if (y < h - 1 && x > 0) {
			y2 = y + 1;
			x2 = x - 1;
			insert_or_update(x, y, x2, y2, poped_value, distance_image, queue);
		}
	}
	return answer;
}


// ===================================================================================================

Color Rainbow(double distance, double max_distance) {
	Color answer;
	if (distance < 0.001) {
		// black
		answer.r = 0;
		answer.g = 0;
		answer.b = 0;
	} else if (distance < 0.2 * max_distance) {
		// blue -> cyan
		double tmp = distance * 5.0 / max_distance;
		answer.r = 0;
		answer.g = tmp * 255;
		answer.b = 255;
	} else if (distance < 0.4 * max_distance) {
		// cyan -> green
		double tmp = (distance - 0.2 * max_distance) * 5.0 / max_distance;
		answer.r = 0;
		answer.g = 255;
		answer.b = (1 - tmp * tmp) * 255;
	} else if (distance < 0.6 * max_distance) {
		// green -> yellow
		double tmp = (distance - 0.4 * max_distance) * 5.0 / max_distance;
		answer.r = sqrt(tmp) * 255;
		answer.g = 255;
		answer.b = 0;
	} else if (distance < 0.8 * max_distance) {
		// yellow -> red
		double tmp = (distance - 0.6 * max_distance) * 5.0 / max_distance;
		answer.r = 255;
		answer.g = (1 - tmp * tmp) * 255;
		answer.b = 0;
	} else if (distance < max_distance) {
		// red -> white
		double tmp = (distance - 0.8 * max_distance) * 5.0 / max_distance;
		answer.r = 255;
		answer.g = tmp * 255;
		answer.b = tmp * 255;
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
		answer.r = 255;
		answer.g = 0;
		answer.b = 0;
	} else {
		// shades of grey
		answer.r = answer.g = answer.b = int(num_bands * 256 * distance / double(max_value)) % 256;
	}
	return answer;
}

Color ExtraCredit(double distance, double max_value) {
	Color answer;
	if (distance < 0.001) {
		answer.r = 0;
		answer.g = 204;
		answer.b = 204;
	} else if (distance < 0.05 * max_value) {
		answer.r = answer.g = answer.b = 255;

	} else {
		// white
		answer.r = 182*distance/double(max_value);
		answer.g = 0;
		answer.b = 0;
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
