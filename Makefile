#commandLine makefile

#Variables
COMPILE = g++
FLAGS = -g -W -Wall -Werror -ansi -pedantic -std=c++11
DIR = mkdir bin; mv rshell bin;

all: src/main.cpp src/AndObj.o src/OrObj.o src/SemiObj.o src/Command.o src/TestObj.o src/Pipe.o src/InRed.o src/OutRed.o src/Composite.o
	$(COMPILE) $(FLAGS) -o rshell  src/main.cpp AndObj.o OrObj.o SemiObj.o Command.o TestObj.o Pipe.o InRed.o OutRed.o Composite.o; $(DIR)
	
src/Composite.o:  src/Composite.cpp  src/Composite.h
	$(COMPILE) $(FLAGS) -c  src/Composite.cpp

src/AndObj.o:  src/AndObj.cpp  src/AndObj.h  src/Base.h
	$(COMPILE) $(FLAGS) -c  src/AndObj.cpp
	
src/OrObj.o:  src/OrObj.cpp  src/OrObj.h  src/Base.h
	$(COMPILE) $(FLAGS) -c  src/OrObj.cpp
	
src/SemiObj.o:  src/SemiObj.cpp  src/SemiObj.h  src/Base.h
	$(COMPILE) $(FLAGS) -c  src/SemiObj.cpp
	
src/Command.o:  src/Command.cpp  src/Command.h  src/Base.h
	$(COMPILE) $(FLAGS) -c  src/Command.cpp
	
src/TestObj.o:  src/TestObj.cpp  src/TestObj.h  src/Base.h
	$(COMPILE) $(FLAGS) -c  src/TestObj.cpp
	
src/InRed.o: src/InRed.cpp src/InRed.h src/Base.h
	$(COMPILE) $(FLAGS) -c  src/InRed.cpp
	
src/OutRed.o: src/OutRed.cpp src/OutRed.h src/Base.h
	$(COMPILE) $(FLAGS) -c  src/OutRed.cpp
	
src/Pipe.o: src/Pipe.cpp src/Pipe.h src/Base.h
	$(COMPILE) $(FLAGS) -c  src/Pipe.cpp
	
run:
	bin/rshell

clean:
	rm -rf *~ *.o a.out src/*~ src/*.o src/a.out bin/rshell; rmdir bin;
