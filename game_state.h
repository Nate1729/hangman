#ifndef GAME_STATE_H
#define GAME_STATE_H

#define MAX_GUESSES 16
#define MAX_WORD_SIZE 16

typedef struct {
  char guesses[MAX_GUESSES][MAX_WORD_SIZE];
  unsigned int guess_count;
  unsigned int guess_limit;
} GuessHistory;

GuessHistory guess_history_create();

unsigned guess_history_is_previous_guess(GuessHistory *guess_history, char *guess);
unsigned guess_history_is_previous_character_guess(GuessHistory *guess_history, char guess);
void guess_history_add_guess(GuessHistory *guess_history, char* guess);
/** print to stdout what is in the guess history
 */
void guess_history_print(GuessHistory *guess_history);
unsigned int guess_history_count_incorrect_guesses(GuessHistory *guess_history, const char *answer);
int guess_history_check_win(GuessHistory *guess_history, char* answer);


typedef struct {
  const char *answer;
  GuessHistory guess_history;
} GameState;

GameState game_state_create(const char* answer);


#endif
