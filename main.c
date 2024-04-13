#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "guesses_vec.h"
#include "word_loader.h"


const char* FILE_PATH = "words.txt";

void print_prompt(const char* answer, GuessesVec* guesses) {
  unsigned i;
  printf("Solution: ");
  for (i=0; answer[i] !='\0'; i++) {
    if (guesses_vec_is_previous_guess(guesses, answer[i])) {
      printf("%c", answer[i]);
    } else {
      printf("_");
    }
  }
  printf("\nPrevious Guesses: ");
  guesses_vec_print(guesses);
  printf("\nEnter a guess: ");
}

int main(void) {
  GuessesVec guesses = guesses_vec_init();
  char* answer = get_random_word_from_file(FILE_PATH);
  if (!answer) {
    fprintf(stderr, "Issues loading word.\n");
    return 1;
  }

  unsigned quit = 0;
  char c, buf;
  while(!quit) {
    print_prompt(answer, &guesses);
    c = getchar();
    guesses_vec_add_guess(&guesses, c);
    while (getchar() != '\n');
  }

  free(answer);
  return 0;
}
