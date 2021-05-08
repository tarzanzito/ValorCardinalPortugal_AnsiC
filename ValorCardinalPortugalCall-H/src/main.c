
#include "UtilFunctions.h"
#include "Tests.h"
#include "ValorCardinalPortugal.h"

#include <stdio.h>
#include <string.h>

/* -------------------------------------------------------------------------------- */
/* os ficheiros sources devem ser gravados em ASCII. UTF-8 gera erro nas strcmp etc */
/* -------------------------------------------------------------------------------- */

/* FALTA REVER os FREE em debug pára porquê? */

/* macros */

#define VERSION "1.0.9"
#define TEST

int main(int argc, char *argv[])
{
    #ifdef TEST
        tests();
        getchar();
        return 0;
    #endif

    bool vazioSeZeroParteinteira = false;
    bool vazioSeZeroParteDecimal = false;

    if (argc >= 3)
        vazioSeZeroParteinteira = (strcmp(strupper(argv[2]), "TRUE") == 0);

    if (argc >= 4)
        vazioSeZeroParteDecimal = strcmp(strupper(argv[3]), "TRUE") == 0;

    if (argc >= 2) {
        char *result = converte(argv[1], vazioSeZeroParteinteira, vazioSeZeroParteDecimal);
        printf("\n[%s]\n", result);
        return 0;
    }

    printf("\n");
    printf("ValorCardinalPortugal (Version: %s)\n", VERSION);
    printf("======================================\n");
    printf("\n");

    char str[255];
    printf("Introduza valor '#0.00': ");
    scanf("%s", str);

    printf("\nProcessa :[%s]\n", str);

    char *valor = str;
    //char *valor = &str;

    char *result = converte(valor, vazioSeZeroParteinteira, vazioSeZeroParteDecimal);
    printf("\nResultado:[%s]\n", result);

    printf("\nEnter\n");
    getchar();

    return 0;
}
