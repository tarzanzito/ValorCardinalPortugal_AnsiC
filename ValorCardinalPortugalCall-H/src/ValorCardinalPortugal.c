
#include "ValorCardinalPortugal.h"
#include "UtilFunctions.h"

/* constants */

//length of char array = max length worlds + 1 (\0)
const char CARDINAL_UNIDADES[CARDINAL_MAX][8] = { "", "um", "dois", "três", "quatro", "cinco", "seis", "sete", "oito", "nove" };
const char CARDINAL_DEZENAS[CARDINAL_MAX][10] = { "", "dez", "vinte", "trinta", "quarenta", "cinquenta", "sessenta", "setenta", "oitenta", "noventa" };
const char CARDINAL_DEZENAS_DEZ[CARDINAL_MAX][10] = { "dez", "onze", "doze", "treze", "catorze", "quinze", "desasseis", "desassete", "dezoito", "dezanove" };
const char CARDINAL_CENTENAS[CARDINAL_MAX][15] = { "", "cento", "duzentos", "trezentos", "quatrocentos", "quinhentos", "seiscentos", "setecentos", "oitocentos", "novecentos" };
const char CARDINAL_ZERO[5] = "zero";
const char CARDINAL_UM[3] = "um";
const char CARDINAL_UMA[4] = "uma";
const char CARDINAL_DOIS[5] = "dois";
const char CARDINAL_DUAS[5] = "duas";
const char CARDINAL_CEM[4] = "cem";

const char CARDINAL_GRUPOS_PLURAL[CARDINAL_GRUPOS_MAX][64] = { "", "mil", "milhões", "milhares de milhão", "biliões",
                                                               "dezenas de bilião", "centenas de bilião", "milhares de bilião", "dezenas de milhar de bilião",
                                                               "centenas de milhar de bilião", "triliões", "undifined"
                                                             };
const char CARDINAL_GRUPOS_SINGULAR[CARDINAL_GRUPOS_MAX][64] = { "", "mil", "milhão", "milhar de milhão", "bilião",
                                                                 "dezena de bilião", "centena de bilião", "milhar de bilião", "dezena de milhar de bilião",
                                                                 "centena de milhar de bilião", "trilião", "undified"
                                                               };
const char CARDINAL_GRUPOS_MASCULINO[CARDINAL_GRUPOS_MAX][2] = { "T", "T", "T", "T", "T", "F", "F", "T", "F", "F", "T", "T" };

const char FRASE_SUFIXO_AO[3] = "ão";
const char FRASE_SUFIXO_OES[4] = "ões";
const char FRASE_E[FRASE_E_MAX] = " e ";
const char FRASE_VIRGULA[3] = ", ";
const char FRASE_DE[4] = " de";
const char FRASE_NOME_INTEIROS_P[6] = "euros";
const char FRASE_NOME_INTEIROS_S[5] = "euro";
const char FRASE_NOME_DECIMAIS_P[9] = "centimos";
const char FRASE_NOME_DECIMAIS_S[8] = "centimo";
const char FRASE_MENOS[7] = "menos ";
const char FRASE_TRUE[2] = "T";
const char FRASE_ESPACO[2] = " ";

