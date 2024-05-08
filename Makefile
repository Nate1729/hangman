COMPILER_FLAGS=--std=c89 -Wall

hangman: main.c  word_loader.o game_state.o
	gcc $(COMPILER_FLAGS) $^ -o $@ 

word_loader.o: word_loader.c
	gcc $(COMPILER_FLAGS) -c $^ -o $@

game_state.o: game_state.c
	gcc $(COMPILER_FLAGS) -c $^ -o $@

clean:
	rm *.o
