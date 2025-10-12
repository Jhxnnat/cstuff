#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>

#define PORT 6969
#define BUFFER_SIZE 16000

int log_value = 0;

int main() {
	int server_socket;
	if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		puts("error creating socket");
		return 1;
	}

	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(PORT);
	server_address.sin_addr.s_addr = htons(INADDR_ANY);

	bind(server_socket, (struct sockaddr *) &server_address, sizeof(server_address));
	listen(server_socket, 5);
	printf("== listening on port %d ==\n", PORT);

	int client_socket;
	char buffer[BUFFER_SIZE];
	for (;;) {
		client_socket = accept(server_socket, NULL, NULL);
		ssize_t bytes_read = read(client_socket, buffer, BUFFER_SIZE - 1);
		if (bytes_read >= 0) {
			buffer[bytes_read] = '\0';
			puts(buffer);
		} else {
			puts("Error reading buffer");
			return 1;
		}
		char* response = "HTTP/1.1 200 OK\r\n"
						 "Content-Type: text/html; charset=UTF-8\r\n\r\n"
						 "<html>\r\n"
						 "<head>\r\n"
						 "<title>Tiny Http Server</title>\r\n"
						 "<body>\r\n"
						 "Tiny Http Server\r\n"
						 "</body>\r\n"
						 "</head>\r\n"
						 "</html>\r\n";
		write(client_socket, response, strlen(response));
		close(client_socket);
	}

	return 0;
}

