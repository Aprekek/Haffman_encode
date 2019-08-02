// переменные типа char в структурах могут не корректно вести себя
// если пытаться считать символы из второй части ascii.
// unsigned char???
#include <stdio.h>
#include <stdlib.h>
#include "include/encode.h"
#include "include/file.h"
#include "include/types.h"
#include "include/vector.h"
#include "include/vector_s_count.h"

size_t capacity = 1000;
size_t symbols = 256;

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

    vector *nm_arr = vector_init();
    vector_s_count **cnt_nm_arr = vector_s_count_init();
    vector_s_count **symbols_code = vector_s_count_init();
    h_tree *tree = h_tree_init();
    unsigned int size = 0;

    file_read(nm_arr, cnt_nm_arr, fin);

    for (unsigned int i = 0; i < symbols; i++)
    {
        symbols_code[i] = cnt_nm_arr[i];
    }

    Sort(cnt_nm_arr);

    size = h_tree_sift(tree, cnt_nm_arr);
    dequeue_code(tree, symbols_code, size);
    uint8_t *code_vector = (uint8_t *)malloc(sizeof(uint8_t) * nm_arr->size);

    uint8_t past_byte_lenght = 0;
    uint32_t total_bytes = encode_process(code_vector, nm_arr, symbols_code, &past_byte_lenght);

    for (unsigned int i = 0; i < symbols; i++)
    {
        if (cnt_nm_arr[i]->weight != 0)
        {
            int x = cnt_nm_arr[i]->symbol;
            printf("[%d] \'%c\'"
                   "%0x %d %u\n",
                   x, cnt_nm_arr[i]->symbol, cnt_nm_arr[i]->code,
                   cnt_nm_arr[i]->weight, cnt_nm_arr[i]->lenght);
        }
    }

    fwrite_s_codes(symbols_code, code_vector, size, past_byte_lenght, total_bytes, fout);

    fclose(fout);
    if ((fout = fopen("symbols_binary.txt", "rb")) == NULL)
    {
        fclose(fin);
        exit(EXIT_FAILURE);
    }
    uint8_t ssize;
    uint16_t cde;
    uint8_t smbol;
    uint8_t lenght;
    fread(&ssize, sizeof(uint8_t), 1, fout);
    fread(&smbol, sizeof(uint8_t), 1, fout);
    fread(&lenght, sizeof(uint8_t), 1, fout);
    fread(&cde, sizeof(uint16_t), 1, fout);
    printf("\n%d\n%c (%d) - %0x\n", ssize, smbol, lenght, cde);

    fread(&smbol, sizeof(uint8_t), 1, fout);
    fread(&lenght, sizeof(uint8_t), 1, fout);
    fread(&cde, sizeof(uint16_t), 1, fout);
    printf("\n%d\n%c (%d) - %0x\n", ssize, smbol, lenght, cde);

    fread(&smbol, sizeof(uint8_t), 1, fout);
    fread(&lenght, sizeof(uint8_t), 1, fout);
    fread(&cde, sizeof(uint16_t), 1, fout);
    printf("\n%d\n%c (%d) - %0x\n", ssize, smbol, lenght, cde);

    free(code_vector);
    free(tree);
    free(symbols_code);
    free(cnt_nm_arr);
    free(nm_arr->array);
    free(nm_arr);
    fclose(fin);
    fclose(fout);
    return 0;
}