/* ************** */
/* Implementation */
/* ************** */
char* converte(char *valor, bool vazioSeZeroParteinteira, bool vazioSeZeroParteDecimail)
{
    char *valorTrim = strtrim(valor);

    // Valida impute
    if (!validaValor(valorTrim))
        return *"ERRO: não é um valor valido: " + valor;

    char *valorForm = formataValor(valorTrim);

    // se negativo remove "-" do valor
    bool negativo = valorNegativo(valorForm);

    char *valorInicial;
    if (negativo)
        valorInicial = substring(valorForm, 1, strlen(valorForm));
    else
        valorInicial = strcopy(valorForm);

    // free //
    //XFREE free(valorTrim);
    //XFREE free(valorForm);

    //Inicia Processo

    //divide parte inteira e decimal
    struct partes *partes = divideEmPartesInteiraDecimal(valorInicial);

    // separa por grupos de mil "???"
    struct grupoCDU *gruposInteiros = divideEmGruposDeMil(partes->array[0]);
    struct grupoCDU *gruposDecimais = divideEmGruposDeMil(partes->array[1]);

    // descodifica os grupos inteiros
    int lenGrpInt = gruposInteiros->size;
    char *gruposCardinaisInteiros[lenGrpInt]; //MAX !!!!
    for (int x = 0; x < lenGrpInt; x++)
        gruposCardinaisInteiros[x] = descodificaCardinal(gruposInteiros->array[x], (lenGrpInt - x - 1));

    // descodifica os groupos decimais
    int lenGrpDec = gruposDecimais->size;
    char *gruposCardinaisDecimais[lenGrpDec];
    for (int x = 0; x < lenGrpDec; x++)
        gruposCardinaisDecimais[x] = descodificaCardinal(gruposDecimais->array[x], (lenGrpDec - x - 1));

    // junta todos os grupos
    char *finalInteiros = juntaTodosGruposDeMil(gruposCardinaisInteiros, lenGrpInt, vazioSeZeroParteinteira);
    char *finalDecimais = juntaTodosGruposDeMil(gruposCardinaisDecimais, lenGrpDec, vazioSeZeroParteDecimail);

    // caso: se valor = 0.0 mostra sempre "zero"
    if ((strlen(finalInteiros) == 0) && (strlen(finalDecimais) == 0))
    {
        strcpy(finalInteiros, CARDINAL_ZERO);
        strcat(finalInteiros, FRASE_ESPACO);
        strcat(finalInteiros, FRASE_NOME_INTEIROS_P);
    }

    // caso: analiza se coloca "de" antes do qualificador
    if (strlen(finalInteiros) > strlen(FRASE_DE))
    {
        char *temp1 = substring(finalInteiros,(strlen(finalInteiros) - 3), strlen(finalInteiros));
        if (strcmp(temp1, FRASE_SUFIXO_OES) == 0)
        {
            strcat(finalInteiros, FRASE_DE);
        }
        else
        {
            char *temp2 = substring(finalInteiros,(strlen(finalInteiros) - 2), strlen(finalInteiros));
            if (strcmp(temp2, FRASE_SUFIXO_AO) == 0)
            {
                strcat(finalInteiros, FRASE_DE);
                //XFREE free(temp2);
            }
        }
        //XFREE free(temp1);
    }

    // obtem qualificadores
    char *qualificadorInteiros = obtemQualificadorParteInteira(partes->array[0], vazioSeZeroParteinteira);
    char *qualificadoreDecimais = obtemQualificadorParteDecimal(partes->array[1], vazioSeZeroParteDecimail);

    // caso: adiciona qualificador inteiros
    if (strlen(finalInteiros) > 0)
    {
        strcat(finalInteiros, FRASE_ESPACO);
        strcat(finalInteiros, qualificadorInteiros);
    }

    // caso: adiciona qualificador decimais
    if (strlen(finalDecimais) > 0)
    {
        strcat(finalDecimais, FRASE_ESPACO);
        strcat(finalDecimais, qualificadoreDecimais);
    }
//    if ((strlen(finalDecimais) > 0) && (strlen(finalInteiros) > 0))
//        strcat(finalDecimais, FRASE_ESPACO);
//
//    strcat(finalDecimais, qualificadoreDecimais);


    // case: adiciona " e " entre a frase inteiros & frase decimais
    char *dual = calloc(FRASE_E_MAX, sizeof(char));
    //char* dual = malloc(size);
    //memset(dual, 0, size);

    if ((strlen(finalInteiros) > 0) && (strlen(finalDecimais) > 0))
        strcpy(dual, FRASE_E);

    char *resultado = calloc(RESULTADO_FINAL_SIZE, sizeof(char));
    //char* resultado = malloc(RESULTADO_FINAL_SIZE);
    //memset(resultado, 0, RESULTADO_FINAL_SIZE);

    if (negativo)
        strcpy(resultado, FRASE_MENOS);
    else
        strcpy(resultado, "");

    strcat(resultado, finalInteiros);
    strcat(resultado, dual);
    strcat(resultado, finalDecimais);


    // free //
//XFREE
//    free(partes->array[0]);
//    free(partes[1]->array[1]);
//    free(partes);
//
//    for (int x=0; x < lenGrpInt; x++)
//        free(gruposInteiros->array[x]);
//    free(gruposInteiros);
//
//    for (int x=0; x < lenGrpDec; x++)
//        free(gruposDecimais->array[x]);
//    free(gruposDecimais);
//
//
//    for (int x = 0; x < lenGrpInt; x++)
//        free(gruposCardinaisInteiros[x]);
//
//    for (int x = 0; x < lenGrpDec; x++)
//        free(gruposCardinaisDecimais[x]);
//
//    free(finalInteiros);
//    free(finalDecimais);
//
//    free(qualificadorInteiros);
//    free(qualificadoreDecimais);
//
//    free(dual);

    return resultado;
}

