#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "game_state.h"

GuessHistory guess_history_create() {
  return (GuessHistory){.guess_count=0, .guess_limit=MAX_GUESSES};
}

/** Loop over the guess history and compare against all guesses
 * until it finds a match. If it does find a match, it will return 1.
 * If no match is found, return 0;
 */
unsigned guess_history_is_previous_guess(GuessHistory *guess_history, char *guess) {
  unsigned i;
  for (i=0; i<guess_history->guess_count; i++) {
    if (strcmp(guess_history->guesses[i], guess) == 0) {
      return 1;
    }
  }

  return 0;
}

unsigned guess_history_is_previous_character_guess(GuessHistory *guess_history, char guess) {
  unsigned i;
  char *history_guess;
  for (i=0; i<guess_history->guess_count; i++) {
    history_guess = guess_history->guesses[i];
    if (history_guess[1] == '\0' && history_guess[0] == guess) {
      return 1;
    }
  }
  return 0;
}

void guess_history_add_guess(GuessHistory *guess_history, char *guess) {
  if (guess_history_is_previous_guess(guess_history, guess))
    return;

  strcpy(guess_history->guesses[guess_history->guess_count], guess);

  guess_history->guess_count++;
}

void guess_history_print(GuessHistory *guess_history) {
  unsigned i;
  printf("[");
  for (i=0; i<guess_history->guess_count; i++) {
    if (i == 0)
      printf("%s", guess_history->guesses[i]);
    else
     printf(" %s", guess_history->guesses[i]);
  }
  printf("]\n");
}

unsigned int guess_history_count_incorrect_guesses(GuessHistory *guess_history, const char *answer) {
  unsigned i, count;
  char test_array[2] = {'z', '\0'};

  count = 0;
  for (i=0; answer[i] != '\0'; i++) {
    test_array[0] = answer[i];
    if (guess_history_is_previous_guess(guess_history, test_array))
      count++;
  }
  
  return count;
}

int guess_history_check_win(GuessHistory *guess_history, char* answer) {
  printf("Checking for win.\n");
  char *last_guess = guess_history->guesses[guess_history->guess_count-1];
  unsigned i;
  char test_array[] = {'f', '\0'};
  if (last_guess[1] != '\0') {
    /* The last guess was a word, we just need to strcmp */
    return !strcmp(last_guess, answer);
  }

  /* Now we need to do the long, boring check */
  for (i=0; answer[i] != '\0'; i++) {
    test_array[0] = answer[i];
    if (!guess_history_is_previous_guess(guess_history, test_array)) {
      return 0;
    }
  }
  return 1;
}
