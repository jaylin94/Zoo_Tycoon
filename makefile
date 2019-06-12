CXX = g++
CXXFLAGS = -std=c++11
OBJS = game.o zoo.o animal.o tiger.o penguin.o turtle.o tycoon.o
SRCS = game.cpp zoo.cpp animal.cpp tiger.cpp penguin.cpp turtle.cpp tycoon.cpp
HEADERS = game.hpp zoo.hpp animal.hpp tiger.hpp penguin.hpp turtle.hpp

tycoon:${OBJS}
	${CXX} ${CXXFLAGS} ${OBJS} -o tycoon

${OBJS}: ${SRCS} ${HEADERS}
	${CXX} ${CXXFLAGS} -c ${@:.o=.cpp}

clean:
	rm *.o tycoon

make zip:
	zip -D Tycoon.zip *.cpp *.hpp makefile