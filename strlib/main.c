#include "strlib.h"

int main(void) {
	
	string_t str;
	str_alloc(&str, 64);
	str_fmt(&str, "time: %d,%d", 35, 34);
	str_cat(str);
	str_free(&str);

	// string_t str;
	// str_init(&str, "magic..thing");
	// str_cat(str);
	//
	// bool e = str_insert(&str, "resistancee", 5);
	// if (e) {
	// 	printf("insert error\n");
	// 	exit(1);
	// }
	// str_cat(str);
	//
	// e = str_concat(&str, "...");
	// if (e) {
	// 	printf("concat error\n");
	// 	exit(1);
	// }
	// str_cat(str);
	//
	// e = str_delete(&str, 0, 5);
	// if (e) {
	// 	printf("delete error\n");
	// 	exit(1);
	// }
	// str_cat(str);
	// str_free(&str);

	return 0;
}
