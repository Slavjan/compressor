#include "coder.h"

// .::Выведение кода в выходной файл::.
int OutputCode(FILE *f_out,int iCode)
{
    static unsigned char cBuffer;
    static int iNumberOfBitsInBuffer;
    int i=0;
    int i2_in_power_NOBI=1;
    if(iCode==-2)
    {
        cBuffer=(unsigned char)0;
        iNumberOfBitsInBuffer=0;
        return 0;
    }
    if(iCode==-1)
    {
        if(iNumberOfBitsInBuffer!=0)
            fprintf(f_out,"%c",cBuffer);
        return 0;
    }
    if(iCode>=0)
    {
        while(i<iNumberOfBitsInBuffer)
        {
            i2_in_power_NOBI*=2;
            i++;
        }
        i=0;
        while(i<BITS_IN_CODE)
        {
            cBuffer+=i2_in_power_NOBI*(iCode%2);
            iCode/=2;
            i2_in_power_NOBI*=2;
            iNumberOfBitsInBuffer++;
            i++;
            if (iNumberOfBitsInBuffer>=8)
            {
                fprintf(f_out,"%c",cBuffer);
                cBuffer=(unsigned char)0;
                iNumberOfBitsInBuffer=0;
                i2_in_power_NOBI=1;
            }
        }
        return 0;
   }
    return -1;
}

// .::получение первого символа из строки символа::.
unsigned char GetFirstCharacterForCode(int *iPrefixCode, unsigned char *cCharacter, int iCurrentCode)
{
    while(iPrefixCode[iCurrentCode]>=0)
    {
        iCurrentCode=iPrefixCode[iCurrentCode];
    }
    return (cCharacter[iCurrentCode]);
}

// .::Выведение строки для кода в выходной файл::.
int OutputStringForCode(int *iPrefixCode, unsigned char *cCharacter, FILE *f_out,int iCurrentCode)
{
    if(iCurrentCode>=0){
        int iCode = iCurrentCode;
        int iLengthOfString = 0, i;
    while(iPrefixCode[iCode]>=0){
        iCode=iPrefixCode[iCode];
        iLengthOfString++;
      }
    unsigned char *sOutputtingString = new unsigned char[iLengthOfString+1];
    iCode=iCurrentCode;
    i=iLengthOfString;
    while(i>=0){
        sOutputtingString[i]=cCharacter[iCode];
        iCode=iPrefixCode[iCode];
        i--;
      }
    i=0;
    while(i<=iLengthOfString){
        fprintf(f_out,"%c",sOutputtingString[i]);
        i++;
      }
        delete [] sOutputtingString;
        return 0 ;
    }
    else
        return -1;
}

// .::получение следующего кода из файла::.
int GetNextCodeFromFile(FILE *f_in)
{
    static unsigned char cBuffer;
    static int iNumberOfBitsInBuffer = 0;
    int i = 0;
    int i2_in_power_i = 1 ;
    int iCode = 0;
    while(i<BITS_IN_CODE)
    {
        if(iNumberOfBitsInBuffer==0)
        {
            if(fscanf(f_in, "%c", &cBuffer)!=1) return -1;
            iNumberOfBitsInBuffer=8;
        }
        iCode+=(cBuffer%2)*i2_in_power_i;
        cBuffer/=2;
        iNumberOfBitsInBuffer--;
        i++;
        i2_in_power_i*=2;
   }
   return iCode ;
}
