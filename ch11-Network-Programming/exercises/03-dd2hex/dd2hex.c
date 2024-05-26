#include <stdio.h> /* fprintf(), puts(), stderr */
#include <stdlib.h> /* exit(), EXIT_FAILURE */
#include <arpa/inet.h> /* inet_pton(), AF_INET */
#include <string.h> /* strerror() */
#include <errno.h> /* errno */

#define MAX_BIN_IP_LEN 65

int
main(int argc, char *argv[])
{
	/* Verify arguments were provided */
	if (argc != 2) {
		fprintf(stderr, "Usage: %s dotted-decimal-ip\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	/* Parse dotted-decimal (presentation) IP address */
	unsigned char binaryIpAddr[MAX_BIN_IP_LEN];
	
	switch (inet_pton(AF_INET, argv[1], binaryIpAddr)) {
		case -1:
			fprintf(stderr, "Error parsing IP address: %s\n", strerror(errno));
			exit(EXIT_FAILURE);
		case  0:
			fprintf(stderr, "Invalid IP address\n");
			exit(EXIT_FAILURE);
		case  1:
		default:
			/* Convert to hex */
			printf("0x");
			for (int i = 0; i < 4; i++)
				printf("%02x", binaryIpAddr[i]);
			printf("\n");
			break;
	}
	exit(EXIT_SUCCESS);
}
