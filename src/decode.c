#include <stdio.h>
#include <stdlib.h>
#include "include/file.h"
#include "include/types.h"
#include "include/vector.h"
#include "include/vector_s_count.h"
#include "include/h_node_h_tree.h"
#include "include/decode.h"
#include "include/node.h"

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
    uint8_t past_total_byte;
    __size_smbls count;
    fread(&count, sizeof(__size_smbls), 1, fin);

    s_node **c_symbols = node_itit(count);
    if (c_symbols == NULL)
    {
        printf("fc\n");
        exit(EXIT_FAILURE);
    }

    uint8_t *encode_message = fread_s_codes(c_symbols, count, &past_total_byte, fin);
    for (unsigned i = 0; i < count; i++)
        printf("%c [%d] - %0x\n", c_symbols[i]->symbol, c_symbols[i]->lenght, c_symbols[i]->code);

    fclose(fin);
    fclose(fout);
    free(c_symbols);
    return;
}