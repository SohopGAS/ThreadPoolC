all: main.o 
	g++ main.o -o main -pthread
main: main.cpp
	g++ -c main.cpp -o main.o
threadpool: threadpool.h
	g++ -c threadpool.h -o threadpool.o
func: func.h
	g++ -c func.h -o func.o
log: log.h
	g++ -c log.h -o log.o
clean:
	rm -rf main.o threadpool.o func.o log.o
