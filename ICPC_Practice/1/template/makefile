./out: *.cpp
	g++ -Wall -Wextra -o ./out *.cpp -O3

.PHONY: run clip

run: ./out
	./out ${ARGS}

clip:
	cat test.cpp | xsel -b
