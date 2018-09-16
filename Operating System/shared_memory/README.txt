
/*
Open terminal and compile server.c, client1.c and client2.c

Run Server program and let it keep running.It will stop when both client read
data from shared memory.

Open new terminal and execute client1 and afterwards client2. Now the server
program should stop.

*/

/*Terminal 1*/
sanul@sanul-HP-Notebook:~/github/SPPU_TE_IT/Operating System/shared_memory$ gcc -o server server.c
sanul@sanul-HP-Notebook:~/github/SPPU_TE_IT/Operating System/shared_memory$ gcc -o client1 client1.c
sanul@sanul-HP-Notebook:~/github/SPPU_TE_IT/Operating System/shared_memory$ gcc -o client2 client2.c
sanul@sanul-HP-Notebook:~/github/SPPU_TE_IT/Operating System/shared_memory$ ./server
Enter data to write on shared memory
HelloWorld
Server : Data written on Shared Memory with key 5056
Server: Client 1 read at  local time and date: Sun Sep 16 22:36:56 2018
Server: Client 2 read at local time and date: Sun Sep 16 22:37:09 2018
sanul@sanul-HP-Notebook:~/github/SPPU_TE_IT/Operating System/shared_memory$

/*Terminal 2*/
sanul@sanul-HP-Notebook:~/github/SPPU_TE_IT/Operating System/shared_memory$ ./client1
Client 1 : Data read from Shared Memory with key 5056
HelloWorld
sanul@sanul-HP-Notebook:~/github/SPPU_TE_IT/Operating System/shared_memory$ ./client2
Client 2 : Data read from Shared Memory with key 5056
HelloWorld
sanul@sanul-HP-Notebook:~/github/SPPU_TE_IT/Operating System/shared_memory$
