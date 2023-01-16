/*	Instituto Superior de Engenharia de Lisboa
 *	Ezequiel Conde, 2023
 *
 * 	Obter o endereço IP dado o identificador da interface
 *
 *	Exemplo:
 * 		$ ipaddress enp4s0
 *
 * 	Documentação:
 *
 * 		$ man netdevice
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <netinet/in.h>
#include <errno.h>
static void usage(char *prog_name) {
	fprintf(stderr, "%s <interface>\n", prog_name);
}

int main(int argc, char *argv[]) {
		if (argc != 2) {
		usage(argv[0]);
		exit(EXIT_FAILURE);
	}

	int socket_fd = socket(PF_INET, SOCK_DGRAM, 0);
	if (socket_fd < 0) {
		fprintf(stderr, "socket(...)=%d, error=(%d) %s",
			socket_fd, errno, strerror(errno));
			exit(EXIT_FAILURE);
		}
	struct ifreq ifr;
	memset(&ifr, 0, sizeof(ifr));
	strncpy(ifr.ifr_name, argv[1], sizeof(ifr.ifr_name));
	((struct sockaddr_in*)&ifr.ifr_addr)->sin_family = AF_INET;
	int result = ioctl(socket_fd, SIOCGIFADDR, &ifr);
	if (result < 0) {
		fprintf(stderr, "ioctl(%d, ...)=%d, error=(%d) %s",
			socket_fd, result, errno, strerror(errno));
			exit(EXIT_FAILURE);
	}
	in_addr_t ip_address = ((struct sockaddr_in*)&ifr.ifr_addr)->sin_addr.s_addr;
	printf("%d.%d.%d.%d", ip_address & 0xff, (ip_address & 0xff00) >> 8,
		(ip_address & 0xff0000) >> 16, (ip_address & 0xff000000) >> 24);
}
