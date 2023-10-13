N=1000000
# N=4000000
# N=10000000

bin/fast_sieve: src/fast_sieve.cpp
	g++ src/fast_sieve.cpp -Wall -Wextra -o bin/fast_sieve

bin/big_sieve: src/big_sieve.cpp
	g++ src/big_sieve.cpp -Wall -Wextra -o bin/big_sieve

bin/cache: src/cache.cpp
	g++ src/cache.cpp -Wall -Wextra -o bin/cache

bin/darren: src/darren.cpp
	g++ src/darren.cpp -Wall -Wextra -o bin/darren

.PHONY: runf runb runc rund run
runf: bin/fast_sieve
	bin/fast_sieve < <(printf $N) > out/fast_sieve.txt
	cat out/fast_sieve.txt

runb: bin/big_sieve
	bin/big_sieve < <(printf $N) > out/big_sieve.txt
	cat out/big_sieve.txt

runc: bin/cache
	bin/cache < <(printf $N) > out/cache.txt
	cat out/cache.txt

rund: bin/darren
	bin/darren < <(printf $N) > out/darren.txt
	cat out/darren.txt

run: runf runb runc rund

.PHONY: timef timeb timec timed time
timef: bin/fast_sieve
	time bin/fast_sieve < <(printf $N) > out/fast_sieve.txt

timeb: bin/big_sieve
	time bin/big_sieve < <(printf $N) > out/big_sieve.txt

timec: bin/cache
	time bin/cache < <(printf $N) > out/cache.txt

timed: bin/darren
	time bin/darren < <(printf $N) > out/darren.txt

time: timef timeb timec timed

.PHONY: debugf debugb debugc debugd
debugf: bin/fast_sieve
	bin/fast_sieve < <(printf $N)

debugb: bin/big_sieve
	bin/big_sieve < <(printf $N)

debugc: bin/cache
	bin/cache < <(printf $N)

debugd: bin/darren
	bin/darren < <(printf $N)

.PHONY: clean
clean:
	rm ./bin/*
