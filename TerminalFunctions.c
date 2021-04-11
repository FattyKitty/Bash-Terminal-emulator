#include "TerminalHeader.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

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

char **ParsingLine(char *line)
{
    char Delimeter[AmOfDelimeters]={' ', '\t'}; //args neeeded for parsing
    int SizeOfBuffer=DEFAULTBUFFERSIZE;
    char *Token; //singele token from line. Like ls, -a etc
    int i=0; //variable to specify position of token in tokens array
    char **Tokens=malloc(sizeof(char*)*SizeOfBuffer);  //array of tokens

    if (Tokens==NULL)
    {
        printf("Error occured, not enough memory\n");
        exit(-1);
    }

    Token=strtok(line, Delimeter);

    while(Token!=NULL)
    {
        Tokens[i]=Token;
        ++i;

        Token=strtok(NULL, Delimeter);

        if (i>SizeOfBuffer)
        {
            SizeOfBuffer*=2;
            Tokens=realloc(Tokens, sizeof(char*)*SizeOfBuffer);
        }
        
    }
    Tokens[i]=NULL;
    return Tokens;
}

int ExecCom(char **Tokens)
{
    pid_t Child;
}