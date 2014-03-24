all:
	mkdir -p ./bin
	g++ -o ./bin/2048 ./src/2048.cc

clean:
	rm -R ./bin