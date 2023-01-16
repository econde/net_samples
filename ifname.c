#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <net/if.h>

static void usage(char *prog_name) {
	fprintf(stderr, "%s <interface>\n", prog_name);
}

static char ifnames[3][IFNAMSIZ];

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))

int main(int argc, char *argv[]) {
	if (argc != 2) {
		usage(argv[0]);
		exit(1);
	}
	struct ifreq ifr;
	int socket_fd = socket(AF_INET, SOCK_DGRAM, 0);

#if 0
	memset(&ifr, 0, sizeof(ifr));
	strncpy(ifr.ifr_name, argv[1], IFNAMSIZ);
	ioctl(socket_fd, SIOCGIFINDEX, &ifr);
	printf("Interface index =%d\n", ifr.ifr_ifindex);
#endif

#if 1
	int i;
	for (i = 0; i < ARRAY_SIZE(ifnames); ++i) {
		memset(&ifr, 0, sizeof(ifr));
		ifr.ifr_ifindex = i + 1;
		int result = ioctl(socket_fd, SIOCGIFNAME, &ifr);
		if (result == 0) {
			strcpy(ifnames[i], ifr.ifr_name);
			printf("Interface index = %d, interface name = %s\n",
				ifr.ifr_ifindex,  ifr.ifr_name);
		}
	}
#endif
	
	for (i = 0; i < ARRAY_SIZE(ifnames); ++i) {
		char filename[100];
		char buffer[100];
		strcpy(filename, "/sys/class/net/");
		strcat(filename, ifnames[i]);
		strcat(filename, "/device/modalias");
		FILE *fd = fopen(filename, "r");
		if (fd != NULL) {
			fgets(buffer, sizeof(buffer), fd);
			printf("%s - %s\n", filename, buffer);
		}
	}

	return 0;
}
