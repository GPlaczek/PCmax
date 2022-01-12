
main:
	g++ -o bin/main src/main.cpp src/genetic.cpp src/greedy.cpp src/brute.cpp

clean:
	rm -rf bin/*
