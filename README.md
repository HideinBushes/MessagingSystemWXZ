# MessagingSystemWXZ
Group project of EE810

This is a Server/Client model messaging system , it uses LAN to send/receive messages. The communication protocol is developed based on TCP.

To run this system, download the folder Server and folder Client, run the executable file "servermain" in the Server folder first, 
and then run the executable file "clientmain" in Client folder. 

The server process runs in multi-thread, it can responce the request of serveral clients concurrently. To run this system, you should:
  1. Run serermain
  2. Run clientmain to create each client process.
  3. Enter your username for each client.
  4. Enter ! to refresh the online client list.
  5. Enter @username to choose another client you want to communicate with.
  6. Enter @all to broadcast your message to all clients that connected to the server.
  7. Enter # to close client.
