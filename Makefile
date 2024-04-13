hangman: main.c guesses_vec.o word_loader.o
	gcc --std=c89 $^ -o $@ 

word_loader.o: word_loader.c
	gcc --std=c89 -c $^ -o $@

guesses_vec.o: guesses_vec.c
	gcc --std=c89 -c $^ -o $@

clean:
	rm *.o
