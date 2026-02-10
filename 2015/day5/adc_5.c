#include<stdio.h>
#include<string.h>

char VOWELS[6] = "aeiou";
const char EXCLUDE_CHARS[10] = "abcdpqxy\0";

int verify_vowels(char input[]) {
  int counter = 0;
  for (int i = 0; input[i] != '\0'; i++) {
    for ( int j = 0; VOWELS[j] != '\0'; j++) {
      if ( input[i] == VOWELS[j] ) {
        counter++;
      }
    }
  }

  if ( counter >= 3 ) {
    return 0;
  }

  return 1;
}

int is_input_valid(char input[]) {
  bool has_exclude_chars = false;
  bool has_pair = false;

  for ( int i = 0; input[i+1] != '\0'; i++) {
    char first_character = input[i];
    char second_character = input[i + 1];

    if ( first_character == second_character ) {
      has_pair = true;
    }

    for ( int c = 0; EXCLUDE_CHARS[c] != '\0'; c+=2) {
      char first_exclude_char = EXCLUDE_CHARS[c];
      char second_exclude_char = EXCLUDE_CHARS[c+1];

      if ( first_character == first_exclude_char && second_character == second_exclude_char) {
        has_exclude_chars = true;
      }
    }
  }

  if ( !has_pair || verify_vowels(input) == 1 || has_exclude_chars ) {

    return 1;
  }

  return 0;
}

int main() {
  FILE *file = fopen("data", "r");

  char input[20];
  int counter = 0;

  if ( file != NULL) {
    while( fgets(input, sizeof(input), file) ) {
      if ( is_input_valid(input) == 0 ) {
        counter++;
      }
    }

    fclose(file);
  }

  printf("%d\n", counter);

  return 0;
}
