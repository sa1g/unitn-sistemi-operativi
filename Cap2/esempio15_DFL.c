#include <signal.h> // sigDFL . c

int main()
{
    signal(SIGTSTP, SIG_DFL);
    while (1);
}

/*
SIG_DFL:
It does exactly what one would expect: informs the kernel
that there is no user signal handler for the given signal,
and that the kernel should take default action for it
(the action itself may be to ignore the signal,
to terminate the program (with or without core dump),
etc. depending on the signal).
*/