#include "TerminalHeader.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    char *InputLine=NULL;
    char **Tokens;
    int BackGround=0;
    int Executable=1;
    char *Path=malloc(sizeof(char)*MAXPATHLENGTH);
    
    do
    {
        getcwd(Path, MAXPATHLENGTH);
        printf(PURPLE"%s > "DEFAULT, Path);
        InputLine=ReadLine();
        if (InputLine!=NULL)
        {
            Tokens=ParsingLine(InputLine);
            BackGround=IsBackground(Tokens);
            Executable=LaunchProcess(Tokens, BackGround);
            free(InputLine);
        }
            free(Tokens);
            Tokens=NULL;
        
    } while(Executable);

    free(Path);
    return 0;
}