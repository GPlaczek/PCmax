
main:
	g++ -o bin/main src/main.cpp src/evolutionary.cpp src/greedy.cpp src/brute.cpp

clean:
	rm -rf bin/*
