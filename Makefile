CC=gcc

all : lab3
	
lab3: command.o main.o string_parser.o
	$(CC) -o $@ $^
	gcc -o lab3 command.o main.o string_parser.o
	
main.o: main.c
	$(CC) -c $^
	
string_parser.o: string_parser.c string_parser.h
	$(CC) -c $<

command.o: command.c command.h
	$(CC) -c $<
	
clean:
	rm -f core *.o lab3
