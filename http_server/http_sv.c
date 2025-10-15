#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>

#define BUFFER_SIZE 16000

int PORT = 6969;
int log_value = 0;

// TODO: scan for changes and read again to update

char *get_html_file(char* filepath) {
	long len;
	char *buff = 0;
	FILE *f = fopen(filepath, "r");
	if (f) {
		fseek(f, 0, SEEK_END);
		len = ftell(f);
		fseek(f, 0, SEEK_SET);
		buff = malloc(len);
		if (buff) {
			fread(buff, 1, len, f);
		}
		fclose(f);
	}
	return buff;
}

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
		bool not_found = false;
		client_socket = accept(server_socket, NULL, NULL);

		char buff[256] = {0};
		recv(client_socket, buff, 256, 0);

		// GET /somefile.html ...
		char* f = buff + 5;
		*strchr(f, ' ') = 0;
		char* html_content = get_html_file(f);
		if (!html_content) {
			not_found = true;
		}

		// NOTE: wtf is this?
		ssize_t bytes_read = read(client_socket, buffer, BUFFER_SIZE - 1);
		if (bytes_read >= 0) {
			buffer[bytes_read] = '\0';
			puts(buffer);
		} else {
			puts("Error reading buffer");
			return 1;
		}

		if (not_found) {
			char* res = "HTTP/1.1 404 Not Found\r\n";
			write(client_socket, res, strlen(res));
			close(client_socket);
			continue;
		}

		char* _response = "HTTP/1.1 200 OK\r\n"
						 "Content-Type: text/html; charset=UTF-8\r\n\r\n";

		char* response = malloc(strlen(_response) + strlen(html_content) + 1);
		if (!response) {
			puts("Malloc error");
			return 1;
		}

		sprintf(response, "%s%s", _response, html_content);
		response[-1] = '\0';

		write(client_socket, response, strlen(response));
		close(client_socket);
		free(response);
		free(html_content);
	}

	return 0;
}

