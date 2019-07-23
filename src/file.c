#include <stdio.h>
#include <stdlib.h>
#include "include/file.h"
#include "include/types.h"
#include "include/vector.h"
#include "include/vector_s_count.h"

void file_works(vector *nm_arr, vector_s_count *cnt_nm_arr, FILE *fin)
{
    char ch;
    int int_ch;
    int i = 0;
    while (!feof(fin))
    {
        fscanf(fin, "%c", &ch);
        int_ch = ch;
        vector_push_back(nm_arr, ch);
        cnt_nm_arr[int_ch].symbol = ch;
        cnt_nm_arr[int_ch].weight++;
        i++;
    }
}