#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void update_floor(int *floor, char parenthesis) {
  if ( parenthesis == 40 ) {
    *floor += 1;
  } else if ( parenthesis == 41 ) {
    *floor -= 1;
  }
}

bool get_first_basement_char(int floor) {
  if ( floor < 0) return true;

  return false;
}

int main() {
  FILE *data = fopen("data", "r");

  if ( data == NULL ) {
    printf("File not opened.");
    return 1;
  }

  int floor = 0;
  int i = 0;

  char parenthesis;
  while ((parenthesis =fgetc(data)) != EOF ) {
    update_floor(&floor, parenthesis);

    // PART 2
    if ( get_first_basement_char(floor) ) {
      printf("%d-> %d\n", i+1, floor);
      return 0;
    };

    i += 1;
  }

  printf("%d\n", floor);
  return 0;
}

