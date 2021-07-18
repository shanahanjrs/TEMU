#include <stdio.h>
#include <stdlib.h>

void print_arr(size_t s, int memprintwidth, int x[])
{
    /*
     * size_t (s) size of array to print
     * int[] (x) array to print
     */
    for (int i=0; i<s; i++) {
        if (i % memprintwidth == 0 && i != 0) {
            printf("\n");
        }
        printf("0x%x ", x[i]);
    }
    printf("\n");
}

void mem_load(size_t s, int offset, int dest[], int src[])
{
    /*
     * size_t (s) size of src arr
     * int (offset) byte offset to start writing to dest
     * int[] (dest) destination to write to
     * int[] (src) source of bytes to copy into src
     */
    for (int i=0; i<s; i++) {
        dest[offset+i] = src[i];
    }
}

char* file_read(char *filename) {
    FILE *f = fopen(filename, "rb");
    char *buffer = 0;
    long length;

    if (f) {
        fseek(f, 0, SEEK_END);
        length = ftell(f);
        fseek(f, 0, SEEK_SET);
        buffer = malloc(length);
        if (buffer) {
            fread(buffer, 1, length, f);
        }
        fclose(f);

        return buffer;
    }
}