//создание СОКЕТА  для протокола TCPIP
int sock;
struct sockaddr_in server;
struct hostent *hp, *gethostbyname();

int CrSocket(char* host,char* port)
	{
/* Create socket */
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock < 0) {
	perror("opening stream socket");
	return -1;//exit(1);
	 }
/* Connect socket  using name specified by  command line.  */
	server.sin_family = AF_INET;
	server.sin_addr.s_addr=INADDR_ANY;
	hp = gethostbyname(host);
	if (hp == 0) 
		{
		printf("\n%s: unknown host\n",host );
		return -1;//exit(2);
	 	}
//		delay (500);	
	memcpy(&server.sin_addr, hp->h_addr, hp->h_length);
	server.sin_port = htons(atoi(port));
//	printf("server.sin_port=#%d \n",server.sin_port);

	if (connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0) 
		{
//		delay (500);
		perror("connecting stream socket");
		return -1;//exit(1);
		}
//		delay (500);
//	printf("\nклиент:server.sin_port=%d\n",server.sin_port);
	return sock;
	}