#ifndef STUD_STRUCT_H
#define STUD_STRUCT_H
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<stdbool.h>


typedef struct student {
    // int id[6];
    char surname[21];
    char initials[5];
    char sex[2];
    char num_group[5];
} student;

typedef struct marks {
    // int id[6];
    char mark[20];
} marks;

#endif