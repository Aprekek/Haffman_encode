#include <stdio.h>
#include <stdlib.h>
#include "include/file.h"
#include "include/types.h"
#include "include/vector.h"
#include "include/vector_s_count.h"
#include "include/h_node_h_tree.h"

extern size_t symbols;

void file_read(vector *nm_arr, vector_s_count **cnt_nm_arr, FILE *fin)
{
    __size_smbls ch;
    int int_ch;
    while (!feof(fin))
    {
        fscanf(fin, "%c", &ch);
        int_ch = ch;
        vector_push_back(nm_arr, ch);
        cnt_nm_arr[int_ch]->symbol = ch;
        cnt_nm_arr[int_ch]->weight++;
    }
}

void fwrite_s_codes(vector_s_count **codes_array, uint8_t *encode_vector,
                    __size_smbls count, uint64_t decode_message_leght,
                    uint64_t total_bist, FILE *fout)
{
    fwrite(&count, sizeof(__size_smbls), 1, fout);
    printf("total symbols %d\n", count);
    for (size_t i = 0; i < symbols; i++)
    {
        if (codes_array[i]->weight > 0)
        {
            fwrite(&codes_array[i]->symbol, sizeof(__size_smbls), 1, fout);
            fwrite(&codes_array[i]->lenght, sizeof(uint8_t), 1, fout);
            fwrite(&codes_array[i]->code, sizeof(code_type), 1, fout);
        }
    }

    printf("decode_message_leght %ld\n", decode_message_leght);
    printf("size of encode_message (bit) %ld\n", total_bist);
    fwrite(&decode_message_leght, sizeof(uint64_t), 1, fout);
    fwrite(&total_bist, sizeof(uint64_t), 1, fout);

    printf("fwrite message bytes %ld\n", fwrite(encode_vector, sizeof(uint8_t), total_bist / 8 + 1, fout));
}
