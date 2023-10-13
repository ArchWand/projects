#include <cstdlib>
#include <cmath>
#include <vector>
#include <iostream>

#include "image.h"
#include "priority_queue.h"

// ===================================================================================================

// distance field method functions
double NaiveDistanceFieldMethod(Image<Color> &input, Image<DistancePixel> &distance_image);
double ImprovedDistanceFieldMethod(Image<Color> &input, Image<DistancePixel> &distance_image);
double FastMarchingMethod(Image<Color> &input, Image<DistancePixel> &distance_image);

// visualization style helper functions
Color Rainbow(double distance, double max_distance);
Color GreyBands(double distance, double max_distance, int num_bands);

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

// compares every pixel with every BLACK pixel
double ImprovedDistanceFieldMethod(Image<Color> &input, Image<DistancePixel> &distance_image) {

	int w = input.Width();
	int h = input.Height();

	std::vector<std::pair<int, int> > black_pixels;
	// loops over the pixels in input image
	for (int i = 0; i < w; i++) {
		for (int j = 0; j < h; j++) {
			const Color& c = input.GetPixel(i, j);
			// if the pixel is black, add it to the vector
			if (c.isBlack()) {
				black_pixels.push_back(std::make_pair(i, j));
			}
		}
	}

	// return the maximum distance value
	double answer = 0;
	// loop over the pixels in the input image
	for (int i = 0; i < w; i++) {
		for (int j = 0; j < h; j++) {
			double closest = -1;
			// loops through vector of found black pixels
			int black_vec_size = black_pixels.size();
			for (int k = 0; k < black_vec_size; k++) {
				int i2 = black_pixels[k].first;
				int j2 = black_pixels[k].second;
				// calculate the distance between the two pixels
				double distance = sqrt((i-i2)*(i-i2) + (j-j2)*(j-j2));
				// store the closest distance to a black pixel
				if (closest < 0 || distance < closest) {
					closest = distance;
				}
			}
			assert(closest >= 0);
			answer = std::max(answer, closest);
			// save the data to the distance image
			DistancePixel& p = distance_image.GetPixel(i, j);
			p.setValue(closest);
		}
	}
	return answer;
}

// using advancing front method and a priority queue
double FastMarchingMethod(Image<Color> &input, Image<DistancePixel> &distance_image) {

	int w = input.Width();
	int h = input.Height();
	double answer = 0;

	// vector of black pixels (x, y)
	std::vector<std::pair<int, int> > black_pixels;

	// create a priority queue for the pixels
	DistancePixel_PriorityQueue pixel_queue;

	// loop over the pixels in the input image
	for (int i = 0; i < w; i++) {
		for (int j = 0; j < h; j++) {
			DistancePixel& p = distance_image.GetPixel(i, j);
			const Color& c = input.GetPixel(i, j);
			// if color is black, set value in distance field to 0
			if (c.isBlack()) {
				p.setValue(0.0);
				black_pixels.push_back(std::make_pair(i, j));
				pixel_queue.add_to_black(i, j);
			}
			// else set it to infinity
			else {
				p.setValue(std::numeric_limits<double>::infinity());
			}
		}
	}

	// loops through black pixel vector
	int black_vec_size = black_pixels.size();
	for (int i = 0; i < black_vec_size; i++) {
		int b_x = black_pixels[i].first;
		int b_y = black_pixels[i].second;
		// bp for black pixel
		DistancePixel& bp = distance_image.GetPixel(b_x, b_y);
		double b_dist = bp.getValue();
		// checks 8 neighbors and inserts into priority queue
		for (int dx = -1; dx <= 1; dx++) {
			for (int dy = -1; dy <= 1; dy++) {
				int n_x = b_x + dx;
				int n_y = b_y + dy;
				if ((dx == 0 && dy == 0) || (n_x < 0) || (n_y < 0) || (n_x >= w) || (n_y >= h)) {
					continue;
				}
				// np for neighbor pixel
				DistancePixel& np = distance_image.GetPixel(n_x, n_y);
				if (pixel_queue.is_black(n_x, n_y || pixel_queue.is_red(n_x, n_y))) {
					continue;
				}
				double n_dist = np.getValue();
				double dist_btw = sqrt((b_x - (n_x))*(b_x - (n_x)) + (b_y - (n_y))*(b_y - (n_y)));
				if (n_dist > (b_dist + dist_btw)) {
					// sets the values to np pixel
					np.setValue(b_dist + dist_btw);
					np.setX(n_x);
					np.setY(n_y);
					pixel_queue.add_to_red(n_x, n_y);
					DistancePixel* dp = &np;
					if (pixel_queue.in_heap(dp) == false) {
						pixel_queue.push(dp);
					}
					else {
						pixel_queue.update_position(dp);
					}
				}
			}
		}
	}

	// propogates the data
	while (!pixel_queue.empty()) {
		const DistancePixel* pixel = pixel_queue.top();

		pixel_queue.pop();

		int c_x = pixel->getX();
		int c_y = pixel->getY();

		// remove from red and add to black
		pixel_queue.remove_red(c_x, c_y);
		pixel_queue.add_to_black(c_x, c_y);

		// cp for current pixel
		DistancePixel& cp = distance_image.GetPixel(c_x, c_y);
		double c_dist = cp.getValue();

		// checks 8 neighbors and inserts into priority queue
		for (int dx = -1; dx <= 1; dx++) {
			for (int dy = -1; dy <= 1; dy++) {
				int n_x = c_x + dx;
				int n_y = c_y + dy;
				if ((dx == 0 && dy == 0) || (n_x < 0) || (n_y < 0) || (n_x >= w) || (n_y >= h)) {
					continue;
				}
				// if the pixel is marked black then skip it
				if (pixel_queue.is_black(n_x, n_y)) {
					continue;
				}
				// np for neighbor pixel
				DistancePixel& np = distance_image.GetPixel(n_x, n_y);
				double n_dist = np.getValue();
				double dist_btw = sqrt((c_x - (n_x))*(c_x - (n_x)) + (c_y - (n_y))*(c_y - (n_y)));
				if (n_dist > (c_dist + dist_btw)) {
					// sets the values to np pixel
					np.setValue(c_dist + dist_btw);
					np.setX(n_x);
					np.setY(n_y);
					if (pixel_queue.is_red(n_x, n_y)) {
						// update position
						DistancePixel* dp = &np;
						pixel_queue.update_position(dp);
					}
					else {
						// add to pririoty queue
						DistancePixel* dp = &np;
						if (pixel_queue.in_heap(dp) == false) {
							pixel_queue.push(dp);
						}
						else {
							pixel_queue.update_position(dp);
						}
					}
				}
			}
		}
	}

	for (int y = 0; y < distance_image.Height(); y++) {
		for (int x = 0; x < distance_image.Width(); x++) {
			answer = std::max(answer, distance_image.GetPixel(x, y).getValue());
		}
	}
	return answer;
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

// ===================================================================================================
