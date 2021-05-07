#define _GNU_SOURCE
#include "TerminalHeader.h"
#include "AdditionalCommands.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
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
        free(Line);
        Line=NULL;
        return Line;
    }

    return Line;
}

char **ParsingLine(char *line)
{
    char Delimeter[AmOfDelimeters]={' ', '\t'}; //args neeeded for parsing
    int SizeOfBuffer=DEFAULTBUFFERSIZE;
    char *Token; //single token from line. Like ls, -a etc
    int i=0; //variable to specify position of token in tokens array
    char **Tokens=malloc(sizeof(char*)*SizeOfBuffer);  //array of tokens
    int LineLength=strlen(line);

    if (strlen(line)==1)
    {
        Tokens[0]="\n";
        return Tokens;
    }

    if (line[LineLength-1]=='\n')
    {
        line[LineLength-1]='\0';
    }

    if (Tokens==NULL)
    {
        printf("Error occured, not enough memory\n");
        free(Tokens);
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
            char **Temp=realloc(Tokens, sizeof(char*)*SizeOfBuffer); //reallocating memory if we have not enough to store our command
            if (Temp==NULL)
            {
                free(Tokens);
                Tokens=NULL;
            }
            else
            {
                Tokens=Temp;
            }        
        }
    }
    if (Tokens!=NULL)
    {
        Tokens[i]=NULL;
    }
    return Tokens;
}

int ExecCom(char **Tokens, int BackGround)
{
    pid_t pid;
    pid_t wpid;
    int Status;

    pid=fork();

    if (pid<0)
    {
        printf("Forking error\n");
        return 0;
    }
    else if (pid==0)
    {
        //child process
        if(execvp(Tokens[0], Tokens)==-1)
        {
            printf("Error occured while trying to execute process\n");
            kill(pid, SIGINT);
            waitpid(pid, NULL, 0);
        }
    }
    else if(BackGround)
    {
        printf("Launching backgroung process\n");
        printf("His pid: %i\n", pid);
    }
    else 
    {
        Signal.sa_handler=&KillChild;
        sigaction(SIGINT, &Signal, NULL);

        wpid=waitpid(pid, NULL, 0);

        Signal.sa_handler=&KillParent;

        sigaction(SIGINT, &Signal, NULL);
    }
    return 1;
}

int LaunchProcess(char **Tokens, int BackGround)
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
    else if (strcmp(Tokens[0], "\n")==0)
    {
        return 1;
    }
    else
    {
        return ExecCom(Tokens, BackGround);
    }
}

void KillChild()
{
    printf("\nClosing process\n");
    Signal.sa_handler=&KillParent;
}

void KillParent()
{
    printf("\nClosing terminal\n");
    TerminalExit();
}

int IsBackground(char **arguments)
{
    int i=0;

    while(arguments[i]!=NULL)
    {
        printf("\n%s\n", arguments[i]);
        if (strcmp(arguments[i], "&")==0)
        {
            arguments[i]='\0';
            return 1;
        }
        ++i;
    }
    return 0;
}