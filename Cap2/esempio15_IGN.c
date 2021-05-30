#include <signal.h> // sigIGN . c

int main()
{
    signal(SIGTSTP, SIG_IGN);
    while (1);
}
//SIG_IGN 	signal is ignored 