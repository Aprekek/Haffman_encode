#ifndef ENCODE_H
#define ENCODE_H
#include "types.h"

void encode(char *name_fin, char *name_fout);
unsigned int encode_process(uint8_t *code_vector, vector *vctr,
                            vector_s_count **s_codes, uint8_t *past_byte_lenght);
#endif