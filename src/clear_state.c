#include "state_sort.h"

#include <unistd.h>

int main() {
    FILE *file1 = NULL;
    char path[4100];
    int  year1, month1, day1, year2, month2, day2, pos_1, pos_2;
    scanf("%4099s", path);
    if ((file1 = fopen(path, "r+b")) != NULL) {
        int records_count;
        records_count = get_records_count_in_file(file1);
        sort(file1, records_count);
        if (input_date(&year1, &month1, &day1)) {
            error();
        } else {
            if (input_date(&year2, &month2, &day2)) {
                 error();
            } else {
                //  printf(" \n from main %d . %d . %d", year, month, day);
                if (compare_dates(year1, month1, day1, year2, month2, day2)) {
                    error();
                } else {
                    find_the_doors(file1, records_count, year1, month1, day1,
                                    year2, month2, day2, &pos_1, &pos_2);
                    clear_data(file1, records_count, pos_1, pos_2);
                    fclose(file1);
                    file1 = fopen(path, "r+b");
                    records_count = get_records_count_in_file(file1);
                    print_file(file1, records_count);
                    fclose(file1);
                }
            }
        }
    } else {
        error();
    }
    fclose(file1);
    return 0;
}

int input_date(int* year, int* month, int* day) {
    int status = 0;
    char input[11];
    if ((scanf("%10s", input) != 1) || input[2] != '.' || input[5] != '.')
        status = 1;
    *day = ((int)input[0] - 48) * 10 + ((int)input[1] - 48);
    *month = ((int)input[3] - 48) * 10 + ((int)input[4] - 48);
    *year = (((int)input[6] - 48) * 1000 + ((int)input[7] - 48) * 100 +
             ((int)input[8] - 48) * 10 + ((int)input[9] - 48));
    //  printf(" \n from input %d . %d . %d", *year, *month, *day);
    if (is_date_wrong(*year, *month, *day)) {
        status = 1;
    }
    //  for (int i = 0; i <12; i ++) printf(" \ni = %d input = %c \n", i , input[i]);
    return status;
}

void find_the_doors(FILE *file1, int n, int year1, int month1, int day1,
                    int year2, int month2, int day2, int* pos_1, int* pos_2) {
    *pos_1 = 0;
    *pos_2 = n - 1;
    for (int i = 0; i < n && *pos_1 == 0; i++) {
        struct my_struct el = read_record_from_file(file1, i);
        if (el.year * 365 + el.month * 30.42 + el.day >=
            year1 * 365 + month1 * 30.42 + day1) {
            *pos_1 = i;
        }
    }
    for (int i = n - 1; 0 <= i && *pos_2 == n - 1; i--) {
        struct my_struct el = read_record_from_file(file1, i);
        if (el.year * 365 + el.month * 30.42 + el.day <=
            year2 * 365 + month2 * 30.42 + day2) {
            *pos_2 = i;
        }
    }
}

void clear_data(FILE *file1, int n, int pos_1, int pos_2) {
    for (int i = 0; i < (n - pos_2 - 1); i++) {
        replace_the_records(file1, i + pos_1, i + pos_2 + 1);
    }
    if (ftruncate(fileno(file1), (n * sizeof(struct my_struct) -
                                  (pos_2 - pos_1 + 1) * sizeof(struct my_struct))) != 0) error();
}

int compare_dates(int year1, int month1, int day1, int year2, int month2, int day2) {
    int m = 0;
    double a1, a2;
    a1 = year1 * 365 + month1 * 30.42 + day1;
    a2 = year2 * 365 + month2 * 30.42 + day2;
    if (a1 > a2) m = 1;
    // printf("\na1 = %lf a2 = %lf\n", a1, a2);
    return m;
}
