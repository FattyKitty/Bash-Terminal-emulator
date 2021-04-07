#include "TerminalHeader.h"
#include <stdio.h>
#include <stdlib.h>

char *ReadLine()
{
    char *Line=NULL;
    size_t LineSize=0;
    int MemLeak=0;

    if(MemLeak=getline(&Line, &LineSize, stdin)==-1)
    {
        printf("While reading line error occured, exiting the program...\n");
        exit(-1);
    }

    return Line;
}

char ParseLine(char *line)
{
    char Delimeter[2]={" ", "\r", "\t"};
}