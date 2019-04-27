all: clean create

create: main_fopen.c main_open.c
	gcc main_fopen.c -lpthread -o fopen
	gcc main_open.c -lpthread -o open

clean:
	rm -rf open fopen