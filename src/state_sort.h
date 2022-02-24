#ifndef SRC_STATE_SORT_H_
#define SRC_STATE_SORT_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

struct my_struct{
    int year;
    int month;
    int day;
    int hours;
    int minutes;
    int seconds;
    int status;
    int code;
};

struct my_struct read_record_from_file(FILE *pfile, int index);
void write_record_in_file(FILE *pfile, const struct my_struct *record_to_write, int index);
void swap_records_in_file(FILE *pfile, int record_index1, int record_index2);
int get_file_size_in_bytes(FILE *pfile);
int get_records_count_in_file(FILE *pfile);
void replace_the_records(FILE *pfile, int record_index1, int record_index2);

int input_date(int* year, int* month, int* day);
void find_the_door(FILE *file1, int n, int year, int month, int day);

void sort(FILE *file1, int size);
struct my_struct create_struct();
int is_date_wrong(int year, int month, int day);

void error();
void print_file(FILE *file1, int n);

int is_date_wrong(int year, int month, int day);
int input_date(int* year, int* month, int* day);
void find_the_doors(FILE *file1, int n, int year1, int month1, int day1,
                    int year2, int month2, int day2, int* pos_1, int* pos_2);
void clear_data(FILE *file1, int n, int pos_1, int pos_2);
int compare_dates(int year1, int month1, int day1, int year2, int month2, int day2);


#endif  // SRC_STATE_SORT_H_
