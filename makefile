all:  task

task: main.o prefix_table.o
	gcc -o task main.o prefix_table.o

prefix_table.o: prefix_table.c prefix_table.h
	gcc -c prefix_table.c

main.o: main.c prefix_table.h
	gcc -c main.c
	
clean:
	rm -f *.o *.so tesk