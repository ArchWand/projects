inputf=in/dots2.ppm
output=out/out.ppm
# method=naive_method
# method=improved_method
method=pq_with_map
# render=greyscale
# render=grey_bands
# render=rainbow
render=hot_cold
# render=ExtraCredit

bin/out: src/*
	g++ -o bin/out src/*.cpp -Wall

.PHONY: run edit clean

clean:
	rm -f bin/out

edit:
	cd src && nvim main.cpp

run: bin/out
	bin/out $(inputf) $(output) $(method) $(render)
	kitty +kitten icat $(output)

