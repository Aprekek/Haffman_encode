#ifndef ENCODE_H
#define ENCODE_H
#include "types.h"

void encode(char *name_fin, char *name_fout);
uint64_t encode_process(uint8_t *code_vector, vector *vctr,
                        vector_s_count **s_codes);
#endif
