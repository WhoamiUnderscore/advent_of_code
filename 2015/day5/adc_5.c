#include<stdio.h>
#include<string.h>

typedef struct {
  char a;
  char b;
  int index;
} Pair;

const bool PART_ONE = true;
const char VOWELS[6] = "aeiou";
const Pair EXCLUDE_CHARS[4] = { 
  { 'a', 'b', 0 },
  { 'c', 'd', 0 },
  { 'p', 'q', 0 },
  { 'x', 'y', 0 },
};


// bool value_contain_exclude_chars(char* val) {
//   int len = sizeof(EXCLUDE_CHARS) / sizeof(EXCLUDE_CHARS[0]);
//
//   for ( size_t i = 0; i < len; i++ ) {
//     if ( strcmp(val, EXCLUDE_CHARS[i]) == 0 ) {
//       return true;
//     }
//   }
//
//   return false;
// }



bool value_contain_in_pairs(Pair p, const Pair* pairs, int len) {
  char val[3] = { p.a, p.b, '\0' };

  for ( size_t i = 0; i < len; i++ ) {
    char ref[3] = { pairs[i].a, pairs[i].b, '\0' };
    if ( strcmp(val, ref) == 0 ) {
      if ( PART_ONE ) {
        return true;
      } else if ( p.index > pairs[i].index + 1 ) {
        return true;
      }
    }
  }

  return false;
}

bool is_input_valid_part_1(char* input) {
  int voyel_count = 0;
  bool has_double_letter = false;
  bool contain_exclude_char = false;

  for ( int i = 0; input[i+1] != '\0'; i++ ) {
    char letter1 = input[i];
    char letter2 = input[i+1];

    if ( letter1 == letter2 ) {
      has_double_letter = true;
    }

    Pair p = { letter1, letter2, 0 };
    if ( !contain_exclude_char && value_contain_in_pairs(p, EXCLUDE_CHARS, 4) ) {
      contain_exclude_char = true;
    }

    if ( strchr(VOWELS, letter1 ) != NULL ) {
      voyel_count++;
    }
  }

  return voyel_count >= 3 && has_double_letter && !contain_exclude_char;
}

bool is_input_valid_part_2(char* input) {
  int input_len = strlen(input);
  bool letter_repeate = false;
  bool pair_repeate = false;

  Pair pairs[20] = { 0 };
  int pairs_count = 0;
  
  for ( int i = 0; input[i+1] != '\0'; i++ ) {
    if ( !letter_repeate && i+2 < input_len && input[i] == input[i+2] ) {
      letter_repeate = true;
    }

    if ( !pair_repeate ) {
      Pair p = { input[i], input[i+1], i };

      if ( value_contain_in_pairs(p, pairs, pairs_count) ) {
        pair_repeate = true;
      } else {
        pairs[pairs_count++] = p;
      }
    }
  }

  return letter_repeate && pair_repeate;
}

int main() {
  FILE *file = fopen("data", "r");

  char input[20];
  int cnt_pt_1 = 0;
  int cnt_pt_2 = 0;

  if ( file != NULL) {
    while( fgets(input, sizeof(input), file) ) {
      /* Part 1 */
      if ( is_input_valid_part_1(input) ) {
        cnt_pt_1++;
      }

      /* Part 2 */
      if ( is_input_valid_part_2(input) ) {
        cnt_pt_2++;
      }
    }

    fclose(file);
  }

  printf("Part 1 => %d\nPart 2 => %d\n", cnt_pt_1, cnt_pt_2);

  return 0;
}
