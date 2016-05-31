#ifndef DECOMPRESSFILE_H
#define DECOMPRESSFILE_H

#include "coder.h"
#include "stringtable.h"

/*
 * InitializeStringTable()
 * GetNextCodeFromFile()
 * OutputStringForCode()
 *
 */
int DecompressFile(FILE *f_in, FILE *f_out);


#endif // DECOMPRESSFILE_H
