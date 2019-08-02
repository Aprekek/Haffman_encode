#include <stdio.h>
#include <stdlib.h>
#include "include/file.h"
#include "include/types.h"
#include "include/vector.h"
#include "include/vector_s_count.h"

extern size_t symbols;

void file_read(vector *nm_arr, vector_s_count **cnt_nm_arr, FILE *fin)
{
    __size_smbls ch;
    int int_ch;
    int i = 0;
    while (!feof(fin))
    {
        fscanf(fin, "%c", &ch);
        int_ch = ch;
        vector_push_back(nm_arr, ch);
        cnt_nm_arr[int_ch]->symbol = ch;
        cnt_nm_arr[int_ch]->weight++;
        i++;
    }
}

void fwrite_s_codes(vector_s_count **codes_array, uint8_t *encode_vector,
                    __size_smbls count, __size_smbls past_byte_leght,
                    uint32_t total_bytes, FILE *fout)
{
    fwrite(&count, sizeof(__size_smbls), 1, fout);
    for (size_t i = 0; i < symbols; i++)
    {
        if (codes_array[i]->weight > 0)
        {
            fwrite(&codes_array[i]->symbol, sizeof(__size_smbls), 1, fout);
            fwrite(&codes_array[i]->lenght, sizeof(uint8_t), 1, fout);
            fwrite(&codes_array[i]->code, sizeof(code_type), 1, fout);
        }
    }
    fwrite(&past_byte_leght, sizeof(__size_smbls), 1, fout);
    fwrite(encode_vector, sizeof(uint8_t), total_bytes, fout);
}