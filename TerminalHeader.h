#include <signal.h>
#define AmOfDelimeters 2
#define DEFAULTBUFFERSIZE 16
#define MAXPATHLENGTH 256

#define PURPLE "\e[0;35m"
#define DEFAULT "\033[0m"
char *ReadLine();
char **ParsingLine(char *line);
int ExecCom(char **Tokens);
int LaunchProcess(char **Tokens);
int IsBackground(char **arguments);
void KillChild();
void KillParent();


struct sigaction Signal;