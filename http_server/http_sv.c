#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdarg.h>

#define BUFFER_SIZE 16000
#define FILE_SIZE 256
#define PORT 6968

void error(const char* fmt, ...) {
	va_list ap;
	va_start(ap, fmt);
	vfprintf(stdout, fmt, ap);
	fprintf(stdout, "\n");
	fflush(stdout);
	va_end(ap);
	exit(1);
}

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

void get_requested_file(char *file, char* buffer) {
	// NOTE: file should be zeroed
	int i = 5;

	// root edge case (return index.html)
	if (buffer[5] == ' ') {
		// if there is no index.html not_found will remain true
		const char* index_html = "index.html";
		for (size_t j = 0; j<strlen(index_html); ++j) {
			file[j]=index_html[j];
		}
		return;
	}

	while (true) {
		if (buffer[i] == ' ') break;
		else if (buffer[i] == '\n') break; //just in case
		file[i-5] = buffer[i];
		i++;
	}
}

int main() {
	int server_socket;
	if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		error("error creating socket");
	}

	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(PORT);
	server_address.sin_addr.s_addr = htons(INADDR_ANY);

	bind(server_socket, (struct sockaddr *) &server_address, sizeof(server_address));
	listen(server_socket, 5);
	printf("== listening on port %d ==\n", PORT);

	int client_socket, n;
	char buffer[BUFFER_SIZE];
	char file[FILE_SIZE] = {0};
	for (;;) {
		int s = 0;
		bool not_found = true;
		char* html_content;
		client_socket = accept(server_socket, NULL, NULL);

		memset(buffer, 0, BUFFER_SIZE);
		memset(file, 0, FILE_SIZE);
		while ((n = read(client_socket, buffer, BUFFER_SIZE-1)) > 0) {
			// Request example: GET /somefile.html ...
			if (!s) { // lookup for the file on first line
				s = 1;
				get_requested_file(file, buffer);
				if ((html_content = get_html_file(file))) not_found = false;
			}

			fprintf(stdout, "\n%s", buffer);
			// VERY reliable way to detect end of the request :)
			if (buffer[n-1] == '\n') break;
			memset(buffer, 0, BUFFER_SIZE);
		}
		if (n < 0) error("error reading buffer");

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
			error("malloc error");
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

