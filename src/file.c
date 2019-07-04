#include <stdio.h>
#include <stdlib.h>
#include "include/file.h"
#include "include/types.h"
#include "include/vector.h"
#include "include/vector_s_count.h"

void file_works(vector *nm_arr, vector_s_count *cnt_nm_arr, FILE *fin)
{
    unsigned char ch;
    int i = 0;
    while (!feof(fin))
    {
        fscanf(fin, "%c", &ch);
        vector_push_back(nm_arr, ch);
        cnt_nm_arr[ch].symbol = ch;
        cnt_nm_arr[ch].count++;
        i++;
    }
}