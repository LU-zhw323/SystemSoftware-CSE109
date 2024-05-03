# CSE 109 - Quiz 9

**Due: 4/22/2021 End of Day**

Make at least one commit per question. You can write your answers in this file, `README.md`. You can use the Gitlab interface to edit this file if you prefer.

## Question 1

Define the following computer networking terms:

- IP Address
The unique address that would be used to identify devices that are connected to the Internet. IP Address can be used in the communication between devices. 
- Port
The place with a specific address that is used in the communication between the client and specific server. Every server has its unique port and port number.
- Stream socket
Unix socket that will guarantee delivery, which means that it will notify both server and client if the message is received or sent, and guarantee order, which means the message will be received with same order of sent message. Stream socket follows TCP(transmission control protocol)
- Datagram socket
Unix socket that will not guarantee both delivery and order, but it has higher performance.Daragram socket follows UDP(User Datagram protocol)

## Question 2

Is network byte order little or big endian?
Big endian

## Question 3

On a Unix socket server, why is the client socket file descriptor passed to the `read()`/`write()` functions?
After the connect function, the client socket that was created with a specific socket file descriptor is connected with a specific server socket. Thus, we need to pass the socket file descriptor of this connected client socket to the read()/write() functions to indicate which server or which address we expect to send information to or receive information from.
