#include "state_sort.h"


int main() {
    FILE *file1 = NULL;
    char path[4100];
    int records_count = 0, year, month, day;
    scanf("%4099s", path);
    if ((file1 = fopen(path, "r+b")) != NULL) {
        records_count = get_records_count_in_file(file1);
        if (input_date(&year, &month, &day))  error();
        //  printf(" \n from main %d . %d . %d", year, month, day);
        find_the_door(file1, records_count, year, month, day);
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


void find_the_door(FILE *file1, int n, int year, int month, int day) {
    int b = 0;
    for (int i = 0; i < n && b == 0; i++) {
        struct my_struct el = read_record_from_file(file1, i);
        if (el.year == year && el.month == month && el.day == day) {
            printf("%d", el.code);
            b = 123;
        }
    }
    if (b == 0) error();
}
