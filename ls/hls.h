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

typedef struct stat _stat_struct;

/**
 * struct _path_data - container for all the relevant items pertinent to a
 * given path
 * @name: the string name the path
 * @stream: a handle on a read stream of a given directory or file
 * @stat: a structure containing metadata about the path
 * @errcode: any error code encountered when dealing with the path
 */

typedef struct _path_data
{
	char *name;
	DIR *stream;
	struct stat *stat;
	int errcode;
} path_data;

void sort_args(
	char **argv, int argc,
	char **opts, int *num_opts,
	char **dirs, int *num_dirs);

int set_opt_flags(
	char **opt_args,
	int num_opts,
	char *prog);

path_data **init_path_data_chain(
	char **path_args,
	int *num_paths);

/* void print_paths( */
/* char *program, */
/* path_data **data_chain, */
/* int num_paths); */

void print_errors(
	char *program,
	path_data **data_chain,
	int *indeces,
	int num_err);

void print_reg_paths(
	path_data **data_chain,
	int *indeces,
	int num_reg);

void print_dir_paths(
	path_data **data_chain,
	int *indeces,
	int num_dir);

void free_data_chain(
	path_data **data_chain,
	int num_paths);

#endif /* _LS_H_ */
