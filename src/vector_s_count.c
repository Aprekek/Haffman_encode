#include <stdio.h>
#include <stdlib.h>
#include "include/types.h"
#include "include/vector_s_count.h"

extern size_t symbols;

void Sort(vector_s_count **cnt_nm_arr)
{
    for (unsigned int i = 0; i < symbols - 1; i++)
        for (unsigned int j = 0; j < symbols - i - 1; j++)
            if (cnt_nm_arr[j]->weight > cnt_nm_arr[j + 1]->weight)
            {
                vector_s_count *temp = cnt_nm_arr[j + 1];
                cnt_nm_arr[j + 1] = cnt_nm_arr[j];
                cnt_nm_arr[j] = temp;
            }
}

vector_s_count **vector_s_count_init()
{
    vector_s_count **vctr = (vector_s_count **)malloc(sizeof(*vctr) * symbols);
    for (unsigned int i = 0; i < symbols; i++)
        vctr[i] = (vector_s_count *)malloc(sizeof(vctr));
    if (vctr != NULL)
    {
        for (unsigned int i = 0; i < symbols; i++)
        {
            vctr[i]->symbol = 0;
            vctr[i]->weight = 0;
            vctr[i]->code = 0;
            vctr[i]->lenght = 0;
        }
    }
    return vctr;
}
