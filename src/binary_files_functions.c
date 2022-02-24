#include "state_sort.h"

// Function of reading a record of a given type from a file by its serial number.
struct my_struct read_record_from_file(FILE *pfile, int index) {
    // Calculation of the offset at which desired entry should be located from the beginning of the file.
    int offset = index * sizeof(struct my_struct);
    // Move the position pointer to the calculated offset from the beginning of the file.
    fseek(pfile, offset, SEEK_SET);

    // Reading a record of the specified type from a file.
    struct my_struct record;
    fread(&record, sizeof(struct my_struct), 1, pfile);

    // For safety reasons, we return the file position pointer to the beginning of the file.
    rewind(pfile);

    // Return read record
    return record;
}

// Function of writing a record of the specified type to the file at the specified serial number.
void write_record_in_file(FILE *pfile, const struct my_struct *record_to_write, int index) {
// Calculation of the offset at which the required record should be located from the beginning of the file.
    int offset = index * sizeof(struct my_struct);
    // Move the position pointer to the calculated offset from the beginning of the file.
    fseek(pfile, offset, SEEK_SET);

    // Write a record of the specified type to a file.
    fwrite(record_to_write, sizeof(struct my_struct), 1, pfile);

    // Just in case, force the I/O subsystem to write the contents of its buffer to a file right now.
    fflush(pfile);

    // For safety reasons, return the file position pointer to the beginning of the file.
    rewind(pfile);
}

// Function of mutual transfer of two records in the file by their indexes.
void swap_records_in_file(FILE *pfile, int record_index1, int record_index2) {
    // Read both records from file to variables
    struct my_struct record1 = read_record_from_file(pfile, record_index1);
    struct my_struct record2 = read_record_from_file(pfile, record_index2);

    // Rewrite records in file
    write_record_in_file(pfile, &record1, record_index2);
    write_record_in_file(pfile, &record2, record_index1);
}

void replace_the_records(FILE *pfile, int record_index1, int record_index2) {
    // Read record from file to variables
    struct my_struct record2 = read_record_from_file(pfile, record_index2);
    // Rewrite record in file
    write_record_in_file(pfile, &record2, record_index1);
}


// Function to get file size in bytes.
int get_file_size_in_bytes(FILE *pfile) {
    int size = 0;
    // Move the position pointer to the end of the file.
    fseek(pfile, 0, SEEK_END);
    // Read the number of bytes from the beginning of the file to the current position pointer.
    size = ftell(pfile);
    // For safety reasons, move the position pointer back to the beginning of the file.
    rewind(pfile);
    return size;
}

// Function to get count of records in file
int get_records_count_in_file(FILE *pfile) {
    return get_file_size_in_bytes(pfile) / sizeof(struct my_struct);
}

void error() {
    printf("n/a");
}

int is_date_wrong(int year, int month, int day) {
    int status = 0;
    if (year % 4 != 0 && month == 2 && day > 28) status = 1;
    if ((month == 1 && day > 31) || (month == 2 && day > 29) ||
        (month == 3 && day > 31) || (month == 4 && day > 30) ||
        (month == 5 && day > 31) || (month == 6 && day > 30) ||
        (month == 7 && day > 31) || (month == 8 && day > 31) ||
        (month == 9 && day > 30) || (month == 10 && day > 31) ||
        (month == 11 && day > 30) || (month == 12 && day > 31) ||
         month > 12) status = 1;
    return status;
}

void sort(FILE *file1, int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = (size - 1); j > i; j--) {
            struct my_struct el1 = read_record_from_file(file1, j);
            struct my_struct el2 = read_record_from_file(file1, j - 1);
            if ((el1.year * 8760 + el1.month * 730 + el1.day * 24 + el1.hours
                + el1.minutes / 60 + el1.seconds / 3600) <
                (el2.year * 8760 + el2.month * 730 + el2.day * 24 + el2.hours
                + el2.minutes / 60 + el2.seconds / 3600)) {
                    swap_records_in_file(file1, j, j - 1);
            }
        }
    }
}


void print_file(FILE *file1, int n) {
    for (int i = 0; i < n; i++) {
        struct my_struct el = read_record_from_file(file1, i);
        if (i < n -1) {
            printf("%d %d %d %d %d %d %d %d\n",
            el.year, el.month, el.day, el.hours, el.minutes, el.seconds, el.status, el.code);
        } else {
            printf("%d %d %d %d %d %d %d %d",
            el.year, el.month, el.day, el.hours, el.minutes, el.seconds, el.status, el.code);
        }
    }
    // printf("  count = %d", cnt);
}
