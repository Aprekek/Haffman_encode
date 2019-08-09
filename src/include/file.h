#ifndef FILE_H
#define FILE_H
#include "types.h"

void file_read(vector *symbols, vector_s_count **s_count, FILE *fin);
void fwrite_s_codes(vector_s_count **codes_array, uint8_t *encode_vector,
                    __size_smbls count, uint8_t past_byte_leght,
                    uint64_t total_bytes, FILE *fout);
#endif
