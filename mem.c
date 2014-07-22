#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

void *debug_malloc(size_t size, const char* file, int line) {
	void *p = malloc(size);

	if (p == NULL) {
		return NULL;
	}

	char buff[256];

	sprintf(buff, "%p.mem", p);

	FILE *f = fopen(buff, "w");

	fprintf(f, "File: %s\nLine: %d\nSize: %zu bytes\n", file, line, size);
	fclose(f);

	return p;
}

void *debug_calloc(size_t count, size_t size, const char* file, int line) {
	void *p = calloc(count, size);

	if (p == NULL) {
		return NULL;
	}

	char buff[256];

	sprintf(buff, "%p.mem", p);

	FILE *f = fopen(buff, "w");

	fprintf(f, "File: %s\nLine: %d\nSize: %zu bytes\n", file, line, 
		count * size);
	fclose(f);

	return p;
}

void *debug_realloc(void *ptr, size_t size, const char* file, int line) {
	void *p = realloc(ptr, size);

	if (p == NULL) {
		return NULL;
	}

	char buff[256];
	//Delete the old pointer record
	sprintf(buff, "%p.mem", ptr);
	unlink(buff);

	//Create the new pointer record
	sprintf(buff, "%p.mem", p);

	FILE *f = fopen(buff, "w");

	fprintf(f, "File: %s\nLine: %d\nSize: %zu bytes\n", file, line, size);
	fclose(f);

	return p;
}

void debug_free(void *p) {
	char buff[256];

	sprintf(buff, "%p.mem", p);
	unlink(buff);

	free(p);
}

