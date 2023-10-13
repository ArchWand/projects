out: *.cpp
	g++ -o out *.cpp -Wall

.PHONY: run

run: out
	./out example.txt example_16_flush_left.txt 16 flush_left
	./out example.txt example_16_flush_right.txt 16 flush_right
	./out example.txt example_16_full_justify.txt 16 full_justify