struct partes* divideEmPartesInteiraDecimal(char *valor)
{
    #ifdef DEBUG
        printf("function 'DivideEmPartesInteiraDecimal' init\n");
    #endif

    //char *valorForm = FormataValor(valor);
    int pos = indexof(valor, ".");
    size_t len = strlen(valor);

    struct partes *partes;
    //partes = (struct Partes*) malloc(1 * sizeof(struct Partes)); //malloc
    partes = calloc(1, sizeof(struct partes)); //malloc

    //size_t size = strlen(valor);
    //partes->array[0] = calloc(pos, sizeof(char));
    partes->array[0] = calloc(pos + 1, sizeof(char));
    //partes->array[0] = malloc(pos);
    //memset(partes->array[0], 0, pos);

    //partes->array[1] = calloc(len - pos - 1, sizeof(char));
    partes->array[1] = calloc(len - pos, sizeof(char));
    //partes->array[1] = malloc(len - pos - 1);
    //memset(partes->array[1], 0, len - pos - 1);

    //parte esquerda e direita do "."
    partes->array[0] = substring(valor, 0, pos);
    partes->array[1] = substring(valor, pos + 1, len);

    #ifdef DEBUG
        printf("function 'DivideEmPartesInteiraDecimal' result[L]:[%s]\n", partes->array[0]);
        printf("function 'DivideEmPartesInteiraDecimal' result[R]:[%s]\n", partes->array[1]);
    #endif

    return partes;
}

struct grupoCDU* divideEmGruposDeMil(char *valor)
{
    #ifdef DEBUG
        printf("function 'divideEmGruposDeMil' init\n");
    #endif

    char *valor1 = valor;

    char *listf[GRUPO_CDU_ARRAY_MAX];

    //clear arrays
    for (int i = 0; i < GRUPO_CDU_ARRAY_MAX; i++)
        listf[i] = '\0';

    //calc length
    size_t len = strlen(valor1);
    int grp = len / 3;
    int rest = len  - (grp * 3);
    if (rest > 0)
        grp++;

    // extrai
    char *str3;
    int pos = 0;
    while (len > 3)
    {
        str3 = substring(valor1, strlen(valor1) - 3, strlen(valor1));
        listf[pos++] = str3;
        valor1 = substring(valor, 0, strlen(valor1) - 3);
        len = strlen(valor1);
    }

    str3 = padleft(valor1, "0", 3); // garante comprimento = 3
    listf[pos] = str3;

    //salva
    struct grupoCDU *grupo;
    grupo = (struct grupoCDU*) malloc(1 * sizeof(struct grupoCDU));

    //clear arrays
    for (int i = 0; i < GRUPO_CDU_ARRAY_MAX; i++) //aqui malloc + memset   -> nao parece ser preciso
        grupo->array[i] = '\0';

    // reverte array
    for (int x = 0; x < grp; x++)
        grupo->array[grp - 1 - x] = listf[x];

    grupo->size = grp;

    #ifdef DEBUG
        printf("function 'DivideEmGruposDeMil' result:[%d]\n", grupo->size);
    #endif

    return grupo;
}

char* juntaTodosGruposDeMil(char *grouposEmCardinal[], int length, bool vazioSeZero)
{
    #ifdef DEBUG
        printf("function 'juntaTodosGruposDeMil' init\n");
    #endif

    char *result = calloc(RESULTADO_GRUPO_SIZE, sizeof(char));
    //char* result = malloc(RESULTADO_GRUPO_SIZE);
    //memset(result, 0, RESULTADO_GRUPO_SIZE);

    for (int x = 0; x < length; x++)
    {
        if (strlen(grouposEmCardinal[x]) == 0)
            continue;

        // no ultimo elemento analisa se coloca  " e " no fim
        if ((x == length-1) && (strlen(result) > 1))
        {

            int pos = indexof(grouposEmCardinal[x], FRASE_E);
            if (pos == -1)
            {
                result = removeUltimasVirgulasEmExcesso(result);
                strcat(result, FRASE_E);
            }
        }

        strcat(result, grouposEmCardinal[x]);
        strcat(result, FRASE_VIRGULA);
    }

    //verifica em caso de vazio se coloca "zero"
    if ((strlen(result) == 0) && (!vazioSeZero))
        strcpy(result, CARDINAL_ZERO);

    result = removeUltimasVirgulasEmExcesso(result);


    //caso: quantos " e " existem depois da ultima virgula? se zero substitui ultima ", " por " e "
    int pos = lastindexof(result, FRASE_VIRGULA);
    if (pos > 0)
    {
        char *temp1 = substring(result, 0, pos);
        char *temp2 = substring(result, pos + strlen(FRASE_VIRGULA), strlen(result));
        pos = indexof(temp2, FRASE_E);
        if (pos == -1)
        {
            strcpy(result, temp1);
            strcat(result, FRASE_E);
            strcat(result, temp2);
            //result = temp1 + FRASE_E + temp2;
        }
    }

    #ifdef DEBUG
        printf("function 'JuntaTodosGruposDeMil' result:[%s]\n", result);
    #endif

    return result;
}

