#ifndef COMPRESSFILE_H
#define COMPRESSFILE_H

#include "coder.h"
#include "stringtable.h"

/*
 * InitializeStringTable()
 * OutputCode()
 * SearchInStringTable()
 */
int CompressFile(FILE *f_in, FILE *f_out); // \1

#endif // COMPRESSFILE_H
