#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#define PORTS 60000		/* port du serveur */
#define IP_S "192.168.122.91"	/* adresse ip du serveur */

int
main ()
{
  struct sockaddr_in adr_s, adr_c;
  char buf[20];
  int sock, a;

  if ((sock = socket (AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
    {
      perror ("socket");
      exit (1);
    }

  adr_s.sin_family = AF_INET;
  adr_s.sin_port = htons (PORTS);	/* passage au format réseau */
  adr_s.sin_addr.s_addr = inet_addr (IP_S);	/* adresse IP de la machine */

  a = connect (sock, (struct sockaddr *) &adr_s, sizeof (adr_s));

  send (sock, "bonjour, serveur !! ", 20, 0);

  close (sock);

}
