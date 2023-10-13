.PHONY: all
all: bin/CheckCoin.jar bin/Coin.java

bin/CheckCoin.jar: src/*
	javac -d class src/*.java
	jar -cmf src/MANIFEST.MF bin/CheckCoin.jar -C class .

bin/Coin.java: example/Coin.java
	cp example/Coin.java bin/Coin.java

.PHONY: run edit coinedit clean
run: all
	cd bin && java -jar CheckCoin.jar

edit:
	nvim src/CheckCoin.java

coinedit:
	nvim example/Coin.java

clean:
	rm -rf bin/* class/*
