genome = medium

bin/out: src/*
	g++ -o bin/out src/* -Wall

.PHONY: run diff edit show

edit:
	nvim src/main.cpp

run: bin/out
	bin/out < in/input_$(genome).txt > out/$(genome).txt

show: bin/out
	bin/out < in/input_$(genome).txt

diff:
	diff out/$(genome).txt example/output_$(genome).txt
