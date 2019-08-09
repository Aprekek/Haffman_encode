#include <stdio.h>
#include <stdlib.h>
#include "include/file.h"
#include "include/types.h"
#include "include/vector.h"
#include "include/vector_s_count.h"
#include "include/h_node_h_tree.h"
#include "include/decode.h"
#include "include/s_node.h"

void decode(char *name_fin, char *name_fout)
{
    FILE *fin, *fout;
    if ((fin = fopen(name_fin, "rb")) == NULL)
    {
        printf("Не удалось открыть файл %d\n", *name_fin);
        exit(EXIT_FAILURE);
    }
    if ((fout = fopen(name_fout, "w")) == NULL)
    {
        printf("Не удалось открыть файл %d\n", *name_fout);
        exit(EXIT_FAILURE);
    }

    uint64_t sizeof_message;
    uint8_t past_total_byte;
    __size_smbls count;
    fread(&count, sizeof(__size_smbls), 1, fin);
    printf("total symbols %d\n", count);

    s_node *tree = NULL;
    s_node **c_symbols = s_node_itit(count);
    if (c_symbols == NULL)
    {
        exit(EXIT_FAILURE);
    }

    for (uint8_t i = 0; i < count; i++)
    {
        fread(&c_symbols[i]->symbol, sizeof(__size_smbls), 1, fin);
        fread(&c_symbols[i]->lenght, sizeof(uint8_t), 1, fin);
        fread(&c_symbols[i]->code, sizeof(code_type), 1, fin);
        printf("%c %d %d\n", c_symbols[i]->symbol, c_symbols[i]->lenght, c_symbols[i]->code);
    }
    fread(&sizeof_message, sizeof(uint64_t), 1, fin);
    printf("size of message %ld\n", sizeof_message);
    fread(&past_total_byte, sizeof(__size_smbls), 1, fin);
    printf("past total byte %d\n", past_total_byte);
    uint8_t encode_message[sizeof_message + 1];

    printf("%ld\n", fread(encode_message, sizeof(uint8_t), sizeof_message, fin));

    /*    vector *decode_message = vector_init(count);

    s_node_sort(c_symbols, count);
    s_tree_node_add(&tree, c_symbols, count);
    decode_process(tree, encode_message, decode_message, past_total_byte, sizeof_message); */
    fclose(fin);
    fclose(fout);
    free(c_symbols);
    return;
}
void decode_process(s_node *tree, uint8_t *encode_message, vector *decode_message,
                    uint8_t past_byte_lenght, uint64_t sizeof_message)
{

    uint8_t lenght;
    int symbol;
    uint64_t total_bits = 0;
    uint64_t byte = 0;
    code_type code = encode_message[byte];
    code_type tmp_code;
    uint8_t bit;
    while (total_bits < (8 * sizeof_message + past_byte_lenght))
    {
        tmp_code = 0;
        lenght = 0;
        symbol = -1;
        do
        {
            if ((total_bits % 8 == 0) && (total_bits != 0))
            {
                byte++;
                code = encode_message[byte];
            }

            bit = code & 0x80;
            bit >>= 7;
            tmp_code <<= 1;
            tmp_code |= bit;
            code <<= 1;
            total_bits++;
            lenght++;

        } while ((symbol = search_symbol(tree, tmp_code, lenght)) == -1);
        vector_push_back(decode_message, (__size_smbls)symbol);
    }
    printf("%s", decode_message->array);
}