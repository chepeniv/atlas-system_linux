#ifndef _SIGS_
#define _SIGS_

#include <sys/types.h>
#include <signal.h>

/* REQUIRED FUNCTIONS */

int handle_signal(void);
void (*current_handler_signal(void))(int);
int handle_sigaction(void);
void (*current_handler_sigaction(void))(int);
int trace_signal_sender(void);
int pid_exist(pid_t pid);

/* SUPPLEMENTARY FUNCTIONS */

void print_gotcha(int signum);
void sig_handler_print_sender(
	int        sig_num,
	siginfo_t *sig_info,
	void      *sig_context);

#endif /* _SIGS_ */
