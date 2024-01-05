REP=$(shell basename $(PWD))
CIBLE=$(REP).exe
CFLAGS=-Wall -Wno-format-overflow -Wno-format-truncation

# makefile générique pour produire un code source 
# dont le nom correspond au nom du répertoire qui le contient

all: tttree sm-refresh
	@echo "Le programme tttree a été produit dans le répertoire $(REP)"
	@echo "Le programme sm-refresh a été produit dans le répertoire $(REP)"

clean: 
	@echo "Nettoyage de tttree"
	@rm -rf tttree.exe
	@rm -rf g1.dot
	@rm -rf g2.dot
	@rm -rf g1.png
	@rm -rf g2.png
	
	@echo"Nettoyage de sm-refresh"
	@rm -rf sm-refresh.exe
	@rm -rf g.dot
	@rm -rf g.png
	
	@echo "Nettoyage de test"
	@rm -rf test.exe

tttree: tttree.c ./utils/morpion.c
	@echo "Le programme tttree.exe a été produit"
	gcc $(CFLAGS) tttree.c ./utils/morpion.c -o tttree.exe

sm-refresh: ./sm-refresh/sm-refresh.c ./sm-refresh/minimax.c ./utils/super_morpion.c ./utils/morpion.c
	@echo "Le programme sm-refresh.exe a été produit"
	gcc $(CFLAGS) ./sm-refresh/sm-refresh.c ./sm-refresh/minimax.c ./utils/super_morpion.c ./utils/morpion.c -o sm-refresh.exe

test: ./sm-refresh/test.c ./utils/morpion.c ./sm-refresh/minimax.c ./utils/super_morpion.c 
	@echo "Le programme test.exe a été produit"
	gcc $(CFLAGS) ./sm-refresh/test.c ./utils/morpion.c ./sm-refresh/minimax.c ./utils/super_morpion.c -o test.exe