char* removeUltimasVirgulasEmExcesso(char *valor)
{
    #ifdef DEBUG
        printf("function 'removeUltimasVirgulasEmExcesso' init\n");
    #endif

    char *result = valor;
    size_t tlen;
    size_t vlen = strlen(FRASE_VIRGULA);

    while(true)
    {
        tlen = strlen(result);
        if (tlen < vlen)
            break;

        char *temp = substring(result, tlen - vlen, tlen);
        int cp = strcmp(temp, FRASE_VIRGULA);

        if (cp == 0)
            result = substring(result, 0, tlen - vlen);
        else
            break;
    }

    #ifdef DEBUG
        printf("function 'RemoveUltimasVirgulasEmExcesso' result:[%s]\n", result);
    #endif

    return result;
}

char* descodificaCardinal(char *valor, int nivel)
{
    #ifdef DEBUG
        printf("function 'descodificaCardinal' init\n");
    #endif

    char *result;

    int cmp = strcmp(valor, "000");
    if (cmp == 0)
    {
        int len = 2;
        result = calloc(len, sizeof(char));  //TODO : porquê 2
        //result = malloc(size);  //TODO : porquê 2
        //memset(result, 0, size);
        strcpy(result, "");
        return result;
    }

    char *cardinalArray[] = { '\0', '\0', '\0'};
    short digitArray[]  = { 0, 0, 0}; //new byte[3];
    //char *digitArray[]  = { "\0", "\0", "\0"}; //new byte[3];

    for (int x = 0; x < 3; x++)
    {
        char *chr = substring(valor, x, x+1);
        digitArray[x] = atoi(chr);
    }

    cardinalArray[0] = obtemCentenas(digitArray[0], digitArray[1], digitArray[2]);
    cardinalArray[1] = obtemDezenas(digitArray[1], digitArray[2]);
    cardinalArray[2] = obtemUnidades(digitArray[2], digitArray[1]);

    result = juntaCentenasDezenasUnidades(cardinalArray[0], cardinalArray[1], cardinalArray[2]);

    result = adicionaSufixoDeGrupoMil(result, nivel);

    #ifdef DEBUG
        printf("function 'DescodificaCardinal' result:[%s]\n", result);
    #endif

    return result;
}

char* juntaCentenasDezenasUnidades(char *centena, char *dezena, char *unidade)
{
    #ifdef DEBUG
        printf("function 'juntaCentenasDezenasUnidades' init\n");
    #endif

    char *result = calloc(CDU_SIZE_MAX, sizeof(char));
    //char *result = malloc(CDU_SIZE_MAX);
    //memset(result, 0, CDU_SIZE_MAX);
    strcpy(result, centena);

    if ((strlen(centena) > 0) && ((strlen(dezena) > 0) || (strlen(unidade) > 0)))
        strcat(result, FRASE_E);

    strcat(result, dezena);
    if ((strlen(dezena) > 0) && (strlen(unidade) > 0))
        strcat(result, FRASE_E);

    strcat(result, unidade);

    #ifdef DEBUG
        printf("function 'JuntaCentenasDezenasUnidades' result:[%s]\n", result);
    #endif

    return result;
}

char* obtemUnidades(short digito, short dezena)
{
    #ifdef DEBUG
        printf("function 'obtemUnidades' init\n");
    #endif

    char *result = calloc(PALAVRA_UNIDADES_MAX, sizeof(char));
    //char *result = malloc(PALAVRA_UNIDADES_MAX);
    //memset(result, 0, PALAVRA_UNIDADES_MAX);

    if (dezena == 1)
        strcpy(result, "");
    else
        strcpy(result, CARDINAL_UNIDADES[digito]);

    #ifdef DEBUG
        printf("function 'ObtemUnidades' result:[%s]\n", result);
    #endif

    return result;
}

