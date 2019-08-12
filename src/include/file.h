#ifndef FILE_H
#define FILE_H
#include "types.h"

void file_read(vector *symbols, vector_s_count **s_count, FILE *fin);
void fwrite_s_codes(vector_s_count **codes_array, uint8_t *encode_vector,
                    __size_smbls count, uint64_t decode_message_leght,
                    uint64_t total_bist, FILE *fout);
void fwrite_decode_message(char *decode_message, FILE *fout);
#endif
