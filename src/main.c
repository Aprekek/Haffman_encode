#include <stdio.h>
#include <stdlib.h>
#include "include/file.h"
#include "include/types.h"
#include "include/vector.h"
#include "include/vector_s_count.h"

size_t capacity = 1000;
size_t capacity_symbols = 128;

int main()
{
    FILE *fin, *fout;
    if ((fin = fopen("symbols.txt", "r")) == NULL)
    {
        exit(EXIT_FAILURE);
    }
    if ((fout = fopen("symbols_binary.txt", "wb")) == NULL)
    {
        fclose(fin);
        exit(EXIT_FAILURE);
    }
    vector *nm_arr;
    vector_s_count cnt_nm_arr[capacity_symbols];
    nm_arr = vector_init();
    file_works(nm_arr, cnt_nm_arr, fin);
    printf("%s", nm_arr->array);

    free(nm_arr->array);
    free(nm_arr);
    fclose(fin);
    fclose(fout);
    return 0;
}