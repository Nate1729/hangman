#include <stdio.h>

#include "guesses_vec.h"

GuessesVec guesses_vec_init() {
  return (GuessesVec){.length = 0};
}

int guesses_vec_add_guess(GuessesVec* vec, char guess) {
  unsigned i;
  for (i=0; i<vec->length; i++) {
    if (vec->guesses[i] == guess) {
      return 0;
    }
  }

  if (guess >=97 && guess <= 122) {
    /* Is an ascii lower-case character */
    vec->guesses[vec->length] = guess;
    vec->length++;
    return 1;
  } 
  return -1;
}

void guesses_vec_print(GuessesVec* vec) {
  unsigned i=0;
  if (vec->length > 0) {
    printf("%c", vec->guesses[i]);
  }

  for(i=1; i<vec->length; i++) {
    printf(" %c", vec->guesses[i]);
  }
}

typedef char ascii_lowercase_letter;

int guesses_vec_is_previous_guess(GuessesVec* vec, ascii_lowercase_letter guess) {
  unsigned i;
  for (i=0; i<vec->length; i++) {
    if (vec->guesses[i] == guess) {
      return 1;
    }
  }
  return 0;
}
