#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int calcule_surface_area(int l, int w, int h) {
  return ( 2*l*w ) + ( 2*w*h ) + ( 2*h*l );
}

int smaller_value(int l, int w, int h) {
  int all_values[3] = { l*w, l*h, h*w };
  int length = sizeof(all_values) / sizeof(all_values[0]);

  int min = all_values[0];

  for ( int i = 0; i < length; i++ ) {
    if ( all_values[i] != min && all_values[i] < min ) {
      min = all_values[i];
    }
  }

  return min;
}

void dimention_extractor(char input[], int *out_l, int *out_w, int *out_h) {
  char* token = strtok(input, "x");

  int values[3] = {0};

  for ( int i = 0; i < 3; i++ ) {
    values[i] = atoi(token);
    token = strtok(NULL, "x");
  }

  *out_l = values[0];
  *out_w  = values[1];
  *out_h = values[2];

  return;
}

int comp(const void* a, const void* b) {
  	
  	// If a is smaller, positive value will be returned
    return (*(int*)a - *(int*)b);
}

int calcule_ribbon_needed(int l, int w, int h) {
  int array[3] = { l, w, h };
  int length = sizeof(array) / sizeof(array[0]);

  qsort(array, length, sizeof(int), comp);


  return ( array[0]*2 + array[1]*2 ) + ( array[0]*array[1]*array[2] );
}

int main() {
  FILE *file = fopen("data", "r");

  int length;
  int width;
  int height;

  char input[20];
  // int total_wrapping_paper = 0;
  int total_ribbon = 0;

  if ( file != NULL ) {
    while( fgets(input, sizeof(input), file)) {
      dimention_extractor(input, &length, &width, &height);

      // Wrapping paper
      // int surface_area = calcule_surface_area(length, width, height);
      // int additionnal_value = smaller_value(length, width, height);
      // total_wrapping_paper += surface_area + additionnal_value;

      // Ribbon
      total_ribbon += calcule_ribbon_needed(length, width, height);
    }

    fclose(file);
  }

  // printf("%d\n", total_wrapping_paper);
  printf("%d\n", total_ribbon);

  return 0;
}
