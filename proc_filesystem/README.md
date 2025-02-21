# Python - /proc/ filesystem

## Resources

- [proc documentation](https://www.kernel.org/doc/Documentation/filesystems/proc.txt)

## Objectives

- what is the `/proc/ filesystem` ?
- what is the `/proc/maps` file ?
- what is the `/proc/mem` file ?
- what is the link between those two files ?
- how does the virtual memory map to RAM ?

## Python

- the first line of all python scripts should be `#!/usr/bin/python3`
- conform to `PEP8` style

## Python test-cases

- document all modules, classes, and functions

# Tasks

## 0. Hack the VM (9pts)

[youtube: writing in the VM of a running process](https://www.youtube.com/watch?v=xcpXT4Bukgk)

file: `proc_filesystem/read_write_heap.py`

write a script that finds a string in the heap of a running process and replaces
it

usage: `read_write_heap.py pid search_data replace_data`\
wherein `pid` is the process id of the running program. all strings will be
ASCII

- the script should only look within the heap of the target process
- output: whatever you'd like
- when an error occurs, direct error messages to `stdout` with an exit status
  of 1

## 1. Blog posh #1 (19pts)

write a blog post about the `/proc/ filesystem`, `/proc/maps`, and `/proc/mem`
files

explain how to parse the /proc/maps file in order to read the virtual memory

include examples and at least a single image (at the top)
