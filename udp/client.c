#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#define PORT_C 2059 /* port du client */
#define PORT_S 60000 /* port du serveur */
#define IP_S "192.168.14.178" /* adresse ip du serveur */
 
main()
{

  struct hostent *h;
  char buf[20];
  int sock;

  if((sock = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP)) < 0)
  {
    perror("socket");
    exit(1);
  }

  struct sockaddr_in adr_c; 
  adr_c.sin_family = AF_INET;
  adr_c.sin_port = htons(PORT_C); /* passage au format réseau */
  adr_c.sin_addr.s_addr = INADDR_ANY; /* n'importe quelle adresse IP de la machine locale */

  if(bind(sock, &adr_c, sizeof(adr_c)) < 0 )
  {
    perror("bind");
    exit(2);
  }

  struct sockaddr_in adr_s;
  adr_s.sin_family = AF_INET;
  adr_s.sin_port = htons(PORT_S); /* passage au format réseau */
  adr_s.sin_addr.s_addr = inet_addr(IP_S); 

  sendto(sock, "bonjour, serveur !! ", 20, 0, &adr_s, sizeof(adr_s));

  printf("Hello.\n");

  close(sock);
  return 0;
}  
