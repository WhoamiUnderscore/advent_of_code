#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct {
  int x;
  int y;
} Position;

typedef struct {
  int value;
  int brightness;
} Light;

Position get_pos(char* token) {
  Position pos = { 0, 0 };

  char* str;
  char* x = strtok_r(token, ",", &str);
  char* y = strtok_r(NULL, ",", &str);

  if ( x && y ) {
    pos.x = atoi(x);
    pos.y = atoi(y);
  }

  return pos;
}

void handle_light_instruction(Light* grid, int light_instruction, Position pos1, Position pos2) {
  int current_y = pos1.y;
  while ( current_y <= pos2.y ) {
    for ( int x = pos1.x; x <= pos2.x; x++ ) {
      int real_pos = ( current_y * 1000 ) + x;

      switch ( light_instruction ) {
        case -1: 
          grid[real_pos].value = !grid[real_pos].value;
          grid[real_pos].brightness += 2;
          break;

        case 0:
          grid[real_pos].value = 0;
          grid[real_pos].brightness = grid[real_pos].brightness == 0 ? 0 : grid[real_pos].brightness - 1;
          break;

        case 1:
          grid[real_pos].value = 1;
          grid[real_pos].brightness++;
          break;

        default:
          break;
      }
    }

    current_y++;
  }
}

int main() {
  int len = 1000000;
  Light grid[len];
  int total_brightness = 0;

  for ( int i = 0; i < len; i++ ) {
    Light init_light = { 0, 0 };
    grid[i] = init_light;
  }
                  
  FILE *file = fopen("data", "r");
  char input[40];

  if ( file != NULL) {
    while( fgets(input, sizeof(input), file) ) {
      int light_instruction = 0; // -1 = toggle, 0 = turn off, 1 = turn on
      char splitter[2] = " ";

      char* token = strtok(input, splitter);

      while ( token != NULL ) {
        // Skip unwanted words
        if ( strcmp(token, "turn\0") == 0 || strcmp(token, "through\0") == 0 || strcmp(token, "off\0") == 0 ) 
        {
          token = strtok(NULL, splitter);
          continue;
        }
        else if ( strcmp(token, "on\0") == 0 ) 
        {
          light_instruction = 1;
          token = strtok(NULL, splitter);
          continue;
        }
        else if ( strcmp(token, "toggle\0" ) == 0 ) 
        {
          light_instruction = -1;
          token = strtok(NULL, splitter);
          continue;
        }
        else 
        {
          Position pos1 = get_pos(token);
          token = strtok(NULL, " "); // Skip "through"
          token = strtok(NULL, " ");
          Position pos2 = get_pos(token);

          if (pos1.x > pos2.x) {
            int t = pos1.x;
            pos1.x = pos2.x;
            pos2.x = t;
          }
          if (pos1.y > pos2.y) { int t = pos1.y; pos1.y = pos2.y; pos2.y = t; }

          handle_light_instruction(grid, light_instruction, pos1, pos2);
          break;
        }
      }
    }

    fclose(file);
  }


  int count = 0;
  for ( int i = 0; i < len; i++ ) {
    count += grid[i].value;
    total_brightness += grid[i].brightness;
  }

  printf("Count = %d, Total Brightness = %d\n", count, total_brightness);

  return 0;
}
