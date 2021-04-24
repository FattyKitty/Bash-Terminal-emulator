#include "TerminalHeader.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    char *InputLine=NULL;
    char **CommsAndArgs;
    int Executable=1;
    char *Path=malloc(sizeof(char)*MAXPATHLENGTH);
    

    do
    {
        getcwd(Path, MAXPATHLENGTH);
        printf(PURPLE"%s > "DEFAULT, Path);
        InputLine=ReadLine();

        CommsAndArgs=ParsingLine(InputLine);

        Executable=LaunchProcess(CommsAndArgs);
        free(InputLine);
        free(CommsAndArgs);
    } while(Executable);

    free(Path);
    return 0;
}