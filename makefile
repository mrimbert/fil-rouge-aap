#fichier makefile
all : main.exe

main.exe : main.c morpion.h
	gcc main.c -o main.exe
	
.PHONY : clean	
clean : 
	rm -rf checksum.exe collected_data
