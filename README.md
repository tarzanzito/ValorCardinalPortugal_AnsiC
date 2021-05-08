# ValorCardinalPortugal_AnsiC

IDE used: CodeBlocks
https://www.codeblocks.org/
https://www.codeblocks.org/downloads/binaries/
codeblocks-20.03mingw-nosetup.zip

--------------------------------

- calloc  coloca os bytes a zero
char *result = calloc(CARDINAL_GRUPOS_PRASE_MAX, sizeof(char));

VS

char *result = malloc(CARDINAL_GRUPOS_PRASE_MAX);
memset(result, 0, CARDINAL_GRUPOS_PRASE_MAX); //coloca os bytes a zero


--------------------------------

struct grupoCDU
{
    int size;
    char* array[GRUPO_CDU_ARRAY_MAX];
};

struct GrupoCDU* resultadogrp = DivideEmGruposDeMil("123456789012345");


struct grupoCDU *grupoCDU;
//grupoCDU = (struct grupoCDU*) malloc(1 * sizeof(struct grupoCDU)); //malloc
grupoCDU = calloc(1, sizeof(struct grupoCDU)); //malloc

--------------------------------

struct GrupoCDU* DivideEmGruposDeMil(char *valor)
{
    //salva
    struct GrupoCDU* grupo;
    grupo = (struct GrupoCDU*) malloc(1 * sizeof(struct GrupoCDU));

    return grupo;
}

--------------------------------zzxxy
