#include "stud_struct.h"


int calc_count_row(char *file_name) {
  FILE *f = fopen(file_name, "r");
  int count = 1;
  char ch;
  while((ch = fgetc(f)) != EOF)
    if (ch == '\n')
      count++;
  fclose(f);
  return count;
}

void start_calc(char *file_name) {
  char ch;
  int follow_digit = 0, group = 0, i_col = 0, i_row = 0, max_m, min_m;
  int count_row = calc_count_row(file_name);
  FILE *f = fopen(file_name, "r");
  row_buffer* (arr_row_buffer[count_row]);
  do {
    if(i_row != 0) {
      arr_row_buffer[i_row - 1] = (row_buffer*)malloc(sizeof(row_buffer));
      arr_row_buffer[i_row - 1]->disperse.row_group = *(int*)malloc(sizeof(int));
      arr_row_buffer[i_row - 1]->disperse.row_difference = *(int*)malloc(sizeof(int));
      arr_row_buffer[i_row - 1]->row_arr = (int*)malloc(sizeof(int));
    }
    do {
      ch = fgetc(f);
      if(i_row != 0){
        if((ch == ',' || ch == '\n' || ch == EOF)) {
          i_col++;
          if(i_col > 5) {
            arr_row_buffer[i_row - 1]->row_arr = (int*)realloc(arr_row_buffer[i_row - 1]->row_arr, sizeof(int) * (i_col - 5) * 2);
            arr_row_buffer[i_row - 1]->row_arr[i_col - 6] = follow_digit;
            follow_digit = 0;
          }
        } else if((int)(ch - '0') >= 0 && (int)(ch - '0') <= 9 && i_col > 4) {
          follow_digit = follow_digit * 10 + (int)(ch - '0');
        } else if((int)(ch - '0') >= 0 && (int)(ch - '0') <= 9 && i_col == 4) {
          group = group * 10 + (int)(ch - '0');
        }
      }
    } while (ch != '\n' && ch != EOF);
    if(i_row != 0) {
      arr_row_buffer[i_row - 1]->disperse.row_group = group;
      group = 0, max_m = 0, min_m = 999;
      for(int j = 0; j < i_col - 5; j++) {
        // printf("row_arr:  %d, i_row - 1:  %d, j:  %d", arr_row_buffer[i_row - 1]->row_arr[j], (i_row - 1), j);
        if(arr_row_buffer[i_row - 1]->row_arr[j] > max_m)
          max_m = arr_row_buffer[i_row - 1]->row_arr[j];
        if(arr_row_buffer[i_row - 1]->row_arr[j] < min_m)
          min_m = arr_row_buffer[i_row - 1]->row_arr[j];
      }
      arr_row_buffer[i_row - 1]->disperse.row_difference = max_m - min_m;
      printf("number group:  %d, maximum disperse:  %d\n", arr_row_buffer[i_row - 1]->disperse.row_group, arr_row_buffer[i_row - 1]->disperse.row_difference);
    }
    i_col = 0;
    i_row++;
  } while(ch != EOF);
  fclose(f);
}