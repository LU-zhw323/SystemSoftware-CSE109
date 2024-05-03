# CSE 109 - Homework 2 Grading Rubric

You will get 1 point for every item completed in the follow list of program requirements.

- compiles
- `make` - builds project executable and library
- build artifacts sorted into build directory in appropriate folders
- `make clean` - remove build folder
- `make install` - moves executable to /root/bin
- parses `-a` flag, detects unknown flags.
- flag and filename input are position independent
- selects a directory from `PATH`
- open directory on `PATH`
- determine whether filename exists
- determine whether filename is executable
- searches through all directories on `PATH` until executable is found
- returns 0 on success
- returns 1 on any unfound filename
- returns 2 if invalid option is specified
- prints out path of each executable if found on `PATH`
- the `-a` flag prints all matching pathnames of each argument
- handle multiple files