char* obtemDezenas(short digito, short unidade)
{
    #ifdef DEBUG
        printf("function 'obtemDezenas' init\n");
    #endif

    char *result = calloc(PALAVRA_DEZENAS_MAX, sizeof(char));
    //char *result = malloc(PALAVRA_DEZENAS_MAX);
    //memset(result, 0, PALAVRA_DEZENAS_MAX);

    if (digito == 1)
        strcpy(result, CARDINAL_DEZENAS_DEZ[unidade]);
    else
        strcpy(result, CARDINAL_DEZENAS[digito]);

    #ifdef DEBUG
        printf("function 'ObtemDezenas' result:[%s]\n", result);
    #endif

    return result;
}

char* obtemCentenas(short digito, short dezena, short unidade)
{
    #ifdef DEBUG
        printf("function 'obtemCentenas' init\n");
    #endif

    char *result = calloc(PALAVRA_CENTENAS_MAX, sizeof(char));
    //char *result = malloc(PALAVRA_CENTENAS_MAX);
    //memset(result, 0, PALAVRA_CENTENAS_MAX);

    if ((digito == 1) && (dezena == 0) && (unidade == 0))
        strcpy(result, CARDINAL_CEM); // Caso : Cem
    else
        strcpy(result, CARDINAL_CENTENAS[digito]);

    #ifdef DEBUG
        printf("function 'ObtemCentenas' result:[%s]\n", result);
    #endif

    return result;
}

char* obtemQualificadorParteInteira(char *valor, bool vazioSeZero)
{
    #ifdef DEBUG
        printf("function 'obtemQualificadorParteInteira' init\n");
    #endif

    char *result = calloc(QUALIFICADOR_INTEIRO_MAX, sizeof(char));
    //char *result = malloc(QUALIFICADOR_INTEIRO_MAX);
    //memset(result, 0, QUALIFICADOR_INTEIRO_MAX);

    double valTemp = strtod (valor, '\0');

    if (valTemp > 1)
        strcpy(result, FRASE_NOME_INTEIROS_P);
    else
        if (valTemp == 1)
            strcpy(result, FRASE_NOME_INTEIROS_S);
        else
            if ((valTemp == 0) && (!vazioSeZero))
                strcpy(result, FRASE_NOME_INTEIROS_P);
            else
                strcpy(result, "");

    #ifdef DEBUG
        printf("function 'ObtemQualificadorParteInteira' result:[%s]\n", result);
    #endif

    return result;
}

char* obtemQualificadorParteDecimal(char* valor, bool vazioSeZero)
{
    #ifdef DEBUG
        printf("function 'obtemQualificadorParteDecimal' init\n");
    #endif

    char *result = calloc(QUALIFICADOR_DECIMAL_MAX, sizeof(char));
    //char *result = malloc(QUALIFICADOR_DECIMAL_MAX);
    //memset(result, 0, QUALIFICADOR_DECIMAL_MAX);

    double valTemp = strtod (valor, '\0');

    if (valTemp > 1)
        strcpy(result, FRASE_NOME_DECIMAIS_P);
    else
        if (valTemp == 1)
            strcpy(result, FRASE_NOME_DECIMAIS_S);
        else
            if ((valTemp == 0) && (!vazioSeZero))
                strcpy(result, FRASE_NOME_DECIMAIS_P);
            else
                strcpy(result, "");

    #ifdef DEBUG
        printf("function 'ObtemQualificadorParteDecimal' result:[%s]\n", result);
    #endif

    return result;
}

