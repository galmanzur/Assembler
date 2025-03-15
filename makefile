all: assembler

assembler: file_service.o first_pass.o macro_repo.o main.o manager.o parser.o pre_assembler.o second_pass.o symbol_repo.o
	gcc -ansi -Wall -pedantic -o assembler file_service.o first_pass.o macro_repo.o main.o manager.o parser.o pre_assembler.o second_pass.o symbol_repo.o

file_service.o: file_service.c file_service.h
	gcc -ansi -Wall -pedantic -c file_service.c

first_pass.o: first_pass.c first_pass.h
	gcc -ansi -Wall -pedantic -c first_pass.c

macro_repo.o: macro_repo.c macro_repo.h
	gcc -ansi -Wall -pedantic -c macro_repo.c

main.o: main.c main.h
	gcc -ansi -Wall -pedantic -c main.c

manager.o: manager.c manager.h
	gcc -ansi -Wall -pedantic -c manager.c

parser.o: parser.c parser.h
	gcc -ansi -Wall -pedantic -c parser.c

pre_assembler.o: pre_assembler.c pre_assembler.h
	gcc -ansi -Wall -pedantic -c pre_assembler.c

second_pass.o: second_pass.c second_pass.h
	gcc -ansi -Wall -pedantic -c second_pass.c

symbol_repo.o: symbol_repo.c symbol_repo.h
	gcc -ansi -Wall -pedantic -c symbol_repo.c

clean:
	rm -f *.o assembler
