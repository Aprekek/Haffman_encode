#include <stdio.h>
#include <stdlib.h>
#include "include/encode.h"
#include "include/file.h"
#include "include/types.h"
#include "include/vector.h"
#include "include/vector_s_count.h"

size_t capacity = 1000;
size_t symbols = 128;

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

    vector *nm_arr;
    vector_s_count *cnt_nm_arr = malloc(sizeof(vector_s_count) * symbols);

    nm_arr = vector_init();
    file_works(nm_arr, cnt_nm_arr, fin); //считываем слова из файла и делаем подсчет
    Sort(cnt_nm_arr);                    //сортируем символы по возрастанию по частоте встречаемости

    /*    for (unsigned int i = 0; i < symbols; i++)
    {
        if (cnt_nm_arr[i].weight != 0)
        {
            int x = cnt_nm_arr[i].symbol;
            printf("[%d] %c %d\n", x, cnt_nm_arr[i].symbol, cnt_nm_arr[i].weight);
        }
    }*/

    /*   h_tree *tree = h_tree_init();
    h_tree_node_init(tree, cnt_nm_arr);*/

    free(cnt_nm_arr);
    free(nm_arr->array);
    free(nm_arr);
    fclose(fin);
    fclose(fout);
    return 0;
}