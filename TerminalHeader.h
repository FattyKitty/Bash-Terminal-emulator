#define AmOfDelimeters 2
#define DEFAULTBUFFERSIZE 16
#define _GNU_SOURCE
char *ReadLine();
char **ParsingLine(char *line);
int ExecCom(char **Tokens);
int LaunchProcess(char **Tokens);