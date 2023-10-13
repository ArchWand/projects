#include <iostream>
#include <fstream>

int main(int /* argc */, char* /* argv */[]) {
	int z = 0x41424344;

	char *c = (char*) &z;
	printf("%c", *c++);
	printf("%c", *c++);
	printf("%c", *c++);
	printf("%c", *c++);
	printf("\n");

	c = (char*) &z;
	printf("%p\n", c++);
	printf("%p\n", c++);
	printf("%p\n", c++);
	printf("%p\n", c++);
	return 0;
}
