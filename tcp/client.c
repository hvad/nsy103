#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#define PORTS 60000 /* port du serveur */
#define PORTC 60001 /* port du client */
#define IP_S "192.168.14.186" /* adresse ip du serveur */

int main() 
{
  struct hostent *h; /* TODO */
  struct sockaddr_in adr_s,adr_c; 
  char buf[20];
  int sock;

  if((sock = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP)) < 0)
  {
    perror("socket");
    exit(1);
  }

  adr_c.sin_family = AF_INET;
  adr_c.sin_port = htons(PORTC); /* passage au format réseau */
  adr_c.sin_addr.s_addr = INADDR_ANY; /* n'importe quelle adresse IP de la machine locale */

  if(bind(sock, (struct sockaddr*) &adr_c, sizeof(adr_c)) < 0)
  {
    perror("bind");
    exit(2);
  }

  adr_s.sin_family = AF_INET;
  adr_s.sin_port = htons(PORTS); /* passage au format réseau */
  adr_s.sin_addr.s_addr = inet_addr(IP_S); /* adresse IP de la machine */


  if(connect(sock, (struct sockaddr*) &adr_s, sizeof(adr_s)) < 0)
  {
    perror("connect");
    exit(3);
  }  

  write(sock, "bonjour, serveur !!", 20);
  
  close(sock);    

}

