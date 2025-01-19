#ifndef _LS_H_
#define _LS_H_

#include <dirent.h>    /* opendir, readdir, closedir */
#include <errno.h>
#include <stdio.h>     /* printf, sprintf, fprintf, perror */
#include <stdlib.h>    /* exit, free, malloc */
#include <sys/types.h>
#include <sys/stat.h>  /* (syscall) lstat */
/* #include <grp.h>       /1* getgrgid *1/ */
/* #include <pwd.h>       /1* getpwuid *1/ */
/* #include <time.h>      /1* ctime *1/ */
/* #include <unistd.h>    /1* (syscalls) write, readlink *1/ */

#define _1 1
#define _A 2
#define _a 4
#define _l 8

void sort_args(
	char **argv, int argc,
	char **opts, int *num_opts,
	char **dirs, int *num_dirs);

int set_opt_flags(
	char **opt_args,
	int num_opts,
	char *prog);

/* DIR **validate_dirs( */
/* 	char **dir_args, int *num_dirs, */
/* 	char ***valid_dirs, int *num_valid, */
/* 	char ***invalid_dirs, int *num_invalid); */

struct stat **validate_paths(
	char **path_args, int *num_paths,
	char ***valid_paths, int *num_valid,
	char ***invalid_paths, int *num_invalid);

void output_valid_paths(
	struct stat **file_stats,
	char **valid_paths,
	int num_valid);

void output_valid_dirs(
	DIR **dir_refs,
	char **valid_dirs,
	int num_valid);

void output_invalid(
	char **invalid_dirs,
	int num_invalid,
	char *prog_name);

void free_all(
	void **allocations,
	int count);

#endif /* _LS_H_ */
