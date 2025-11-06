#include "strlib.h"

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

void str_alloc(string_t *str, size_t cap) {
	if (str->capacity == 0) {
		str->capacity = cap;
		str->data = calloc(cap, sizeof(char));
		//TODO: can make a errnull function for this (or use errno)
		if (str->data == NULL) {
			printf("error allocating string\n");
			exit(1);
		}
	} else if (cap > str->capacity) {
		str->capacity = cap;
		char *temp = reallocarray(str->data, cap, sizeof(char));
		if (temp == NULL) {
			printf("error realloc\n");
			exit(1);
		} else str->data = temp;
	}
	str_set(str->data, 0, str->capacity);
}

void str_init(string_t *str, const char* init_value) {
	size_t len = str_len(init_value);
	str->size = len;
	
	// first time
	if (str->capacity == 0) {
		str->capacity = len * STR_GROW_FACTOR;
		str->data = calloc(str->capacity, sizeof(char));
		if (str->data == NULL) {
			printf("error allocating string\n");
			exit(1);
		}
	}
	// was initialized before
	else if (str->capacity < len) {
		str->capacity = len * STR_GROW_FACTOR;
		// char *temp = realloc(str->data, str->capacity * sizeof(char));
		char *temp = reallocarray(str->data, str->capacity, sizeof(char));
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

void str_fmt(string_t* s, const char *format, ...) {
	va_list args;
	va_start(args, format);
	int bytecount = vsnprintf(s->data, s->capacity, format, args);
	va_end(args);
	if (bytecount >= s->capacity) {
		s->size = s->capacity;
		char *trunc = s->data + s->capacity - 4;
		sprintf(trunc, "...");
	} else {
		s->size = bytecount;
	}
}

char upper(char c) {
	if (c >= 97 && c <= 122) {
		return c - 32;
	}
	return c;
}


char lower(char c) {
	if (c >= 65 && c <= 90) {
		return c + 32;
	}
	return c;
}

bool is_letter() {
	return false;
}

void str_toupper(string_t* str) {
	for (size_t i = 0; i < str->size; ++i) {
		str->data[i] = upper(str->data[i]);
	}
}

void str_tolower(string_t* str) {
	for (size_t i = 0; i < str->size; ++i) {
		str->data[i] = lower(str->data[i]);
	}
}

void str_topascal(string_t* str) {
	str->data[0] = _upper(str->data[0]);
	for (size_t i = 0; i < str->size; ++i) {
		// check if current is space
		// check if next is letter
		if (str->data[i] == 32 && is_letter(str->data[i+1])) {

		}
	}
}

