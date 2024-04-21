#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "guesses_vec.h"
#include "word_loader.h"

const char *FILE_PATH = "words.txt";
const unsigned int MAX_INCORRECT_GUESSES = 6;

void print_prompt(const char *answer, GuessesVec *guesses) {
  /* Clear screen and jump up to beginning of screen. */
  printf("\x1b[2J\x1b[H");
  unsigned i;
  printf("Solution: ");
  for (i = 0; answer[i] != '\0'; i++) {
    if (guesses_vec_is_previous_guess(guesses, answer[i])) {
      printf("%c", answer[i]);
    } else {
      printf("_");
    }
  }
  printf("\nPrevious Guesses: ");
  guesses_vec_print(guesses);
  printf("\nIncorrect guesses left: %u\n", MAX_INCORRECT_GUESSES - guesses_vec_count_incorrect_guesses(guesses, answer));
  printf("Enter a guess: ");
}

int main(void) {
  GuessesVec guesses = guesses_vec_init();
  char *answer = get_random_word_from_file(FILE_PATH);
  if (!answer) {
    fprintf(stderr, "Issues loading word.\n");
    return 1;
  }

  char c;
  while (1) {
    print_prompt(answer, &guesses);
    if (has_won(&guesses, answer)) {
      printf("\nYou Win!\n");
      break;
    }
    c = getchar();
    guesses_vec_add_guess(&guesses, c);
    if (guesses_vec_count_incorrect_guesses(&guesses, answer) > MAX_INCORRECT_GUESSES) {
      printf("\nYou Lose, the answer was %s\n", answer);
      break;
    }
    while (getchar() != '\n'); /*flush stdin*/
  }

  free(answer);
  return 0;
}
