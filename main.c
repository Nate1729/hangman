#include <stdio.h>
#include <string.h>
#include <time.h>

#include "guesses_vec.h"


const char* FILE_PATH = "words.txt";

int main(void) {
  GuessesVec guesses = guesses_vec_init();

  char buffer[2048];
  FILE *f = fopen(FILE_PATH, "r");
  if (!f) {
    fprintf(stderr, "I couldn't open the file.\n");
    return 1;
  }

  char c;
  unsigned word_count=0;
  do {
    c = fgetc(f);
    if (c == '\n')
      word_count++;

  } while (c !=EOF);
  if (word_count == 0) {
    fprintf(stderr, "there are no words to load\n");
    fclose(f);
    return 1;
  }

  srand(time(NULL));
  unsigned index_word = (unsigned)rand() % word_count;
  printf("Pick the word on line: %u\n", index_word);

  if (fseek(f, 0, SEEK_SET)) {
    fprintf(stderr, "Couldn't seek to beginning of file\n");
    fclose(f);
    return 1;
  }

  char word[20];
  unsigned line_count=1;
  do {
    c= fgetc(f);

    if (c == '\n')
      line_count++;

    if (line_count == index_word)
      break;

  } while (c !=EOF);
  if (c == EOF) {
    fprintf(stderr, "The world is on fire\n");
    fclose(f);
  }

  /* Should be a large enough buffer.
   * This fails when a word is too long
   */
  fgets(word, 20, f);
  unsigned length = strlen(word);
  word[length] = 0;
  word[length-1] = '\0';

  fclose(f);


  printf("The random word is: %s\n", word);

  return 0;
}
