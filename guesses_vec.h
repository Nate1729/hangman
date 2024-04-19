#ifndef GUESSES_VEC_H
#define GUESSES_VEC_H

typedef struct {
  /* Only 26 letters in the alphabet */
  char guesses[26];
  unsigned length;
} GuessesVec;


/* Initialize the guesses vec struct
 */
GuessesVec guesses_vec_init();

int guesses_vec_add_guess(GuessesVec* vec, char guess);
void guesses_vec_print(GuessesVec* vec);
int guesses_vec_is_previous_guess(GuessesVec* vec, char guess);

/* Check if the `GuessesVec` object is a win
 */
int has_won(GuessesVec* vec, const char* answer);

#endif
