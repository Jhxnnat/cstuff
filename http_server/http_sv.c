#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdarg.h>

#define BUFFER_SIZE 16000
#define FILENAME_MAX_SIZE 256
#define PORT 3435

void error(const char* fmt, ...) {
	va_list ap;
	va_start(ap, fmt);
	vfprintf(stdout, fmt, ap);
	fprintf(stdout, "\n");
	fflush(stdout);
	va_end(ap);
	exit(1);
}

char *read_file(char* filepath) {
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
	// return index.html if GET /
	// if no index.html then not_found remains true
	if (buffer[5] == ' ') {
		const char index_html[] = "index.html";
		for (size_t i = 0; i < strlen(index_html); ++i) {
			file[i] = index_html[i];
		}
		return;
	}

	char* buff = buffer+5;
	size_t i = 0;
	while (true) {
		if (buff[i] == ' ' || buff[i] == '\n') break;
		file[i] = buff[i];
		i++;
	}
}

int main() {
	int server_socket;
	if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		error("error creating socket");
	}

	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET; // only ipv4
	server_address.sin_port = htons(PORT);
	server_address.sin_addr.s_addr = htons(INADDR_ANY);

	bind(server_socket, (struct sockaddr *) &server_address, sizeof(server_address));
	listen(server_socket, 5);
	printf("== listening on port %d ==\n", PORT);

	int client_socket, n;
	char buffer[BUFFER_SIZE] = {0};
	char file[FILENAME_MAX_SIZE] = {0};
	for (;;) {
		bool not_found = true;
		char* html_content = NULL;
		client_socket = accept(server_socket, NULL, NULL);

		memset(buffer, 0, BUFFER_SIZE);
		memset(file, 0, FILENAME_MAX_SIZE);

		n = read(client_socket, buffer, BUFFER_SIZE-1);
		if (n < 0) error("client_socket read error");

		fprintf(stdout, "\n%s\n", buffer);

		// ignore favicon request
		if (memcmp(file, "favicon.ico", 11) == 0) {
			continue;
		}

		get_requested_file(file, buffer);
		fprintf(stdout, "FILE: %s\n", file);

		html_content = read_file(file);
		if (html_content != NULL) not_found = false;
		if (not_found) {
			fprintf(stdout, "NOT FOUND\n");
			char* res = "HTTP/1.1 404 Not Found\r\n";
			write(client_socket, res, strlen(res));
			close(client_socket);
			continue;
		}

		// hardcoded response for now
		char* res_header = "HTTP/1.1 200 OK\r\n"
						   "Content-Type: text/html; charset=UTF-8\r\n\r\n";
		size_t response_len = strlen(res_header) + strlen(html_content);
		if (response_len >= BUFFER_SIZE) response_len = BUFFER_SIZE;
		char response[response_len];
		memset(response, 0, response_len);
		snprintf(response, response_len, "%s%s", res_header, html_content);

		write(client_socket, response, response_len);
		close(client_socket);
		free(html_content);
	}

	return 0;
}

