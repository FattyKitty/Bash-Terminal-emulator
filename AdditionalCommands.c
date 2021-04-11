#include "AdditionalCommands.h"
#include <stdio.h>
#include <unistd.h>


int TerminalExit()
{
    return 0;
}

int TerminalCd(char **Tokens)
{
    if (chdir(Tokens[1])==-1)
    {
        printf("Cannot change directory\n");
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