servermain: servermain.o serverclass.o
	g++ -o servermain servermain.o serverclass.o -std=c++11 
servermain.o: servermain.cc package.hpp
	g++ -c servermain.cc -std=c++11 -pthread
serverclass.o: serverclass.cc package.hpp
	g++ -c serverclass.cc