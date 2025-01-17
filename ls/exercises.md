# exercise 1

write a program that takes the name of a directory as a parameter and print out
its content (the names of all files and folders within)

handle folders that don't exist

check the return values of `opendir`, `readdir`, and `closedir`

# exercise 2

extend the previous program to print out the size of the files and directories

if the file passed to `lstat` is not in the same directory as the program
calling it you're gonna have to build a string containing the file-path

# exercise 3

add file type, rights, and last modified time to the previous program

attempt to match the output of `/usr/bin/ls`

# exercise 4

add group-id and user-id to the program created thus far
