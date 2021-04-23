#include "TerminalHeader.h"
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

int main()
{
    char *InputLine=NULL;
    char **CommsAndArgs;
    int Executable=1;

    struct sigaction signal;

    do
    {
        printf("Type here > ");
        InputLine=ReadLine();

        CommsAndArgs=ParsingLine(InputLine);

        Executable=LaunchProcess(CommsAndArgs);

        sigaction(SIGINT, &signal, NULL);

        free(InputLine);
        free(CommsAndArgs);
    } while(Executable);

    return 0;
}