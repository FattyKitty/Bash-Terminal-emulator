#define AmOfDelimeters 2
#define DEFAULTBUFFERSIZE 16
char *ReadLine();
char **ParsingLine(char *line);
int ExecCom(char **Tokens);
int LaunchProcess(char **Tokens);