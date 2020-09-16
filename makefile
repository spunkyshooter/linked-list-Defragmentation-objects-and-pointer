output: assignment.o list.o
	g++ assignment.cpp list.cpp -g

assignment.o: assignment.cpp
	g++ -c assignment.cpp -g

list.o: list.cpp list.h
	g++ -c list.cpp -g

clean:
	rm *.o