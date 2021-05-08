#ifndef VALORCARDINALPORTUGALCALL_H_INCLUDED
#define VALORCARDINALPORTUGALCALL_H_INCLUDED

#include <stdbool.h>

/* macros */

#define GRUPO_CDU_ARRAY_MAX 32
#define CARDINAL_MAX 10
#define CARDINAL_GRUPOS_MAX 12
#define RESULTADO_FINAL_SIZE 8192
#define VALOR_SIZE_MAX 96
#define RESULTADO_GRUPO_SIZE 4096
#define CDU_SIZE_MAX 32
#define PALAVRA_UNIDADES_MAX 12
#define PALAVRA_DEZENAS_MAX 12
#define PALAVRA_CENTENAS_MAX 13
#define QUALIFICADOR_INTEIRO_MAX 6
#define QUALIFICADOR_DECIMAL_MAX 10
#define CARDINAL_GRUPOS_PRASE_MAX 128
#define FRASE_E_MAX 4

/* declare structs */

/*para -> Centena, Dezena, Unidade */
struct grupoCDU
{
    int size;
    char* array[GRUPO_CDU_ARRAY_MAX];
};

typedef struct grupoCDU GrupoCDU;

/* para -> parte esquerda e direita do ponto */
struct partes
{
    char* array[2];
};

typedef struct partes Partes;


/* declare functions */

char* converte(char* valor, bool vazioSeZeroParteinteira, bool vazioSeZeroParteDecimal);

bool validaValor(char *valor);
char* formataValor(char *valor);
bool valorNegativo(char *valor);

struct partes* divideEmPartesInteiraDecimal(char *valor);
struct grupoCDU* divideEmGruposDeMil(char *valor);
char* juntaTodosGruposDeMil(char *grouposEmCardinal[], int length, bool vazioSeZero);
char* removeUltimasVirgulasEmExcesso(char *valor);
char* descodificaCardinal(char *valor, int nivel);
char* juntaCentenasDezenasUnidades(char *centena, char *dezena, char *unidade);

char* obtemUnidades(short digito, short dezena);
char* obtemDezenas(short digito, short unidade);
char* obtemCentenas(short digito, short dezena, short unidade);

char* obtemQualificadorParteInteira(char *valor, bool vazioSeZero);
char* obtemQualificadorParteDecimal(char *valor, bool vazioSeZero);
char* adicionaSufixoDeGrupoMil(char *valor, int nivel);

#endif // VALORCARDINALPORTUGALCALL_H_INCLUDED
