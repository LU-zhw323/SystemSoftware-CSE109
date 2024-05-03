# CSE 109 - Homework 8

**Due Date: 4/23/2021 EOD**

## Instructions

**Read thoroughly before starting your project:**

1. Fork this repository into your CSE109 project namespace. [Instructions](https://docs.gitlab.com/ee/workflow/forking_workflow.html#creating-a-fork)
2. Clone your newly forked repository onto your development machine. [Instructions](https://docs.gitlab.com/ee/gitlab-basics/start-using-git.html#clone-a-repository) 
3. As you are writing code you should commit patches along the way. *i.e.* don't just submit all your code in one big commit when you're all done. Commit your progress as you work. **You should make at least one commit per function.**
4. When you've committed all of your work, there's nothing left to do to submit the assignment.

## Assignment

This homework assignment is pretty straightforward. You won't have to write a lot of code, because the code is already written for you in in the Week 11 reading. The main purpose of this assignment is to prepare you for Homework 9, which will be the last homework assignment before the Final Exam. Homework 9 will integrate many of the topics we've covered throughout the course into one assignment, so I want to make sure you have a basic grasp on Unix Sockets before we try something harder.

All instructions in this assignment related to the Week 11 reading found [here](https://www.tutorialspoint.com/unix_sockets/socket_quick_guide.htm). You will be writing this assignment in C, so you'll be using the `gcc` compiler again instead of `g++`.

## Part 1 - Client

Copy the client code from the Unix Socket Tutorial into a file called `src/bin/client.c`. Write a Makefile in the project root with the following directives:

- `client` - builds the `client.c` source code into an executable called `client` and places it in `build/bin/release`
- `clean` - removes the `build` directory and all contents

### Explanation

As you did on the Midterm Exam, I want you to record yourself explaining this program to me. In particular, explain the following lines of code.

- `sockfd = socket(AF_INET, SOCK_STREAM, 0);`
- `connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr))`
- `fgets(buffer,255,stdin);`
- `n = write(sockfd, buffer, strlen(buffer));`
- `n = read(sockfd, buffer, 255);`

Explain the purpose of these functions, what the input arguments mean, and what the return values indicate. Also explain their context in the larger client program.

Upload this video to your Gitlab repository.

## Part 2 - Server

Copy the single connection server code from the Unix Socket Tutorial into a file called `src/bin/server.c`. Modify your Makefile to include the following directive:

- `server` - builds the `server.c` source code into an executable called `server` and places it in `build/bin/release`

### Explanation

Record another video that explains the server program to me. In particular, explain the following lines of code:

- `sockfd = socket(AF_INET, SOCK_STREAM, 0);`
- `bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)`
- `listen(sockfd,5);`
- `newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen);`
- `n = read( newsockfd,buffer,255 );`
- `n = write(newsockfd,"I got your message",18);`

Explain the purpose of these functions, what the input arguments mean, and what the return values indicate. Also explain their context in the larger server program.

Upload this video to your Gitlab repository.

## Part 3 - Demonstration

Record one final video demonstrating the client and server communicating with eachother. Build your client and server programs with your Makefile. You'll want to open two different terminals to demonstrate the programs communicating. In one terminal, start up the server on a port (5001 is the one used in the source, but it does't really matter. If this is being used on your computer, choose a different one). In a second terminal, start your client program and have it connect to your server. Make sure the client and server programs are arranged side-by-side, so you can see the messages in both terminatls. The client terminal will prompt you to enter a message. You can enter anything you like, and you should see your message arrive at the server terminal with the message `"Here is the message:"`. The server will send back the message `"I got your message"` to the client, and you should see that appear in the client window.

Upload this video to your Gitlab repository.
