#include "compressfile.h"

int CompressFile(FILE *f_in, FILE *f_out)
{
// .::Доска строки::.
    int *iPrefixCode = new int[TABLE_SIZE];
    unsigned char *cCharacter = new unsigned char[TABLE_SIZE];

    int iCurrentPrefixCode = -1;
    unsigned char cCurrentCharacter;
    int iNumberOfCodes = 0;
    int iReturnCode;
    int iCounter=0, iKbCounter=0;
// .::Инициализация из таблицы строк::.
    iNumberOfCodes=InitializeStringTable(iPrefixCode, cCharacter);

// .::Зжатие::.
// .::Начало сжатии::.
    if(OutputCode(f_out,-2)<0)
    {
        delete [] iPrefixCode;
        delete [] cCharacter;
        return -1;
    }

    while(fscanf(f_in, "%c", &cCurrentCharacter)==1)
    {
    // .::Kb-счетчик::.
        iCounter++;
        if(iCounter>=1024){
            iKbCounter++;
            iCounter-=1024;
            printf("%10d Kb compressed...\r\r\r\r\r\r\r\r\r\r\r\r\r\r\r\r\r\r\r\r\r\r\r\r\r\r\r\r", iKbCounter);
      }

    if ((iReturnCode=SearchInStringTable(iPrefixCode, cCharacter, iNumberOfCodes,
                                        iCurrentPrefixCode, cCurrentCharacter))>=0)
    {
            iCurrentPrefixCode = iReturnCode;
    }
    else
    {
        iPrefixCode[iNumberOfCodes] = iCurrentPrefixCode;
        cCharacter[iNumberOfCodes] = cCurrentCharacter;
        iNumberOfCodes++;

        if(OutputCode(f_out,iCurrentPrefixCode)<0)
        {
            delete [] iPrefixCode;
            delete [] cCharacter;
            return -1;
         }
         iCurrentPrefixCode=(unsigned int)cCurrentCharacter;
    }
    if(iNumberOfCodes>=TABLE_SIZE)
    {
        if(OutputCode(f_out,iCurrentPrefixCode)<0)
        {
            delete [] iPrefixCode;
            delete [] cCharacter;
            return -1;
         }
         iCurrentPrefixCode = -1;
// .::Выедение кода для таблицы строк::.
        if(OutputCode(f_out,TABLE_SIZE)<0)
        { // код пополнения таблицы строк= (TABLE_SIZE-1)+
            delete [] iPrefixCode;
            delete [] cCharacter;
            return -1;
         }
// .::Переинициализация таблицы строк::.
        iNumberOfCodes = InitializeStringTable(iPrefixCode, cCharacter);
      }
   }
    if(OutputCode(f_out,iCurrentPrefixCode)<0)
    {
        delete [] iPrefixCode;
        delete [] cCharacter;
        return -1;
    }
// .::Конец стжатия::.
    if(OutputCode(f_out,-1)<0)
    {
        delete [] iPrefixCode;
        delete [] cCharacter;
        return -1;
    }

    delete [] iPrefixCode;
    delete [] cCharacter;
    return 0;
}
