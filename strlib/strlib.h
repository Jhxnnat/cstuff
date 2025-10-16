#ifndef strlib_h
#define strlib_h

typedef struct {
	size_t size;
	size_t capacity;
	char* data;
} string_t;

#define STR_GROW_FACTOR 2

size_t str_len(const char* s);
void str_init(string_t *str, const char* init_value);
void str_free(string_t* str);
void str_cat(string_t str);

#endif // strlib_h
