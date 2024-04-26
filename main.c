#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "word_loader.h"
#include "game_state.h"

const char *FILE_PATH = "words.txt";
const unsigned int MAX_INCORRECT_GUESSES = 6;

typedef enum {
  READ_GUESS_RESULT_SUCCESS,
  READ_GUESS_RESULT_INVALID_CHARACTER,
  READ_GUESS_RESULT_TOO_LONG,
  READ_GUESS_RESULT_TOO_SHORT,
  READ_GUESS_RESULT_NO_GUESS,
} ReadGuessResult;


void print_prompt(const char *answer, GuessHistory *guess_history, ReadGuessResult guess_result, unsigned int incorrect_guess_count) {
  /* Clear screen and jump up to beginning of screen. */
  printf("\x1b[2J\x1b[H");
  unsigned i;
  printf("Solution: ");
  for (i = 0; answer[i] != '\0'; i++) {
    if (guess_history_is_previous_character_guess(guess_history, answer[i])) 
      printf("%c", answer[i]);
    else 
      printf("_");
  }
  printf("\nPrevious Guesses: ");
  guess_history_print(guess_history);
  printf("\nIncorrect guesses left: %u\n", MAX_INCORRECT_GUESSES - incorrect_guess_count);
  if (guess_result == READ_GUESS_RESULT_INVALID_CHARACTER) 
    printf("Your previous guess contained characters that weren't letters!\n");
  if (guess_result == READ_GUESS_RESULT_TOO_LONG)
    printf("Your previous guess was too long, the answer has less characters\n");
  printf("Enter a guess: ");
}

ReadGuessResult read_guess(char *result, unsigned int length) {
  char c;
  unsigned i=0;
  c = tolower(getchar());
  while (c !='\n') {
    if (c < 'a' || c > 'z') {
      while(getchar() != '\n');
      return READ_GUESS_RESULT_INVALID_CHARACTER;
    }
    if (i>length) {
      /* result is too long, need to clear
       * stdin
       */
      while(getchar() != '\n');
      return READ_GUESS_RESULT_TOO_LONG;
    }

    result[i] = c;
    i++;
    c = tolower(getchar());
  }
  result[i] = '\0';
  return READ_GUESS_RESULT_SUCCESS;
}

int is_incorrect_guess(char *answer, char* guess) {
  unsigned i;
  if (guess[1] == '\0') {
    /* Need to check for a character match */
    for(i=0; answer[i] != '\0'; i++) {
      if (answer[i] == guess[0])
        return 0;
    }
    return 1;
  } else {
    return strcmp(answer, guess);
  }
}

int main(void) {
  char *answer = get_random_word_from_file(FILE_PATH);
  if (!answer) {
    fprintf(stderr, "Issues loading word.\n");
    return 1;
  }

  GuessHistory guess_history = guess_history_create();
  
  char guess[16];
  unsigned int incorrect_guess_count = 0;
  ReadGuessResult read_result = READ_GUESS_RESULT_NO_GUESS;
  while (1) {
    print_prompt(answer, &guess_history, read_result, incorrect_guess_count);
    read_result = read_guess(guess, strlen(answer));
    if (read_result == READ_GUESS_RESULT_SUCCESS) {
      guess_history_add_guess(&guess_history, guess);
      if (is_incorrect_guess(answer, guess))
        incorrect_guess_count++; 
    }
    if (incorrect_guess_count == MAX_INCORRECT_GUESSES) {
      printf("You loose, the answer was %s\n", answer);
      break;
    }
    if (guess_history_check_win(&guess_history, answer)) {
      printf("You win\n");
      break;
    }
  }
  free(answer);

  return 0;
}
