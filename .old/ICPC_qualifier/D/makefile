./out: *.cpp
	g++ -Wall -Wextra -o ./out *.cpp

.PHONY: run test 1 2

run: ./out
	./out

test: ./out
	./out ${ARGS}

1: ./out
	./out < 1.txt

2: ./out
	./out < 2.txt

