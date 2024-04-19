COMPILER_FLAGS=--std=c89 -Wall

hangman: main.c guesses_vec.o word_loader.o
	gcc $(COMPILER_FLAGS) $^ -o $@ 

word_loader.o: word_loader.c
	gcc $(COMPILER_FLAGS) -c $^ -o $@

guesses_vec.o: guesses_vec.c
	gcc $(COMPILER_FLAGS) -c $^ -o $@

clean:
	rm *.o
