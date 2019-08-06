#include <stdio.h>
#include <stdlib.h>
#include "include/file.h"
#include "include/types.h"
#include "include/vector.h"
#include "include/vector_s_count.h"
#include "include/h_node_h_tree.h"
#include "include/encode.h"

extern size_t symbols;

void encode(char *name_fin, char *name_fout)
{
    FILE *fin, *fout;
    if ((fin = fopen(name_fin, "r")) == NULL)
    {
	printf("Не удалось открыть файл %d\n", *name_fin);
        exit(EXIT_FAILURE);
    }
    if ((fout = fopen(name_fout, "wb")) == NULL)
    {
	printf("Не удалось открыть файл %d\n", *name_fout);
        exit(EXIT_FAILURE);
    }

    vector *symbols_arr = vector_init();
    if (symbols_arr == NULL)
    {
        exit(EXIT_FAILURE);
    }
    vector_s_count **cnt_symbols_arr = vector_s_count_init();
    if (cnt_symbols_arr == NULL)
    {
        exit(EXIT_FAILURE);
    }
    vector_s_count **symbols_code = vector_s_count_init();
    if (symbols_code == NULL)
    {
        exit(EXIT_FAILURE);
    }
    h_tree *tree = h_tree_init();
    if (tree == NULL)
    {
        exit(EXIT_FAILURE);
    }
    unsigned int size = 0;

    file_read(symbols_arr, cnt_symbols_arr, fin);

    for (unsigned int i = 0; i < symbols; i++)
    {
        symbols_code[i] = cnt_symbols_arr[i];
    }

    Sort(cnt_symbols_arr);

    size = h_tree_sift(tree, cnt_symbols_arr);
    extraction_code(tree, symbols_code, size);

    uint8_t *code_vector = (uint8_t *)malloc(sizeof(uint8_t) * symbols_arr->size);
    if (code_vector == NULL)
    {
        exit(EXIT_FAILURE);
    }
    uint8_t past_byte_lenght = 0;
    uint64_t total_bytes = encode_process(code_vector, symbols_arr, symbols_code, &past_byte_lenght);

    fwrite_s_codes(symbols_code, code_vector, size, past_byte_lenght, total_bytes, fout);

    free(code_vector);
    free(tree);
    free(symbols_code);
    free(cnt_symbols_arr);
    free(symbols_arr->array);
    free(symbols_arr);
    fclose(fin);
    fclose(fout);
    return;
}

uint64_t encode_process(uint8_t *code_vector, vector *vctr,
                        vector_s_count **s_codes, uint8_t *past_byte_lenght)
{
    code_type code = 0x0;
    code_type tmp_code = 0x0;
    char lenght = 0;
    char byte_lenght = 0;
    uint64_t total_bytes = 0;
    unsigned int ch_int;
    char old_lenght;

    for (unsigned int i = 0; i < vctr->size; i++)
    {
        if (byte_lenght == 8)
        {
            byte_lenght = 0;
            total_bytes++;
        }

        ch_int = vctr->array[i];
        tmp_code = s_codes[ch_int]->code;
        lenght = s_codes[ch_int]->lenght;

        if (byte_lenght + lenght <= 8)
        {
            code_vector[total_bytes] |= tmp_code;
            byte_lenght += lenght;
            code_vector[total_bytes] <<= (8 - byte_lenght);
        }
        else
        {
            while (lenght > 0)
            {
                if (byte_lenght == 8)
                {
                    byte_lenght = 0;
                    total_bytes++;
                }

                code = tmp_code;
                old_lenght = lenght;
                lenght = lenght - (8 - byte_lenght);

                if (lenght >= 0)
                {
                    tmp_code >>= lenght;
                    byte_lenght += old_lenght - lenght;
                }

                code_vector[total_bytes] |= tmp_code;

                if (lenght < 0)
                {
                    code_vector[total_bytes] <<= (abs(lenght));
                    byte_lenght = old_lenght;
                }

                if (lenght > 0)
                {
                    tmp_code = code << (sizeof(code_type) * 8 - lenght);
                    tmp_code >>= sizeof(code_type) * 8 - lenght;
                }
            }
        }
    }
    *past_byte_lenght = byte_lenght;
    return total_bytes;
}
