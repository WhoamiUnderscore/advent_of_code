#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct {
  int **cells;
  int width;
  int height;
  int offset_x;
  int offset_y;
  int robot_offset_x;
  int robot_offset_y;
} Grid;

typedef struct {
  int x;
  int y;
} Position;

typedef struct {
  int left; int right;
  int top;  int bottom;
} AddInformations;

void count_happy_houses(Grid grid) {
  int count = 0;

  for ( int y = 0; y < grid.height; y++ )
  {
    for ( int x = 0; x < grid.width; x++ )
    {
      if ( grid.cells[y][x] > 1 ) {
        count += 1;  
      }
    }
  }

  printf("%d \n", count);
}

void ensure(Grid *grid, Position pos, bool is_robot) {
  Position grid_position;

  if ( is_robot ) {
    grid_position.x = pos.x + grid->robot_offset_x;
    grid_position.y = pos.y + grid->robot_offset_y;
  } else {
    grid_position.x = pos.x + grid->offset_x;
    grid_position.y = pos.y + grid->offset_y;
  }

  AddInformations add_info;
  add_info.left = 0;
  add_info.right = 0;
  add_info.top = 0;
  add_info.bottom = 0;

  if ( grid_position.x <= 0) add_info.left = 1;
  if ( grid_position.y <= 0) add_info.top= 1;

  if ( grid_position.x >= grid->width - 1 ) add_info.right = 1;
  if ( grid_position.y >= grid->height - 1 ) add_info.bottom = 1;

  if ( add_info.left || add_info.right || add_info.top || add_info.bottom ) {
    grow_grid(grid, grid_position, add_info, is_robot);
  }
}

void grow_grid(Grid *grid, Position grid_position, AddInformations add_info, bool is_robot ) { 
  int new_width = grid->width + add_info.left + add_info.right;
  int new_height = grid->height + add_info.top+ add_info.bottom;
  
  int **new_cells = malloc(new_height * sizeof(int *));

  for ( int y = 0; y < new_height; y++ ){
    new_cells[y] = calloc(new_width, sizeof(int));
  }

  // Recopier les information de l'ancien array
  for ( int y = 0; y < grid->height; y++ ){
    int x = 0;

    if ( add_info.left != 0 ) {
      x = grid_position.x + add_info.left;
    }

    memcpy(
      &new_cells[y+add_info.top][x],
      grid->cells[y],
      grid->width * sizeof(int)
    );

    free(grid->cells[y]);
  }

  free(grid->cells);

  grid->cells = new_cells;
  grid->width= new_width;
  grid->height= new_height;

  grid->robot_offset_x += add_info.left;
  grid->robot_offset_y += add_info.top;
  grid->offset_x += add_info.left;
  grid->offset_y += add_info.top;
}


void increment_cell_value(Grid *grid, Position pos) {
  int grid_x = pos.x + grid->offset_x;
  int grid_y = pos.y + grid->offset_y;
  grid->cells[grid_y][grid_x] += 2;
}

int main() {
  Position santa_position;
  santa_position.x = 0;
  santa_position.y = 0;

  Position robot_position;
  robot_position.x = 0;
  robot_position.y = 0;

  Grid grid;
  grid.width = 11;
  grid.height = 11;
  grid.offset_x = 5;
  grid.offset_y = 5;
  grid.robot_offset_x = 5;
  grid.robot_offset_y = 5;

  grid.cells = malloc(grid.height * sizeof(int*));
  for ( int y = 0; y < grid.width; y++ ) {
    grid.cells[y] = calloc(grid.width, sizeof(int));
  }
  grid.cells[grid.offset_y][grid.offset_x] = 2;

  FILE *file = fopen("data", "r");

  if ( file == NULL ) {
    printf("File not opened.");
    return 1;
  }

  char cursor;
  bool is_robot = false;
  while ((cursor = fgetc(file)) != EOF ) {
      
      switch ( cursor ) {
        case 62:
          if ( is_robot ) {
            robot_position.x += 1;
          } else {
            santa_position.x += 1;
          }
          break;

        case 60:
          if ( is_robot ) {
            robot_position.x -= 1;
          } else {
            santa_position.x -= 1;
          }
          break;

        case 118:
          if ( is_robot ) {
            robot_position.y += 1;
          } else {
            santa_position.y += 1;
          }
          break;

        case 94:
          if ( is_robot ) {
            robot_position.y -= 1;
          } else {
            santa_position.y -= 1;
          }
          break;

        default:
          break;
      }

      if ( is_robot ) {
        ensure(&grid, robot_position, true);
        increment_cell_value(&grid, robot_position);
      } else {
        ensure(&grid, santa_position, false);
        increment_cell_value(&grid, santa_position);
      }
      
      is_robot = !is_robot;
  }

  count_happy_houses(grid);

  return 0;
}
