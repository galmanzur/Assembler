all: assembler

assembler: file_service.o first_pass.o macro_repo.o main.o manager.o parser.o pre_assembler.o second_pass.o symbol_repo.o addressing_service.o process_data.o technical_functions.o debug.o encoding_service.o encoding_repo.o
	gcc -ansi -Wall -pedantic -o assembler file_service.o first_pass.o macro_repo.o main.o manager.o parser.o pre_assembler.o second_pass.o symbol_repo.o addressing_service.o process_data.o technical_functions.o debug.o encoding_service.o encoding_repo.o

manager.o: manager.c manager.h
	gcc -ansi -Wall -pedantic -c manager.c

symbol_repo.o: symbol_repo.c symbol_repo.h
	gcc -ansi -Wall -pedantic -c symbol_repo.c

file_service.o: file_service.c file_service.h
	gcc -ansi -Wall -pedantic -c file_service.c

first_pass.o: first_pass.c first_pass.h
	gcc -ansi -Wall -pedantic -c first_pass.c

macro_repo.o: macro_repo.c macro_repo.h
	gcc -ansi -Wall -pedantic -c macro_repo.c

main.o: main.c main.h
	gcc -ansi -Wall -pedantic -c main.c

parser.o: parser.c parser.h
	gcc -ansi -Wall -pedantic -c parser.c

pre_assembler.o: pre_assembler.c pre_assembler.h
	gcc -ansi -Wall -pedantic -c pre_assembler.c

second_pass.o: second_pass.c second_pass.h
	gcc -ansi -Wall -pedantic -c second_pass.c

debug.o: debug.c debug.h
	gcc -ansi -Wall -pedantic -c debug.c

addressing_service.o: addressing_service.c addressing_service.h
	gcc -ansi -Wall -pedantic -c addressing_service.c	

process_data.o: process_data.c process_data.h
	gcc -ansi -Wall -pedantic -c process_data.c

technical_functions.o: technical_functions.c technical_functions.h
	gcc -ansi -Wall -pedantic -c technical_functions.c	

encoding_service.o: encoding_service.c encoding_service.h
	gcc -ansi -Wall -pedantic -c encoding_service.c

encoding_repo.o: encoding_repo.c encoding_repo.h
	gcc -ansi -Wall -pedantic -c encoding_repo.c	


clean:
	rm -f *.o assembler
