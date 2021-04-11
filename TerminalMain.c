#include "TerminalHeader.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    char *InputLine=NULL;
    char **CommsAndArgs;

    InputLine=ReadLine();
   
    printf("%s\n", InputLine);

    CommsAndArgs=ParsingLine(InputLine);

    free(InputLine);

    return 0;
}