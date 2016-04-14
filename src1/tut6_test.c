          #include <sys/types.h>
          #include <sys/socket.h>
          #include <netinet/in.h>
          #include <netdb.h>
          #include <stdio.h>
          #include <string.h>
          #include <unistd.h>
          #include <stdlib.h>
		  #include "../include/shared_mem.h"
		  
          #define TRUE 1
		  
		  struct my_elt
			{char elt_ID[5];
			char elt_name[50];
			int rez_tst;
			};
          

		   
		
          main()
          {
                  int sock, length;
                  struct sockaddr_in server;
                  int msgsock, j, i;
                  char buf[1024], b[6];
                  int rval;
				  struct my_elt mass[6];

				  delay(1500);
				  open_shmem();
				  delay(1000);
				  printf("cvs=%d\n", p->cvs);
				  if (p->cvs==10) i=6;				//cvs test
								else if (p->cvs==11) i=6;								
									else {printf("CVS!=10,11. ERROR\n");exit(1);}
				  printf("cvs=%d\n", p->cvs);
                  /* Create socket */
                  sock = socket(AF_INET, SOCK_STREAM, 0);
                  if (sock < 0) 
				  {
                          perror("opening stream socket");
                          exit(1);
                  }
				  printf ("create socket_ok\n\n");
                  /* Name socket using wildcards */
                  server.sin_family = AF_INET;
                  server.sin_addr.s_addr = INADDR_ANY;  
                  server.sin_port = htons(1030); //add port
                  printf ("socet start_ok\n\n");
				  if (bind(sock, (struct sockaddr *)&server, sizeof(server))) 
				  {
                          perror("binding stream socket");
                          exit(1);
                  }
				  printf ("bind_ok\n\n");
                  /* Find out assigned port number and print it out */
                  length = sizeof(server);
                  if (getsockname(sock, (struct sockaddr *)&server, &length)) 
				  {
                          perror("getting socket name");
                          exit(1);
                  }
                  printf("Socket has port #%d\n", ntohs(server.sin_port));

                  /* Start accepting connections */
                  printf ("start accepting connections\n\n");
				  listen(sock, 5);
				  printf ("listen_ok\n\n");
                  do {				 
                          msgsock = accept(sock, 0, 0);
						  printf ("ok\n\n");
                          if (msgsock == -1) 
						  {
                                  perror("accept");
								  return EXIT_FAILURE;
                          } 
						  else do {
                                  memset(buf, 0, sizeof(buf));
                                  if ((rval  = read(msgsock, buf,  1024)) < 0)
                                          perror("reading stream message");
                                  else if (rval == 0)
                                          printf("Ending connection %d\n", rval);
										else {								 
										for (j=0; j<i; j++) mass[j].rez_tst=2;//b[j]=2;	
										write(msgsock, mass, sizeof(struct my_elt)*i);			
										printf("-->%s %d \n", b,rval);
																	}								  
                          } 
						  while (rval > 0);
                          close(msgsock);
                  } 
				  while (TRUE);
                  /*
                   * Since  this program has  an infinite loop,  the socket "sock" is
                   * never explicitly closed.  However, all sockets will be closed
                   * automatically when  a process is killed  or terminates normally.
                   */
          }
