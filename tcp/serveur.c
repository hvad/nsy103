#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#define PORTS 60000		/* port du serveur */
#define TRUE 1

int
main ()
{
  int namelen, sock, nsock;
  char buf[20];
  char a;
  struct sockaddr_in adr_s, adr_c;
  int lg, n;
  pid_t pid;


  /* Création socket */
  if ((sock = socket (AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
    {
      perror ("socket");
      exit (errno);
    }

  /* Attachement socket */

  adr_s.sin_family = AF_INET;
  adr_s.sin_port = htons (PORTS);	/* passage au format réseau */
  adr_s.sin_addr.s_addr = htonl (INADDR_ANY);	/* n'importe quelle adresse IP de la machine locale */

  if (bind (sock, (struct sockaddr *) &adr_s, sizeof (adr_s)) < 0)
    {
      perror ("bind");
      exit (2);
    }

  if (listen (sock, 5) < 0)
    {
      perror ("listen");
      exit (4);
    }

  /* Boucle d'acceptation d'une connexion */

  while (TRUE)
    {
      lg = sizeof (adr_c);
      nsock = accept (sock, (struct sockaddr *) &adr_c, &lg);
      pid = fork ();

      if (pid == 0)
	{
	  close (sock);
	  n = recv (nsock, buf, 20, 0);
	  printf ("Chaine reçue %s\n", buf);
	  close (nsock);
	  exit (0);
	}
    }
  return 0;
}
