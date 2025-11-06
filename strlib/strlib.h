#ifndef strlib_h
#define strlib_h

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

// reference for functions to implement:
// https://manual.gamemaker.io/monthly/en/index.htm?#t=GameMaker_Language%2FGML_Reference%2FStrings%2FStrings.htm

typedef struct {
	size_t size;
	size_t capacity;
	char* data;
} string_t;

#define STR_GROW_FACTOR 2

size_t str_len(const char* s);
char *str_copy(char* dest, const char* s);

void str_alloc(string_t *str, size_t cap);
void str_init(string_t* str, const char* init_value);
void str_free(string_t* str);
void str_cat(string_t str);
bool str_concat(string_t* dest, const char* s);
bool str_insert(string_t* dest, const char* s, int pos);
bool str_delete(string_t* dest, size_t start, size_t end);

void str_fmt(string_t* s, const char *format, ...);

void str_toupper(string_t* str);
void str_tolower(string_t* str);

// === TODO ===
//
//
string_t str_fmt_int(int value, size_t total, size_t dec);

void str_topascal(string_t* str);
void str_tosnake(string_t* str);
void str_tocamel(string_t* str);
// int str_tointeger(const char *text);
// float str_tofloat(const char *text);

// return the character position of an instance 
// of a char of a sub-string within a string
// searching from the beginning of the string
// NOTE: consider doing the oposite: str_last_pos
size_t str_pos(string_t str, const char* c);
size_t str_pos_ext(string_t str, const char* c, size_t start_pos);
size_t str_pos_c(string_t str, const char c);
size_t str_pos_c_ext(string_t str, const char c, size_t start_pos);

// if a string starts of ends with the given substring
bool str_starts_with(string_t str, const char* substr);
bool str_ends_with(string_t str, const char* substr);

// return the amount of times the given substring appears
size_t str_count(string_t str, const char* substr);

// parse a string and get only the numbers on it
string_t str_digits(const char* s);

#endif // strlib_h
