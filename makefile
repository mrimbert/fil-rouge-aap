CIBLE=$(REP).exe
CFLAGS=-Wall -Wno-format-overflow -Wno-format-truncation


all: tttree sm-refresh.exe sm-bot.exe
	@echo "Le programme tttree a été produit dans le répertoire $(REP)"
	@echo "Le programme sm-refresh a été produit dans le répertoire $(REP)"

clean: 
	@echo "Nettoyage de tttree"
	@rm -rf tttree.exe
	@rm -rf g1.dot
	@rm -rf g2.dot
	@rm -rf g1.png
	@rm -rf g2.png
	
	@echo "Nettoyage de sm-refresh"
	@rm -rf sm-refresh.exe
	@rm -rf g.dot
	@rm -rf g.png
	
	@echo "Nettoyage de test"
	@rm -rf test.exe

tttree: tttree.c ./utils/morpion.c
	@echo "Le programme tttree.exe a été produit"
	gcc $(CFLAGS) tttree.c ./utils/morpion.c -o tttree.exe

sm-refresh.exe: ./sm-refresh/sm-refresh.o ./sm-refresh/minimax.o ./utils/super_morpion.o ./utils/morpion.o
	@echo "Le programme sm-refresh.exe a été produit"
	gcc -Wall -o $@ $^


test.exe: ./sm-refresh/test.o ./utils/morpion.o ./sm-refresh/minimax.o ./utils/super_morpion.o 
	@echo "Le programme test.exe a été produit"
	gcc -Wall -o $@ $^
	
sm-bot.exe : sm-bot.o negamax.o ./utils/super_morpion.o ./utils/morpion.o
	@echo "Le programme sm-bot.exe a été produit"
	gcc -Wall -o $@ $^


%.o: %.c
	gcc -c $< -o $@

