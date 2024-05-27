#include <stdio.h> /* fprintf(), printf(), stderr, NULL */
#include <stdlib.h> /* exit(), EXIT_FAILURE */
#include <string.h> /* memset() */

#include <arpa/inet.h> /* inet_ntop(), AF_INET */
#include <sys/types.h>	/* getaddrinfo(), freeaddrinfo(), gai_strerror(), struct addrinfo */
#include <sys/socket.h>
#include <netdb.h>

#define MAX_IP_ADDR_LEN sizeof("255.255.255.255")

int
main(int argc, char *argv[])
{
	struct addrinfo *p, *listp, hints;
	char buf[MAX_IP_ADDR_LEN];
	int rc;
	struct sockaddr sa;

	if (argc != 2) {
		fprintf(stderr, "Usage: %s <domain_name>", argv[0]);
		exit(EXIT_FAILURE);
	}

	/* Get a list of addrinfo records */
	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_INET;			/* IPv4 only */
	hints.ai_socktype = SOCK_STREAM;	/* Connections only */
	if ((rc = getaddrinfo(argv[1], NULL, &hints, &listp)) != 0) {
		fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(rc));
		exit(EXIT_FAILURE);
	}

	/* Walk the list and display each IP address */
	for (p = listp; p != NULL; p = p->ai_next) {
		struct sockaddr_in *sain = (struct sockaddr_in *) p->ai_addr;
		if (inet_ntop(AF_INET, &(sain->sin_addr), buf, MAX_IP_ADDR_LEN) == NULL) {
			fprintf(stderr, "Error converting IP address: %s\n", (unsigned char *) (p->ai_addr));
			exit(EXIT_FAILURE);
		}
		printf("%s\n", buf);
	}

	/* Clean up */
	freeaddrinfo(listp);
	
	exit(EXIT_SUCCESS);
}