char* adicionaSufixoDeGrupoMil(char *valor, int nivel)
{
    #ifdef DEBUG
        printf("function 'adicionaSufixoDeGrupoMil' init\n");
    #endif

    char *result = calloc(CARDINAL_GRUPOS_PRASE_MAX, sizeof(char));
    //char *result = malloc(CARDINAL_GRUPOS_PRASE_MAX);
    //memset(result, 0, CARDINAL_GRUPOS_PRASE_MAX);

    int isUm = strcmp(valor, CARDINAL_UM);
    int isMasc;

    switch (nivel)
    {

    case 0:
        strcpy(result, valor);
        break;

    case 1:

        if (isUm == 0)
            strcpy(result, CARDINAL_GRUPOS_SINGULAR[nivel]); // special : remove palavra "um" (um mil)
        else
        {
            strcpy(result, valor);
            strcat(result, FRASE_ESPACO);
            strcat(result, CARDINAL_GRUPOS_PLURAL[nivel]);
        }
        break;

    default:

        isMasc = strcmp(CARDINAL_GRUPOS_MASCULINO[nivel], FRASE_TRUE);

        if (isUm == 0)
        {
            if (isMasc == 0)
                strcpy(result, CARDINAL_UM);
            else
                strcpy(result, CARDINAL_UMA);
                //strcat(result, CARDINAL_UMA);

            strcat(result, FRASE_ESPACO);
            strcat(result, CARDINAL_GRUPOS_SINGULAR[nivel]);
        }
        else
        {
            int isDois = strcmp(valor, CARDINAL_DOIS);
            if (isDois == 0)
            {
                if (isMasc == 0)
                   strcpy(result, CARDINAL_DOIS);
                else
                   strcpy(result, CARDINAL_DUAS);

                strcat(result, FRASE_ESPACO);
                strcat(result, CARDINAL_GRUPOS_PLURAL[nivel]);
            }
            else
            {
                strcpy(result, valor);
                strcat(result, FRASE_ESPACO);
                strcat(result, CARDINAL_GRUPOS_PLURAL[nivel]);
            }
        }
        break;

    }

    #ifdef DEBUG
        printf("function 'AdicionaSufixoDeGrupoMil' result:[%s]\n", result);
    #endif

    return result;
}

/* Pre-processo */

bool validaValor(char *valor)
{
    #ifdef DEBUG
        printf("function 'validaValor' init\n");
    #endif

    int len = strlen(valor);

    if (len == 0)
        return true;

    //only numbers, - at first position, only only .
    int pontos = 0;
    for (int x = 0; x < len; x++)
    {
        char chr = valor[x];

        if (chr == '-')
        {
            if (x > 0)
                return false;
            else
                continue;
        }

        if (chr == '.')
        {
            pontos++;
            continue;
        }

        if (chr < 48 || chr > 57)
            return false;
    }
    if (pontos > 1)
        return false;

    return true;
}

char* formataValor(char *valor)
{
    #ifdef DEBUG
        printf("function 'validaValor' init\n");
    #endif

    size_t len = strlen(valor);

    char *resultado;

    if (len == 0)  //empty
    {
        resultado = calloc(5, sizeof(char));
        //resultado = (char *) malloc(len);
        //memset(resultado, 0, len);
        strcpy(resultado, "0.00");
        return resultado;
    }

    int pos = indexof(valor, ".");
    if (pos == -1) // don't have "."
    {
        //len = len + 3;
        resultado = calloc(len + 4, sizeof(char));
        //resultado = (char *) malloc(len);
        //memset(resultado, 0, len);
        strcpy(resultado, valor);
        strcat(resultado, ".00");
        return resultado;
    }
    else
        if (pos == 0) // "." in first position
        {
            //len = len + 1;
            resultado = calloc(len + 2, sizeof(char));
            //resultado = (char *) malloc(len);
            //memset(resultado, 0, len);
            strcpy(resultado, "0");
            strcat(resultado, valor);
        }
        else
        {
            resultado = calloc(len + 1, sizeof(char));
            //resultado = (char *) malloc(len);
            //memset(resultado, 0, len);
            strcpy(resultado, valor);
        }

    char *resultado2;
    pos = indexof(resultado, ".");
    len = strlen(resultado);
    int rlen = len - pos;
    if (rlen == 1)
    {
        resultado2 = calloc(len + 3, sizeof(char));
        //resultado2 = malloc(len);
        //memset(resultado2, 0, len);
        strcpy(resultado2, resultado);
        strcat(resultado2, "00");
        //XFREE free(resultado);
        return resultado2;
    }
    else
        if (rlen == 2)
        {
            resultado2 = calloc(len + 2, sizeof(char));
            //resultado2 = malloc(len);
            //memset(resultado2, 0, len);
            strcpy(resultado2, resultado);
            strcat(resultado2, "0");
            //XFREE free(resultado);
            return resultado2;
        }
        else
            return substring(resultado, 0, pos + 3);
}

bool valorNegativo(char *valor)
{
    char *result = substring(valor, 0, 1);
    int cmp = strcmp(result, "-");
    //XFREE free(result);

    return (cmp == 0);
}
