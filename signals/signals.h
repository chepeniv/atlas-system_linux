#ifndef _SIGS_
#define _SIGS_

#include <sys/types.h>

/* REQUIRED FUNCTIONS */

int handle_signal(void);
void (*current_handler_signal(void))(int);
int handle_sigaction(void);
void (*current_handler_sigaction(void))(int);
int trace_signal_sender(void);
int pid_exist(pid_t pid);

/* SUPPLEMENTARY FUNCTIONS */

void print_gotcha(int signum);

#endif /* _SIGS_ */
