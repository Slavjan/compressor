#include "stringtable.h"

// .::Инициализация из таблицы строк::.
int InitializeStringTable(int *iaPrefixCode,unsigned char *caCharacter)
{
    int i = 0;
    while(i<256){
        iaPrefixCode[i]=-1;
        caCharacter[i]=(unsigned char)i;
        i++;
    }
    return i;
}

// .::Является ли код строкой (==prefix+character) в строке таблицы,при сжатии::.
int SearchInStringTable(int *iPrefixCode, unsigned char *cCharacter, int iNumberOfCodes,
                        int iSearchingPrefixCode, unsigned char cSearchingCharacter)
{
    int i = 0;
    while(i<iNumberOfCodes){
        if ((iPrefixCode[i]==iSearchingPrefixCode) && (cCharacter[i]==cSearchingCharacter))
            return i;
        i++;
    }
    return -1;
}
