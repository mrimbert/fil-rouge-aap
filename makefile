PWD=$(shell pwd)
REP=$(shell basename $(PWD))
SOURCES=$(shell cat makefile_sources)
CIBLE=$(REP).exe
CFLAGS=-Wall -Wno-format-overflow -Wno-format-truncation

# makefile générique pour produire un code source 
# dont le nom correspond au nom du répertoire qui le contient

all: tttree
	@echo "Le programme tttree a été produit dans le répertoire $(REP)"

clean: 
	@echo "Nettoyage de tttree"
	@rm -rf tttree.exe
	@rm -rf g1.dot
	@rm -rf g2.dot
	@rm -rf g1.png
	@rm -rf g2.png
	
tttree: tttree.c ./utils/morpion.c
	@echo "Le programme tttree.exe a été produit"
	gcc $(CFLAGS) tttree.c ./utils/morpion.c -o tttree.exe

