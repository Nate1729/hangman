hangman: main.c guesses_vec.o
	gcc --std=c89 $^ -o $@ 

guesses.o: guesses_vec.h guesses_vec.c
	gcc --std=c89 $^ -o $@
