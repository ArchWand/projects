bin/out: src/*.cpp src/*.h
	g++ -o bin/out -Wall -Wextra src/*.cpp -g

.PHONY: run gdb edit main_edit prototype_edit

prototype_edit:
	cd src && nvim traincar_prototypes.h

main_edit:
	cd src && nvim main.cpp

edit:
	cd src && nvim traincar.cpp

gdb: bin/out
	gdb bin/out -tui

run: bin/out
	bin/out
