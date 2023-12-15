#include "shell.h"

/**
 * handle_signal - handle signal
 *
 * @signum: signal number
 * Return: 0
 */
void handle_signal(int signum)
{
	if (signum == SIGINT)
		write(1, "\nFizz=->> ", 10);
}

void handle_signal2(int signum)
{
	if (signum == SIGINT)
		write(1, "\n", 1);
}
