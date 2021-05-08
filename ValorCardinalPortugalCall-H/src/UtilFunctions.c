
#include "UtilFunctions.h"

/* Util functions */


char* strcopy(char *source)
{
    size_t slen = strlen(source);
    char *result = calloc(slen + 1, sizeof(char));
    //char *result = malloc(slen);
    //memset(result, 0, slen);
    strcpy(result, source);

    #ifdef DEBUG
        printf("function 'strcopy' result:[%s]\n", result);
    #endif

    return result;
}

char* substring(char *source, int begin, int end)
{
    // get length of the destination string
    int len = end - begin;

    char *dest = calloc(len + 1, sizeof(char));
    //char *dest = malloc(len + 1);
    //memset(dest, 0, len + 1);

    for (int i = begin; (i < end) && (*(source + i) != '\0'); i++)
    {
        *dest = *(source + i);
        dest++;
    }

    *dest = 0; //NULL

    char* result = (dest - len);

    #ifdef DEBUG
        printf("function 'substr' result:[%s]\n", result);
    #endif

    return result;
}

char *substring2(char *source, int begin, int length)
{
   char *p = calloc(length + 1, sizeof(char));

   int c;
   for (c = 0; c < length; c++)
   {
      *(p + c) = *(source + begin );//- 1);
      source++;
   }

   *(p + c) = '\0';

   return p;
}

int indexof(char *source, char *phrase)
{
     int result = -1;

     //strchr
     char *p = strstr(source, phrase);
     if (p)
        result = p - source;

    #ifdef DEBUG
        printf("function 'indexof' result:[%d]\n", result);
    #endif

    return result;
}

int lastindexof(char *source, char *phrase)
{
     int result = -1;
     char *match = source;

     while (match)
     {
        match = strstr(match, phrase);
        if (match)
        {
            result = match - source;
            match += sizeof(phrase)-1;
        }
    }

    #ifdef DEBUG
        printf("function 'lastindexof' result:[%d]\n", result);
    #endif

    return result;
}

char* padleft(char *source, char *fill, int length) //Porquê char *fill e não char fill ?
{
    int ichr = (int) fill[0];

    size_t slen = strlen(source);

    char *left = malloc(length - slen);
    memset(left, ichr, length - slen);
    *(left + length - slen) = 0;

    //char* result = malloc(length);
    char* result = calloc(length + 1, sizeof(char));
    sprintf(result, "%s%s", left, source);

    //free(left); //todo isto dá erro ou nao ?!?!?!?

    #ifdef DEBUG
        printf("function 'padleft' result:[%s]\n", result);
    #endif

    return result;
}

char* strtrim(char *source)
{
    char *result = strrtrim(strltrim(source));

    #ifdef DEBUG
        printf("function 'strtrim' result:[%s]\n", result);
    #endif

    return result;
}

char* strltrim(char *source)
{
    while(isspace(*source))
       source++;

    size_t slen = strlen(source);
    char *result = calloc(slen + 1, sizeof(char));
    //char *result = malloc(slen);
    //memset(result, 0, slen);
    strcpy(result, source);

    #ifdef DEBUG
        printf("function 'strltrim' result:[%s]\n", result);
    #endif

    return result;
}

char* strrtrim(char *source)
{
    char *back = (source + strlen(source) - 1);

    while(isspace(*back))
        back--;

    int len = back - source + 1;
    char *result = calloc(len + 1, sizeof(char));
    //char *result = malloc(len);
    //memset(result, 0, len);
    strncpy(result, source, len);
    *(result + len)= 0;  //NULL

    #ifdef DEBUG
        printf("function 'strrtrim' result:[%s]\n", result);
    #endif

    return result;
}

char* strupper(char *source)
{
    size_t slen = strlen(source);
    char *result = calloc(slen + 1, sizeof(char));

    for(int i=0; i < slen; i++)
    {
        if(source[i] >= 'a' && source[i] <= 'z')
            result[i] = source[i] - 32;
        else
            result[i] = source[i];
    }

    return result;
}
