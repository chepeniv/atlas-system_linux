#ifndef _SIGS_
#define _SIGS_

#include <sys/types.h>
#include <signal.h>

/**
 * struct _desc_index - stores a signal int code along with a brief string
 * description
 * @code: the number code of a signal
 * @desc: a string briefly describing the signal
 */

typedef struct _desc_index
{
	int code;
	char *desc;
} desc_index;

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
