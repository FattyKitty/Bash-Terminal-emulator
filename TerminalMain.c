#include "TerminalHeader.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
    char *InputLine=NULL;
    char **CommsAndArgs;
    int Executable=1;
    do
    {
        InputLine=ReadLine();

        CommsAndArgs=ParsingLine(InputLine);

        Executable=LaunchProcess(CommsAndArgs);

        free(InputLine);
        free(CommsAndArgs);
    } while(Executable);

    return 0;
}