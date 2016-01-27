FLAGS = -Wall -fexceptions -O3 -fpermissive -fno-strict-aliasing
TARGET = search_engine

all: search_engine.o main.o
	g++ $(FLAGS) -o $(TARGET) search_engine.o main.o

search_engine.o: search_engine.cpp search_engine.h
	g++ $(FLAGS) -c search_engine.cpp

main.o: main.cpp
	g++ $(FLAGS) -c main.cpp

clean:
	rm *.o