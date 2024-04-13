#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "word_loader.h"


char* get_random_word_from_file(const char* path){
  FILE *f = fopen(path, "r");
  if (!f) {
    fprintf(stderr, "I couldn't open the file.\n");
    return NULL;
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
    return NULL;
  }

  srand(time(NULL));
  unsigned index_word = (unsigned)rand() % word_count;
  /* For debugging
   * printf("Pick the word on line: %u\n", index_word);
   */

  if (fseek(f, 0, SEEK_SET)) {
    fprintf(stderr, "Couldn't seek to beginning of file\n");
    fclose(f);
    return NULL;
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
  size_t length = strlen(word);
  word[length] = 0;
  word[length-1] = '\0';
  fclose(f);


  /* Set up return value
   */
  char* final_ptr = malloc(length+1);
  memcpy(final_ptr, word, length+1);
  return final_ptr;
}
