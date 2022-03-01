objects = Interface.o Log.o LogManager.o LogStream.o
linkflags = -ansi -pedantic -Wall -g #-DMAP
flags = $(linkflags) -std=c++11

main: main.o $(objects)
	g++ $(linkflags) -o analog main.o $(objects)
jorge: main_jorge.o $(objects)
	g++ $(linkflags) -o analog main_jorge.o $(objects)
mario: main_mario.o $(objects)
	g++ $(linkflags) -o analog main_mario.o $(objects)
	
main_jorge.o: main_jorge.cpp Interface.o
	g++ $(flags) -c -o main_jorge.o main_jorge.cpp
main.o: main.cpp
	g++ $(flags) -c -o main.o main.cpp

Interface.o: Interface.cpp Interface.h
	g++ $(flags) -c -o Interface.o Interface.cpp
Log.o: Log.cpp Log.h
	g++ $(flags) -c -o Log.o Log.cpp
LogManager.o: LogManager.cpp LogManager.h Log.o
	g++ $(flags) -c -o LogManager.o LogManager.cpp
LogStream.o: LogStream.h LogStream.cpp Log.o
	g++ $(flags) -c -o LogStream.o LogStream.cpp

gitit:
	git add .
	git commit
	git pull
	git push
clear:
	rm *.o
	rm sejours
