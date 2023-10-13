#include <iostream>

int main(int, char *argv[]) {
	int x = std::stoi(argv[1]);
	const char *frog = "Hello World!";
	int i = 0;
	if (x == 0) { return 0; }
	do {
		std::cout << frog << std::endl;
		++i;
	}
	while (i<x);
}
