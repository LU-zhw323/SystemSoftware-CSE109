# CSE 109 - Homework 2

**Due Date: 2/15/2021**

## Assignment

For this assignment you will write a clone of the the `which` program called `my_which`. This program will search through your PATH variable to find the directory or directories in which a target program is found. For example:

```
$ my_which gcc
```

will have the output: `/usr/local/bin/gcc`. Here is the man page for which:

```
WHICH(1)                                                        General Commands Manual                                                        WHICH(1)

NAME
       which - locate a command

SYNOPSIS
       which [-a] filename ...

DESCRIPTION
       which returns the pathnames of the files (or links) which would be executed in the current environment, had its arguments been given as commands
       in a strictly POSIX-conformant shell.  It does this by searching the PATH for executable files matching the names of the arguments. It does  not
       canonicalize path names.

OPTIONS
       -a     print all matching pathnames of each argument

EXIT STATUS
       0      if all specified commands are found and executable

       1      if one or more specified commands is nonexistent or not executable

       2      if an invalid option is specified
```

Your clone should behave exactly the same way as `which`, including the flags and the output values. 

Your program should:

- Read in the `PATH` variable. Save it to a variable local to your program.
- Read and parse command line inputs.
- Recognize all flags passed as inputs, separate them from the file names
- Determine if the `-a` flag is passed, and if an unknown flags are passed.
- Iterate through the `PATH` directories and look inside each one to find if:
  - A file with that name exists in that directory
  - If the file exists, is it executable?
  - If both conditions are true, then print the path and the filename to `stdout`.
  - Move on to the next filename if the `-a` flag is not passed into the program. If `-a` is passed into the program, continue looping through the remaining directories in the PATH to find duplicate files.
- Return the appropriate value according to the manual.

In a static library, implement the function `file_exists()`. You will link to this library from `main.c` and use this function to implement the logic of your program. 

- `file_exists()` - Takes as input a path to a file, and determines if the file exists and is executable (the [`access()`](https://linux.die.net/man/2/access) function might help you here) at that location. Returns 0 if it does not, 1 if it does.

You may implement more functions in your library as needed. Modify the Makefile to compile `main.c` to the executable `my_which`. Store this binary in `build/bin`. Store object files in `build/objects`. Store library in `build/lib`.

The command `make install` should move the `my_which` binary to `/root/bin`. Implement `make clean` to remove the `build` folder and all contents.

# Instructions

The process of working on assignments will proceed as follows:

1. Fork the relevant repository into your CSE 109 group namespace. [Instructions](https://docs.gitlab.com/ee/workflow/forking_workflow.html#creating-a-fork)

2. Clone your newly forked repository to your computer. Your repository should be hosted at 
```
https://gitlab.com/<your user name>-cse109/<assignment name>
```
You can use the following git command with the appropriate values substituted to customize it for you:
```
git clone https://gitlab.com/<your user name>-cse109/<assignment name>
```
[Instructions](https://docs.gitlab.com/ee/gitlab-basics/start-using-git.html#clone-a-repository) 

3. Write the necessary code to get your project to pass the tests.

4. Commit the changes you made locally to your gitlab repository. Follow the instructions [here](https://githowto.com/staging_and_committing) (read sections 6, 7 and 8) about staging and committing changes.

5. Check the status of your commit with the appropriate values substituted to customize it for you at: 
```
https://gitlab.com/<your user name>-cse109/<assignment name>/pipelines
```
