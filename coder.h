#ifndef CODER_H
#define CODER_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BITS_IN_CODE 12
#define TABLE_SIZE 4095

int OutputCode(FILE *f_out,int iCode);
int GetNextCodeFromFile(FILE *f_in);
int OutputStringForCode(int *iPrefixCode, unsigned char *cCharacter,
                        FILE *f_out,int iCurrentCode);
unsigned char GetFirstCharacterForCode(int *iPrefixCode,unsigned char *cCharacter,
                                       int iCurrentCode);

#endif // CODER_H
