#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/encode.h"
#include "include/decode.h"

size_t capacity = 1000;
size_t symbols = 256;

int main()
{
    // char *fin = "files/symbols.txt";
    char *fin = "files/symbols_binary.txt";
    char *fout = "files/symbols_decode.txt";
    char choice = 2;

    switch (choice)
    {
    case 1:
        encode(fin, fout);
        break;

    case 2:
        decode(fin, fout);
        break;

    default:
        printf("syntax: <path_to_the_file> <encode/decode> <input_file> <output_file>\n");
        break;
    }

    exit(EXIT_SUCCESS);
}
/*int main(int argc, char *argv[])
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
        decode(argv[2], argv[3]);
        break;

    default:
        printf("syntax: <path_to_the_file> <encode/decode> <input_file> <output_file>\n");
        break;
    }

    exit(EXIT_SUCCESS);
}*/