# fil-rouge-aap
Projet réalisé par : Jinhong Zhang, Mathis Rimbert, Mohammed-Ayoub Bouzid, Marie Tanavelle

**Pour compiler les codes :  L'utilisation de la commande "make" entrainera la création de 3 exécutables correspondant aux 3 progammes à développer selon le cahier des charges**

## Programme 1 tttree :
Pour exécuter le fichier de test associé au programme 1 et fourni dans le cahier des charges veuillez rentrer les commandes :  *chmod a+x ./tttree/test_tttree.sh* et *./tttree/test_tttree.sh*

## Programme 2 sm-refresh :
Pour exécuter le fichier de test associé au programme 2 et détaillé dans le compte-rendu fourni avec l'archive, veuillez rentrer les commandes : *make test.exe* et *./test.exe*
Pour passer en mode DEBUG : exécuter dans la console **(commande valable uniquement sous Linux)** la commande *export DEBUG=1*, puis exécuter le programme normalement.
Pour sortir du mode DEBUG : exécuter dans la console **(commande valable uniquement sous Linux)** la commande *unset DEBUG*, puis exécuter le programme normalement.

Pour modifier le chemin de génération de l'image : exécuter dans la console **(commande valable uniquement sous Linux)** la commande *export PATH="Votre_Chemin"*, puis exécuter le programme normalement

## Programme 3 sm-bot :
Lors de l'exécution du programme merci de rentrer l'état actuel du super-morpion au format FEN (voir cahier des charges) ainsi que le temps restant **en secondes** pour jouer. La profondeur de l'algorithme négamax dépend du temps restant selon une règle définie dans le compte-rendu associé à cette archive.


