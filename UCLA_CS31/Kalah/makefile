bin/out: src/*.cpp src/*.h
	g++ -o bin/out src/*.cpp -Wall

.PHONY: run edit
run: bin/out
	bin/out

edit:
	cd src && nvim Main.cpp
