CPP=g++ --std=c++11

# -g3 debug flag
CFLAGS= -Wall -g3


all : tournoi

tournoi : main.o Tournoi.o Partie.o Joueur.o
	$(CPP) $(CFLAGS) -o $@ $^

main.o : main.cpp
	$(CPP) $(CFLAGS) -c $<

Tournoi.o : Tournoi.cpp Tournoi.hpp
	$(CPP) $(CFLAGS) -c $<

Partie.o : Partie.cpp Partie.hpp
	$(CPP) $(CFLAGS) -c $<

Joueur.o : Joueur.cpp Joueur.hpp
	$(CPP) $(CFLAGS) -c $<

clean :
	rm -Rf *.o tournoi

test: all
	cat test_3J test_4J | ./tournoi

valgrind_extreme: all
	valgrind --leak-check=full --show-leak-kinds=all --leak-resolution=high --track-origins=yes --vgdb=yes ./tournoi

# mem chek
valgrind_extreme_test: all
	cat test_3J test_4J | valgrind --leak-check=full --show-leak-kinds=all --leak-resolution=high --track-origins=yes --vgdb=yes ./tournoi
