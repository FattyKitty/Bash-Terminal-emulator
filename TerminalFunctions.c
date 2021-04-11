#include "TerminalHeader.h"
#include "AdditionalCommands.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

char *ReadLine()
{
    char *Line=NULL;
    size_t LineSize=0;
    ssize_t MemLeak=0;

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
    int LineLength=strlen(line);

    if (line[LineLength-1]=='\n')
    {
        line[LineLength-1]='\0';
    }

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
            Tokens=realloc(Tokens, sizeof(char*)*SizeOfBuffer); //reallocating memory if we have not enough to store our command
        }
        
    }
    Tokens[i]=NULL;
    return Tokens;
}

int ExecCom(char **Tokens)
{
    pid_t Child;
    pid_t wpid;
    int Status;

    Child=fork();

    if (Child<0)
    {
        printf("Forking error\n");
        return 0;
    }
    else if (Child==0)
    {
        //child process
        if(execvp(Tokens[0], Tokens)==-1)
        {
            printf("Error occured while trying to execute process\n");
        }
    }
    else 
    {
        do 
        {

            wpid=waitpid(Child, &Status, WUNTRACED);

        } while(!WIFEXITED(Status) && !WIFSIGNALED(Status));
        
    }
    return 1;
}

int LaunchProcess(char **Tokens)
{
    if(strcmp(Tokens[0], "cd")==0)
    {
        TerminalCd(Tokens);
    }
    else if (strcmp(Tokens[0], "exit")==0)
    {
        TerminalExit();
    }
    else if (strcmp(Tokens[0], "help")==0)
    {
        TerminalHelp();
    }
    else
    {
        return ExecCom(Tokens);
    }
}