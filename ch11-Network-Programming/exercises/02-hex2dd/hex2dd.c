#include <arpa/inet.h> /* inet_ntop(), AF_INET */
#include <stdio.h> /* fprintf(), printf(), stderr, NULL, puts() */
#include <stdlib.h> /* exit(), EXIT_FAILURE, EXIT_SUCCESS, strtol */
#include <string.h> /* strerror() */
#include <errno.h> /* errno */

#define HEX_BASE 16
#define DOTTED_IP_LEN sizeof("255.255.255.255.255")

int
main(int argc, char *argv[])
{
	/* Validate command arguments */
	if (argc != 2) {
		fprintf(stderr, "Usage: %s hex-ipaddr\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	/* Parse hex IP address */
	char *endp;
	errno = 0;
	long hexIpAddr = strtol(argv[1], &endp, HEX_BASE);
	if (errno == ERANGE || hexIpAddr < 0 || hexIpAddr > 0xffffffff) {
		fprintf(stderr, "IP address invalid or out of range\n");
		exit(EXIT_FAILURE);
	} else if (errno != 0 || *endp != '\0') {
		fprintf(stderr, "Bad input\n");
		exit(EXIT_FAILURE);
	}

	/* Convert to network byte order */
	uint32_t networkOrderIpAddr = htonl(hexIpAddr);

	/* Interpret pointer as pointing to characters */
	unsigned char *binaryIpAddressStr = (unsigned char *) &networkOrderIpAddr;

	/* Conver to dotted IP */
	char dottedIpAddr[DOTTED_IP_LEN];
	if (inet_ntop(AF_INET, binaryIpAddressStr, dottedIpAddr, DOTTED_IP_LEN) == NULL) {
		fprintf(stderr, "Invalid IP: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	/* Display */
	puts(dottedIpAddr);
	exit(EXIT_SUCCESS);
}
