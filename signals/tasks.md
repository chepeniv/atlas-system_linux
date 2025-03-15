# c - signals

## 0. handle signal (8 pts)

`0-handle_signal.c`

write a function that sets a handler for the `SIGINT` signal

- prototype: `int handle_signal(void);`
- return `0` on success or `-1` on error
- the program should print `Gotcha! [<signum>]`followed by a new line, every time
  `Ctrl-C` is pressed (`<signum>` is signal number that was caught)
- `sigaction`(2) is not allowed

## 1. current handler - signal (8 pts)

`1-current_handler_signal.c`

write a function that retrieves the current handler of the `SIGINT` signal

- prototype: `void (*current_handler_signal(void))(int);`
- return a pointer to the current handler of `SIGINT` or `NULL` upon failure
- `sigaction`(2) is not allowed
- the handler must remain unchanged after calling this function

## 2. gotta catch them all (8 pts)

`2-handle_sigaction.c`

write a function that sets a handler for the `SIGINT` signal

- prototype: `int handle_sigaction(void);`
- return `0` on success or `-1` on error
- the program should print `Gotcha! [<signum>]`followed by a new line, every
  time `Ctrl-C` is pressed (`<signum>` is signal number that was caught)
- `signal`(2) is not allowed

## 3. current handler - sigaction (8 pts)

`3-current_handler_sigaction.c`

write a function that retrieves the current handler for the `SIGINT` signal

- prototype: `void (*current_handler_sigaction(void))(int);`
- return a pointer to the current handler of `SIGINT` or `NULL` upon failure
- `sigaction`(2) must be used
- `signal`(2) is not allowed
- the handler must remain unchanged after calling this function

## 4. who said that ?! (7 pts)

`4-trace_signal_sender.c`

write a function that defines a handler for the `SIGQUIT` signal (`Ctrl-\` in a
shell)

- prototype: `int trace_signal_sender(void);`
- the handler should print `SIGQUIT sent by <pid>` each time `SIGQUIT` (no
  other signal should trigger this) is caught (`<pid>` is pid of the process
  that sent the signal)
- return `0` on success or `-1` on error

## 5. description (14 pts)

`5-signal_describe.c`

write a program that prints a description of the given signal

- usage: `./describe <signum>`
	- if an incorrect number of arguments is given, print `Usage: %s <signum>`
	  followed by a newline
		- where `%s` is given by `argv[0]`
		- exit with `EXIT_FAILURE`
- no more than one function in your file
- no more than twelve lines in your function
- assume all parameters given will be numbers

## 6. catch a single time (6 pts)

`6-suspend.c`

write a program that sets a handler for the `SIGINT` signal, and exits right
after the signal has been received and handled

- this program doesn't take an argument
- suspend indefinitely until a signal is received
- when a `SIGINT` is received, print `Caught %d\n` where is the signal number
- after the first `SIGINT` is received
	-  print `Signal Received\n` with exit `EXIT_SUCCESS`
- the `exit`, `sleep`, and `_exit` functions are not allowed
- no loops are allowed

## 7. sending a signal (8 pts)

`7-signal_send.c`

write a program that sends the `SIGINT` signal to a process given by its PID

- usage: `./signal_send <pid>`
	- if an incorrect number of arguments is given, print `Usage: %s <pid>\n`
		- where `%s` is given by `argv[0]`
		- exit with `EXIT_FAILURE`
		- `<pid>` will not be `0`
	- exit `EXIT_SUCCESS` on success
- no more than one function in your file

## 8. sending a signal in a shell (6 pts)

`8-signal_send.sh`

write a `sh` script that sends the `SIGQUIT` signal to a process given by its PID

- usage: `./signal_send.sh <pid>`
	- if an incorrect number of arguments is given, print `Usage: %s <pid>\n`
		- where `%s` is given by `argv[0]`
		- exit with `1`
		- `<pid>` will not be `0`

## 9. catch with sh (4 pts)

`9-handle_signal.sh`

write a `sh` script that sets a handler for the  signals `SIGABRT`, `SIGIO`, and
`SIGTERM`

- print `Nope\n` each time  `SIGABRT`, `SIGIO`, and `SIGTERM` is caught
- include a shabang
- no more than two lines in the script
- no more than one instruction per line

## 10. does it exist ? (7 pts)

`10-pid_exist.c`

write a  function that test if a process exists given its pid

- prototype: `int pid_exist(pid_t pid);`
- return `1` if the process with the given pid exist, `0` otherwise
- no more than one function in your file
- no more than one line in your function
- no more than two headers in your file
- your `signals.h` is not allowed
- the `getpgid` function is not allowed

## 11. blog post (12 pts)

write a blog post about signals

cover:
- what is a signal ?
- why do they exist ?
- when are they delivered and by whom ?
- what are the default actions of signals ?
- what happens to a process when it receives a signal without handling it ?
- what happens to a process when it receives a signal and handles it ?

include examples and at least one image at the top. publish your blog post on
Medium or Linkedin and share it.
