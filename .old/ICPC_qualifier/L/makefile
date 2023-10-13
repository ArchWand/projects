./out: test.cpp
	g++ -Wall -Wextra -o ./out test.cpp

./out_naive: naive.cpp
	g++ -Wall -Wextra -o ./out_naive naive.cpp

.PHONY: run java naive

run: ./out
	./out

java:
	java bigger.java

naive: ./out_naive
	./out_naive

