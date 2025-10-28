#include <stdio.h>
#include <stdlib.h>
#include "strlib.h"

int main(void) {
	string_t str;
	str_init(&str, "magic..thing");
	str_cat(str);

	bool e = str_insert(&str, "resistancee", 5);
	if (e) {
		printf("insert error\n");
		exit(1);
	}
	str_cat(str);

	e = str_concat(&str, "...");
	if (e) {
		printf("concat error\n");
		exit(1);
	}
	str_cat(str);
	
	e = str_delete(&str, 0, 5);
	if (e) {
		printf("delete error\n");
		exit(1);
	}
	str_cat(str);

	str_free(&str);
	return 0;
}

void str_cat(string_t str) {
	printf("%s[%d,%d]\n", str.data, (int)str.size, (int)str.capacity);
}

size_t str_len(const char* s) {
	size_t i = 0;
	while (s[++i] != '\0');
	return i;
}

char *str_copy(char* d, const char* s) {
	char *_r = d;
	while (*s) {
		*d++ = *s++;
	}
	*d = 0;
	return _r;
}

void str_set(char* dest, int c, size_t n) {
	for (size_t i = 0; i<n; ++i) {
		dest[i] = c;
	}
}

void str_init(string_t *str, const char* init_value) {
	size_t len = str_len(init_value);
	str->size = len;
	
	// first time
	if (str->capacity == 0) {
		str->capacity = len * STR_GROW_FACTOR;
		str->data = malloc(str->capacity * sizeof(char));
		if (str->data == NULL) {
			printf("error allocating string\n");
			exit(1);
		}
	}
	// was initialized before
	else if (str->capacity < len) {
		printf("before\n");
		str->capacity = len * STR_GROW_FACTOR;
		char *temp = realloc(str->data, str->capacity * sizeof(char));
		if (temp == NULL) {
      printf("error realloc\n");
      exit(1);
		} else str->data = temp;
	}

	str_set(str->data, 0, str->capacity);
	str_copy(str->data, init_value);
}

// Deletes a part of a string of string_t
bool str_delete(string_t* dest, size_t start, size_t end) {
	if (start > end 
			|| start > dest->size 
			|| end > dest->size) return true;
	
	for (size_t i = start; i < dest->size; ++i) {
		dest->data[i] = dest->data[i+(end-start)+1];
	}
	dest->size -= (end-start+1);
	return false;
}

// Inserts a const string at any position of a string_t
//   size_t pos can be -1 to insert at the end
bool str_insert(string_t* dest, const char* s, int _pos) {
	int pos = _pos;
	if (_pos < 0 || _pos > dest->size) pos = dest->size - 1;

	size_t len = str_len(s);
	size_t new_len = dest->size + len;
	if (dest->capacity < new_len) {
		dest->capacity = new_len * STR_GROW_FACTOR;
		char *temp = realloc(dest->data, dest->capacity * sizeof(char));
		if (temp == NULL) {
			return true;
		} else {
			dest->data = temp;
		}
	}

	int diff = dest->size - pos;
	for (size_t i = 0; i < diff-1; ++i) {
		size_t n = dest->size + len - i - 1;
		dest->data[n] = dest->data[dest->size-i-1];
	}
	for (size_t i = 0; i < len; ++i) {
		dest->data[pos+i+1] = s[i];
	}
	dest->size += len;
	return false;
}

// Add a constant string to a string_t at the end
//   just a wrapper
bool str_concat(string_t* dest, const char* s) {
	return str_insert(dest, s, -1);
}

void str_free(string_t* str) {
	str->size = 0;
	str->capacity = 0;
	free(str->data);
}
