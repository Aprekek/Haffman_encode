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

    uint64_t sizeof_encode_message;
    uint64_t sizeof_decode_message;
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
        printf("%c %0x %0x\n", c_symbols[i]->symbol, c_symbols[i]->lenght, c_symbols[i]->code);
    }
    fread(&sizeof_decode_message, sizeof(uint64_t), 1, fin);
    printf("decode message lenght %ld\n", sizeof_decode_message);
    fread(&sizeof_encode_message, sizeof(uint64_t), 1, fin);
    printf("encode message lenght %ld\n", sizeof_encode_message);
    uint8_t encode_message[sizeof_encode_message / 8 + 1];

    printf("fread message bytes %ld\n", fread(encode_message, sizeof(uint8_t), sizeof_encode_message / 8 + 1, fin));

    char decode_message[sizeof_decode_message];

    s_node_sort(c_symbols, count);
    s_tree_node_add(&tree, c_symbols, count);

    decode_process(tree, encode_message, decode_message, sizeof_encode_message);

    printf("\n----------\n%s\n----------\n", decode_message);
    //на моем компьютере происходит аварийная остановка при вызове низлежащей функции
    //fwrite_decode_message(decode_message, fout);
    fclose(fin);
    fclose(fout);
    free(c_symbols);
    return;
}
void decode_process(s_node *tree, uint8_t *encode_message, char *decode_message,
                    uint64_t sizeof_encode_message)
{
    uint64_t byte = 0;
    int symbol;
    uint8_t lenght;
    uint8_t code = encode_message[byte];
    code_type tmp_code;
    uint64_t total_bits = 0;
    uint8_t bit;
    uint64_t decode_message_possition = 0;
    while (total_bits < sizeof_encode_message)
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
        decode_message[decode_message_possition] = symbol;
        decode_message_possition++;
    }
    decode_message[decode_message_possition] = '\0';
}