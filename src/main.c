// переменные типа char в структурах могут не корректно вести себя
// если пытаться считать символы из второй части ascii.
// unsigned char???
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/encode.h"

size_t capacity = 1000;
size_t symbols = 256;

int main(int argc, char *argv[])
{

    char choice;
    if (argc < 2)
    {
        printf("syntax: <path_to_the_file> <encode/decode> <input_file> <output_file>\n");
        return 0;
    }
    if (strcmp(argv[1], "encode") == 0)
        choice = 1;
    else if (strcmp(argv[1], "decode") == 0)
        choice = 2;
    else
        choice = -1;

    switch (choice)
    {
    case 1:
        encode(argv[2], argv[3]);
        break;

    case 2:
        break;

    default:
        printf("syntax: <path_to_the_file> <encode/decode> <input_file> <output_file>\n");
        break;
    }

    return 0;
}