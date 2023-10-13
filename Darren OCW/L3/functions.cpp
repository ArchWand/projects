int do_thing(int a, int b) {
	int out = a + b;
	return out;
}

int main() {
	int two   = 2,
		three = 3;
	do_thing(two, three);
	do_thing(three, two);
	return 0;
}
