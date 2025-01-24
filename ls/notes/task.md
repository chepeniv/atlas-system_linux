# core task

## task 0 - something simple (3pts)

usage: `hls`

create a program that list the contents of the current directory

## task 1 - some parameters (6pts)

usage: `hls [FILE]...`

take one or more file or directory names as parameters

errors must match `/usr/bin/ls`'s error output

	- in `stderr`
	- `<program>:` (stored in `argv[0]`)
	- `[ERROR_MSG]`
	- exit value

## task 2 - options (7pts)

usage: `hls [-1] [FILE]...` or `hls [FILE]... [-1]`

implement the single column option `-1`

going forward, options will be identified with a command-line argument
beginning with a `-` character

take note of the edge cases. be able to handle multiple options in any order

## task 3 - hidden files (7pts)

usage: `hls [-a1] [FILE]...`

implement the `-a` option

## task 4 - almost all (7pts)

usage: `hls [-A] [FILE]...`

implement the `-A` option

## task 5 - more details (5pts)

usage: `hls [-l] [FILE]...`

implement the `-l` option

you may ignore the `total ##` output line given by `-l`

note: usernames and group names are not always defined

# advanced task

not yet
