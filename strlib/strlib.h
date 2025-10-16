#ifndef strlib_h
#define strlib_h

typedef struct {
	unsigned int len;
	char* data[0];
} string;

string* str_init(const char* init_value);
bool str_concat(string* dest, const char* value);
unsigned int str_len(string* str);
bool str_free(string* str);

#endif // strlib_h
