#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#define PORTS 60000 /* port du serveur */

int main()
{
  int namelen, sock; 
  char buf[20];
  struct sockaddr_in adr_s, adr_c;
  int lg, n;
  
  if ((sock = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP)) < 0)
  {
    perror("Socket error.");
    exit(1);
  }  

  adr_s.sin_family = AF_INET;
  adr_s.sin_port = htons(PORTS); /* passage au format réseau */
  adr_s.sin_addr.s_addr = INADDR_ANY; /* n'importe quelle adresse IP de la machine locale */

  if (bind(sock, &adr_s, sizeof(adr_s)) < 0)
  {
    perror("Bind error");
    exit(1);
  }
  
  for (;;)
  {
    lg = sizeof(adr_s);
    n = recvfrom (sock, buf, 20, 0, &adr_c, &lg);
    printf("Chaine reçue %s\n", buf);
  }
  
  close(sock);
  return 0;
}
