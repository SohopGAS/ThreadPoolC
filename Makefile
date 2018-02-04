all: main.o
	gcc main.o -o main -pthread
main: main.cpp
	gcc -c main.cpp -o main.o
threadpool: threadpool.h
	gcc -c threadpool.h -o threadpool.o
func: func.h
	gcc -c func.h -o func.o
log: log.h
	gcc -c log.h -o log.o
clean:
	rm -rf main.o threadpool.o func.o log.o
