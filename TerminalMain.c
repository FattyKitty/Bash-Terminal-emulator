#include "TerminalHeader.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
    char *InputLine=NULL;

    InputLine=ReadLine();
   
    printf("%s", InputLine);




    free(InputLine);

    return 0;
}