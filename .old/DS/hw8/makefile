bin/out: src/*.cpp src/*.h
	g++ -o bin/out -Wall -Wextra src/*.cpp -g

.PHONY: clean run edit

edit:
	cd src && nvim BPlusTree.h

run: bin/out
	bin/out out/output.txt

clean:
	rm bin/*
