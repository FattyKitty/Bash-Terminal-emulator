#include "AdditionalCommands.h"
#include "TerminalHeader.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>


int TerminalExit()
{
    exit(1);
}

int TerminalCd(char **Tokens)
{
    if (chdir(Tokens[1])==-1)
    {
        printf("Couldn't move from current directory\n");
    }
    return 1;
}

int TerminalHelp()
{
    printf("This terminal was created for practice by Moscow Aviation Institute student\n");
    printf("List of supported integrated shell commands:\n");
    printf("1. help\n2. cd\n3. exit\n");

    return 1;
}