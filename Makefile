conway: conway.o
	g++ -Wall -Werror conway.o -o conway -lncurses

conway.o: conway.cpp
	g++  -c -g conway.cpp

clean:
	rm *.o conway
