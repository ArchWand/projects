# inputf=in/dots2.ppm
inputf=in/lines_100x100.ppm
output=out/out.ppm
# method=naive_method
# method=improved_method
method=pq_with_map
# method=pq_accurate
render=greyscale
# render=grey_bands
# render=rainbow
# render=hot_cold

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

