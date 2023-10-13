bin/smash.out: src/*.cpp
	g++ -o bin/smash.out -Wall -Wextra src/*.cpp -g

.PHONY: edit run gdb clean diff

diff:
	for f in out/*; do diff "$$f" "example$${f#out}"; done

clean:
	rm bin/smash.out

gdb: bin/smash.out
	echo "r data/large_ult_frame_data.txt queries/queries1_large.txt out/output1_large.txt" | xsel -b
	gdb bin/smash.out

run: bin/smash.out
	bin/smash.out data/large_ult_frame_data.txt queries/queries1_large.txt out/output1_large.txt

edit:
	cd src && nvim *.cpp
