#include <stdio.h>
#include <stdlib.h>
#include "strlib.h"

int main(void) {
	string_t str;

	str_init(&str, "magic 123");
	str_cat(str);

	str_init(&str, "magic");
	str_cat(str);

	// str_concat(" representation");
	// str_cat(str);
	
	// str_insert(&str, 5, "//");
	// str_cat(str);
	
	// str_delete(&str, 2, 4);
	// str_cat(str);

	str_free(&str);
	return 0;
}

void str_cat(string_t str) {
	printf("%s - %d,%d\n", str.data, (int)str.size, (int)str.capacity);
}

size_t str_len(const char* s) {
	size_t i = 0;
	while (s[++i] != '\0');
	return i;
}

// void *memcpy(void dest[restrict .n], const void src[restrict .n],
//              size_t n);
void str_cpy(char* dest, const char* s, size_t len) {
	for (size_t i = 0; i<len; ++i) {
		dest[i] = s[i];
	}
}

// void *memset(void s[.n], int c, size_t n);
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
	str_cpy(str->data, init_value, len);
}


// TODO: 
// bool str_concat(string_t* dest, const char* value);
// bool str_insert();
// bool str_delete();

void str_free(string_t* str) {
	str->size = 0;
	str->capacity = 0;
	free(str->data);
}
