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
bool str_concat(string_t* dest, const char* s);
bool str_insert(string_t* dest, const char* s, int pos);
bool str_delete(string_t* dest, size_t start, size_t end);

#endif // strlib_h
