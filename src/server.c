#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#ifdef _WIN32
    #include <winsock2.h>
    //#pragma comment(lib,"ws2_32.lib") //Winsock Library
    #include <ws2tcpip.h>
#endif
#ifdef __linux__
    #include <unistd.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
#endif
#include <conio.h>


int32_t main(int32_t argc, char** argv) {

    printf("%i\n", sizeof(void*));
	printf("amogus\n");

    #ifdef _WIN32
        WSADATA wsa;
        if (WSAStartup(MAKEWORD(2,2), &wsa) != 0)
        {
            char c;
            printf("Failed. Error Code : %d.\nPress a key to exit...", WSAGetLastError());
            c = _getch();
            return 1;
        }
    #endif

    struct sockaddr_in address;
	int32_t sockfd, serverfd, valread, addrlen;
	addrlen = sizeof(address);
	char buffer[4096];
	if ((serverfd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
		perror("socket failed\n");
		return 0;
	}
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = 8080;
	if (bind(serverfd, (struct sockaddr*)&address, sizeof(address)) < 0) {
		perror("bind failed\n");
		return 0;
	}
	if (listen(serverfd, 3) < 0) {
		perror("listen\n");
		return 0;
	}
	if ((sockfd = accept(serverfd, (struct sockaddr*)&address, (socklen_t*)&addrlen)) < 0) {
		perror("accept\n");
		return 0;
	}
	valread = read(sockfd, &buffer, sizeof(buffer));
	printf("%s\n", &buffer[0]);

    return 0;
}