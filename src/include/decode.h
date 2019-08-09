#ifndef DECODE_H
#define DECODE_H
#include "types.h"

void decode(char *name_fin, char *name_fout);
void decode_process(s_node *tree, uint8_t *encode_message, vector *decode_message,
                    uint8_t past_byte_lenght, uint64_t sizeof_message);

#endif