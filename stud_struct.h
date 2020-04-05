#pragma pack()
#ifndef STUD_STRUCT_H
#define STUD_STRUCT_H
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<stdbool.h>


// variable prev_dump.c

// struct prev_dump.c
typedef struct student {
    int id;
    char surname[21];
    char initials[5];
    char sex[2];
    char num_group[5];
} student;

typedef struct marks {
    int id;
    int *mark_arr;
} marks;

// function prev_dump.c
void preparation_file(char *file_name);
void info();
struct marks* write_marks(struct student *s_in);
void write_input(char *file_name);


// variable calc.c

// struct calc.c
typedef struct {
    int row_difference;
    int row_group;
    bool single;
} unit;

typedef struct {
    int *row_arr;
    unit disperse;
} row_buffer;

// function calc.c
void start_calc(char *file_name);
int calc_count_row(char *file_name);

#endif