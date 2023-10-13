bin/out: src/*.cpp src/*.h
	g++ -o bin/out src/*.cpp -Wall -Wextra -O3

.PHONY: edit clean run profile
.PHONY: 1c 1oc 2c 3c 4c 5c 6c 7c 8c
.PHONY: 1 2 3 4 5 6 7 8
.PHONY: 1o 2o 3o 4o 5o 6o 7o 8o
.PHONY: all
.PHONY: c1c c2c c3c c4c c5c
.PHONY: c1 c2 c3 c4 c5
.PHONY: c1o c2o c3o c4o c5o
.PHONY: 10 11 10c 11c

run: bin/out
	bin/out input/puzzle7.txt out/puzzle7.txt all_solutions
	cat out/puzzle7.txt

profile: bin/out
	valgrind --tool=callgrind --dump-instr=yes --simulate-cache=yes --collect-jumps=yes bin/out input/custom2.txt out/custom2.txt all_solutions

edit:
	cd src && nvim main.cpp

clean:
	rm -f bin/out

1c:
	cat input/puzzle1.txt; head -n 1 example/out1.txt

1oc:
	cat input/puzzle1.txt; head -n 1 example/out1_onesol.txt

2c:
	cat input/puzzle2.txt; head -n 1 example/out2.txt

3c:
	cat input/puzzle3.txt; head -n 1 example/out3.txt

4c:
	cat input/puzzle4.txt; head -n 1 example/out4.txt

5c:
	cat input/puzzle5.txt; head -n 1 example/out5.txt

6c:
	cat input/puzzle6.txt; head -n 1 example/out6.txt

7c:
	cat input/puzzle7.txt; head -n 1 example/out7.txt

8c:
	cat input/puzzle8.txt; head -n 1 example/out8.txt

1: bin/out
	bin/out input/puzzle1.txt out/puzzle1.txt all_solutions
	cat out/puzzle1.txt

2: bin/out
	bin/out input/puzzle2.txt out/puzzle2.txt all_solutions
	cat out/puzzle2.txt

3: bin/out
	bin/out input/puzzle3.txt out/puzzle3.txt all_solutions
	cat out/puzzle3.txt

4: bin/out
	bin/out input/puzzle4.txt out/puzzle4.txt all_solutions
	cat out/puzzle4.txt

5: bin/out
	bin/out input/puzzle5.txt out/puzzle5.txt all_solutions
	cat out/puzzle5.txt

6: bin/out
	bin/out input/puzzle6.txt out/puzzle6.txt all_solutions
	cat out/puzzle6.txt

7: bin/out
	bin/out input/puzzle7.txt out/puzzle7.txt all_solutions
	cat out/puzzle7.txt

8: bin/out
	bin/out input/puzzle8.txt out/puzzle8.txt all_solutions
	cat out/puzzle8.txt

1o: bin/out
	bin/out input/puzzle1.txt out/puzzle1.txt one_solution
	cat out/puzzle1.txt

2o: bin/out
	bin/out input/puzzle2.txt out/puzzle2.txt one_solution
	cat out/puzzle2.txt

3o: bin/out
	bin/out input/puzzle3.txt out/puzzle3.txt one_solution
	cat out/puzzle3.txt

4o: bin/out
	bin/out input/puzzle4.txt out/puzzle4.txt one_solution
	cat out/puzzle4.txt

5o: bin/out
	bin/out input/puzzle5.txt out/puzzle5.txt one_solution
	cat out/puzzle5.txt

6o: bin/out
	bin/out input/puzzle6.txt out/puzzle6.txt one_solution
	cat out/puzzle6.txt

7o: bin/out
	bin/out input/puzzle7.txt out/puzzle7.txt one_solution
	cat out/puzzle7.txt

8o: bin/out
	bin/out input/puzzle8.txt out/puzzle8.txt one_solution
	cat out/puzzle8.txt

all:
	make 1c; make 1
	make 2c; make 2
	make 3c; make 3
	make 4c; make 4
	make 5c; make 5
	make 6c; make 6
	make 7c; make 7
	make 8c; make 8

c1c:
	cat input/custom1.txt

c2c:
	cat input/custom2.txt

c3c:
	cat input/custom3.txt

c4c:
	cat input/custom4.txt

c5c:
	cat input/custom5.txt

c1: bin/out
	bin/out input/custom1.txt out/custom1.txt all_solutions
	cat out/custom1.txt

c2: bin/out
	bin/out input/custom2.txt out/custom2.txt all_solutions
	cat out/custom2.txt

c3: bin/out
	bin/out input/custom3.txt out/custom3.txt all_solutions
	cat out/custom3.txt

c4: bin/out
	bin/out input/custom4.txt out/custom4.txt all_solutions
	cat out/custom4.txt

c5: bin/out
	bin/out input/custom5.txt out/custom5.txt all_solutions
	cat out/custom5.txt

c1o: bin/out
	bin/out input/custom1.txt out/custom1.txt one_solution
	cat out/custom1.txt

c2o: bin/out
	bin/out input/custom2.txt out/custom2.txt one_solution
	cat out/custom2.txt

c3o: bin/out
	bin/out input/custom3.txt out/custom3.txt one_solution
	cat out/custom3.txt

c4o: bin/out
	bin/out input/custom4.txt out/custom4.txt one_solution
	cat out/custom4.txt

c5o: bin/out
	bin/out input/custom5.txt out/custom5.txt one_solution
	cat out/custom5.txt

10c:
	cat input/puzzle10.txt

11c:
	cat input/puzzle11.txt

10: bin/out
	bin/out input/puzzle10.txt out/puzzle10.txt all_solutions
	cat out/puzzle10.txt

11: bin/out
	bin/out input/puzzle11.txt out/puzzle11.txt all_solutions
	cat out/puzzle11.txt

