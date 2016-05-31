#include "decompressfile.h"


int DecompressFile(FILE *f_in, FILE *f_out)
{
// .::Доска строки::.
    int *iPrefixCode = new int[TABLE_SIZE];
    unsigned char *cCharacter = new unsigned char[TABLE_SIZE];

    int iNumberOfCodes = 0;
    int iCurrentPrefixCode = -1;
    int iCurrentCode;
    int iOldCode;
    unsigned char cCurrentCharacter;
    int iCounter=0, iKbCounter=0;

    iNumberOfCodes = InitializeStringTable(iPrefixCode, cCharacter);
    iCurrentCode = GetNextCodeFromFile(f_in);

    if(OutputStringForCode(iPrefixCode, cCharacter, f_out, iCurrentCode)<0)
    {
        delete [] iPrefixCode;
        delete [] cCharacter;
        return -1;
    }
    iOldCode=iCurrentCode;
    while((iCurrentCode=GetNextCodeFromFile(f_in))>=0)
    {
    // .::Kb-счетчик::.
        iCounter++;
        if(iCounter>=((1024*8)/BITS_IN_CODE))
        {
            iKbCounter++;
            iCounter-=((1024*8)/BITS_IN_CODE);
            printf("%10d Kb decompressed...\r\r\r\r\r\r\r\r\r\r\r\r\r\r\r\r\r\r\r\r\r\r\r\r\r\r\r\r",
                   iKbCounter);
        }

    if(iCurrentCode == TABLE_SIZE)
    {
        iNumberOfCodes = InitializeStringTable(iPrefixCode, cCharacter);
        iCurrentCode = GetNextCodeFromFile(f_in);
        // .::Kb-счетчик::.
        iCounter++;
        if(iCounter>=((1024*8)/BITS_IN_CODE))
        {
            iKbCounter++;
            iCounter-=((1024*8)/BITS_IN_CODE);
            printf("%10d Kb decompressed...\r\r\r\r\r\r\r\r\r\r\r\r\r\r\r\r\r\r\r\r\r\r\r\r\r\r\r\r",
                   iKbCounter);
        }

        if(iCurrentCode<0)
            break;
        if(OutputStringForCode(iPrefixCode, cCharacter, f_out, iCurrentCode)<0)
        {
            delete [] iPrefixCode;
            delete [] cCharacter;
            return -1;
        }
        iOldCode=iCurrentCode;
        }
        else
        {
            if(iCurrentCode<=iNumberOfCodes-1)
            {
                if(OutputStringForCode(iPrefixCode, cCharacter, f_out, iCurrentCode)<0)
                {
                    delete [] iPrefixCode;
                    delete [] cCharacter;
                    return -1;
                }
                iCurrentPrefixCode=iOldCode;
                cCurrentCharacter=GetFirstCharacterForCode(iPrefixCode, cCharacter, iCurrentCode);
                iPrefixCode[iNumberOfCodes]=iCurrentPrefixCode;
                cCharacter[iNumberOfCodes]=cCurrentCharacter;
                iNumberOfCodes++;
                iOldCode=iCurrentCode;
            }
            else
            {
                iCurrentPrefixCode=iOldCode;
                cCurrentCharacter=GetFirstCharacterForCode(iPrefixCode, cCharacter, iCurrentPrefixCode);
                iPrefixCode[iNumberOfCodes]=iCurrentPrefixCode;
                cCharacter[iNumberOfCodes]=cCurrentCharacter;
                iNumberOfCodes++;
                if(OutputStringForCode(iPrefixCode, cCharacter, f_out, iNumberOfCodes-1)<0)
                {
                    delete [] iPrefixCode;
                    delete [] cCharacter;
                    return -1;
                }
                iOldCode=iCurrentCode;
            }
        }
    }
    delete [] iPrefixCode;
    delete [] cCharacter;

    return 0;
}
