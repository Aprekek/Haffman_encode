#ifndef DECODE_H
#define DECODE_H
#include "types.h"

void decode(char *name_fin, char *name_fout);
void decode_process(tree *fds, uint8_t *encode_message, char *decode_message,
                    uint64_t sizeof_encode_message);

#endif
