#ifndef UTILFUNCTIONS_H_INCLUDED
#define UTILFUNCTIONS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//#define DEBUG

/* declare functions */

char* substring(char* source, int begin, int end);
char *substring2(char *source, int begin, int length);
int indexof(char* source, char* phrase);
int lastindexof(char* source, char* phrase);
char* padleft(char* source, char* fill, int lentgh);
char* strtrim(char *source);
char* strcopy(char *source);
char* strtrim(char *source);
char* strrtrim(char *source);
char* strltrim(char *source);
char* strupper(char *source);

#endif // UTILFUNCTIONS_H_INCLUDED
