#include "state_sort.h"


int main() {
    FILE *file1 = NULL;
    char path[4100];
    int n = -1, records_count = 0;
    scanf("%4099s", path);
    if ((file1 = fopen(path, "r+b")) != NULL) {
        scanf("%d", &n);
        records_count = get_records_count_in_file(file1);
        if (n == 0) {
            print_file(file1, records_count);
        } else if (n == 1) {
            sort(file1, records_count);
            print_file(file1, records_count);
        } else if (n == 2) {
            struct my_struct el = create_struct();
            if (el.year != -1) {
                write_record_in_file(file1, &el, records_count);
                sort(file1, records_count + 1);
                print_file(file1, records_count + 1);
            }
        } else {
            error();
        }
    } else {
            error();
    }
    fclose(file1);
    return 0;
}


struct my_struct create_struct() {
    struct my_struct el, correct_el;
    correct_el.year = -1;
    if ((scanf("%d %d %d %d %d %d %d %d",
    &el.year, &el.month, &el.day, &el.hours, &el.minutes,
    &el.seconds, &el.status, &el.code)) != 8 ||
    el.year < 0 || el.month < 0 || el.day < 0 ||
    el.hours < 0 || el.minutes < 0 || el.seconds < 0 ||
    el.hours > 24 || el.minutes > 60 || el.seconds > 60 ||
    el.code < -1 || el.status < 0 ||  el.status > 1) {
        error();
    } else {
        correct_el = el;
    }
    if (is_date_wrong(el.year, el.month, el.day)) {
        error();
        correct_el.year = -1;
    }
    return correct_el;
}
