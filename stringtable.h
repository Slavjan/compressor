#ifndef STRINGTABLE_H
#define STRINGTABLE_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int InitializeStringTable(int *iaPrefixCode,
                          unsigned char *caCharacter);

int SearchInStringTable(int *iPrefixCode, unsigned char *cCharacter, int iNumberOfCodes,
                        int iSearchingPrefixCode, unsigned char cSearchingCharacter);

#endif // STRINGTABLE_H
