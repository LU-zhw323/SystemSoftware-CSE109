# CSE 109 - Quiz 10

**Due: 4/29/2021 End of Day**

Make at least one commit per question. You can write your answers in this file, `README.md`. You can use the Gitlab interface to edit this file if you prefer.

## Question 1

Explain the technique of CPU time-sharing and how it works to give the illusion that multiple programs are running simultaneously on your computer.

Time-sharing is achieved by switching context between different programs or processes. Once there is a program running on the computer, the program counter inside the CPU will be pointed to the first instructions of the program and go over all the instructions one by one. If there is another program running on the computer simultaneously, switching context between two programs will happen. Once the program counter reaches certain instructions in program 1, it will switch to the first instruction in the program 2 and start to go over program 2. Then, once again PC reaches certain instructions in program 2, it will return to the instruction left when PC switches to program 2 and go over the rest of program 1. Finally, it will do the same thing to the remainings of program 2. Since the speed of electricity is fast, it might look like two programs are running simultaneously. 

## Question 2

- What is a PID? 
Process identifier, the unique ID for every process running on computer

- What command do you use to get a list of all running processes and their PIDs? 
ps -ef

- How do you terminate a process from the terminal?
kill PID(process identifier) or Control+C

- From the terminal, how do you run a process in the background?
put the "&" symbol after command


## Question 3

What is the return value of the `fork()` system call? 
return 0 when it is in the child process
return positive number(PID of child process) when it is in the parent process