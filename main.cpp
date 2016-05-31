#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//#define STR_FILE_IN_NAME "input.txt"
//#define STR_FILE_OUT_NAME "output.txt"
#define BITS_IN_CODE 12
#define TABLE_SIZE 4095

#include "compressfile.h"
#include "decompressfile.h"



int main(int argc, char* argv[])
{
    bool bAll=false;

    char sFInName[256], sFOutName[256], *pNothingDo;
    FILE *f_in, *f_out;
    char cRead;
// .::Чтение из командной строки::.
    if(argc>1)//// \todo
    {
        if((argv[1][0]=='-')&&(argv[1][1]=='l')&&(argv[1][2]=='\0'))
        {
            bAll=true;
        }
        else if((argv[1][0]=='-')&&(argv[1][1]=='c')&&(argv[1][2]=='\0'))
        {
            cRead='c';
        }
        else if((argv[1][0]=='-')&&(argv[1][1]=='d')&&(argv[1][2]=='\0'))
        {
            cRead='d';
        }
        else
        {
            bAll=true;
        }
        if(argc>2)
            pNothingDo=strcpy(sFInName,argv[2]);
        else
            bAll=true;
        if(argc>3)
            pNothingDo=strcpy(sFOutName,argv[3]);
        else
            bAll=true;
     }
     else
     {
        bAll=true;
     }

// .::Входной сигнал клавиатуры::.
    if(bAll)
    {
        printf("Enter the first letter of the operation (c - compressing; d - decompressing):");
        scanf("%c",&cRead);
        printf("Enter name of Input File:\n");
        scanf("%s",sFInName);
        printf("Enter name of Output File:\n");
        scanf("%s",sFOutName);
    }

    f_in=fopen(sFInName,"rb");
    f_out=fopen(sFOutName,"wb");
    if (cRead!='c' && cRead!='d')
    {
        printf("Error: can't recognize this operation!..\n");
        if(bAll) scanf("%c", &cRead);
        return -1;
    }
    if (!f_in)
    {
        printf("Error: can't open file with name %s!..\n", sFInName);
        if(bAll) scanf("%c", &cRead);
        return -1;
    }
    if (!f_out)
    {
        printf("Error: can't open file with name %s!..\n", sFOutName);
        if(bAll) scanf("%c", &cRead);
        return -1;
    }
    if (cRead=='c')
    {
        if(CompressFile(f_in, f_out)>=0)
        {
            printf("Compressing finished successfully!\n");
        }
        else
        {
            printf("Compressing finished UNsuccessfully!\n");
        }
    }
    if (cRead=='d')
    {
        if(DecompressFile(f_in, f_out)>=0)
        {
            printf("Decompressing finished successfully!\n");
        }
        else
        {
            printf("Decompressing finished UNsuccessfully!\n");
        }
    }
    fclose(f_in);
    fclose(f_out);
    return 0;
}

