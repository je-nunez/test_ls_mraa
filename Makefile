
CC = gcc
CFLAGS = -g -fpic -Wall -I /usr/local/include/
LDFLAGS = -L /usr/local/lib/  -l mraa


.SILENT:  help


help:
	echo "Makefile help"	
	echo -e "Possible make targets:\n"	
	echo "    make compile"	
	echo -e "         Compile the program.\n"	
	echo "    make clean"	
	echo -e "         Remove compiled and binary-object files.\n"	


compile: ls_mraa.c
	$(CC)  $(CFLAGS) -o  ls_mraa  ls_mraa.c  $(LDFLAGS)



.PHONY : clean


clean:
	-rm -f ls_mraa

