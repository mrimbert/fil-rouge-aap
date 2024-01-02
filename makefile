PWD=$(shell pwd)
REP=$(shell basename $(PWD))
SOURCES=$(shell cat makefile_sources)
CIBLE=$(REP).exe
CFLAGS=-Wall -Wno-format-overflow -Wno-format-truncation

# makefile générique pour produire un code source 
# dont le nom correspond au nom du répertoire qui le contient

all: $(CIBLE) tttree
	@echo "Le programme $(CIBLE) a été produit dans le répertoire $(REP)"

clean: 
	@echo "Nettoyage de $(CIBLE)"
	@rm -rf $(CIBLE)
	
tttree: tttree.c ./utils/morpion.c
	@echo "Le programme tttree.exe a été produit"
	gcc $(CFLAGS) tttree.c ./utils/morpion.c -o tttree.exe

