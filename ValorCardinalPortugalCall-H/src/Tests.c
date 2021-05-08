
#include "Tests.h"
#include "UtilFunctions.h"
#include "ValorCardinalPortugal.h"

void tests(void)
{
    printf("Tests Begin...\n\n");

    test_strcopy();
    test_substring();
    test_substring2();
    test_indexof();
    test_lastindexof();
    test_leftpad();
    test_strltrim();
    test_strrtrim();
	test_strtrim();
	test_strupper();

    test_validaValor();
    test_formataValor();
    test_valorNegativo();

    test_adicionaSufixoDeGrupoMil();
    test_obtemQualificadorParteDecimal();
    test_obtemQualificadorParteInteira();
    test_obtemCentenas();
    test_obtemDezenas();
    test_obtemUnidades();
    test_juntaCentenasDezenasUnidades();
    test_descodificaCardinal();
    test_removeUltimasVirgulasEmExcesso();
    test_juntaTodosGruposDeMil();
    test_divideEmGruposDeMil();
    test_divideEmPartesInteiraDecimal();
    test_converte();

    printf("\nTests End...\n\n");
}

void test_strcopy(void)
{
    printf("testing function: strcopy\n");
    char *input = "AABBCCDDEEFF";
    char *output = strcopy(input);
    if (strcmp(output, "AABBCCDDEEFF") != 0)
        printf("ERROR testing function: strcopy (0)\n");
}

void test_leftpad(void)
 {
    printf("testing function: leftpad\n");
    char *input = "123";
    char *output = padleft(input, "A", 10);
    if (strcmp(output, "AAAAAAA123") != 0)
        printf("ERROR testing function: leftpad (0)\n");

    char *output1 = padleft(input, "A", 3);
    if (strcmp(output1, "123") != 0)
        printf("ERROR testing function: leftpad (1)\n");
}

void test_substring(void)
{
    printf("testing function: substring\n");
    char *input = "123456789";
    char *output = substring(input, 5, 7);
    if (strcmp(output, "67") != 0)
        printf("ERROR testing function: substring\n");
}

void test_substring2(void)
{
    printf("testing function: substring2\n");
    char *input = "123456789";
    char *output = substring2(input, 5, 2);
    if (strcmp(output, "67") != 0)
        printf("ERROR testing function: substring2\n");
}

void test_indexof(void)
{
    printf("testing function: indexof\n");
    int pos = indexof("alfabetadeltabetazulu", "beta");
    if (pos != 4)
        printf("ERROR testing function: indexof\n");
}

void test_lastindexof(void)
{
    printf("testing function: lastindexof\n");
    int pos = lastindexof("alfabetadeltabetazulu", "beta");
    if (pos != 13)
        printf("ERROR testing function: lastindexof\n");
}

void test_strltrim(void)
{
    printf("testing function: strltrim\n");
    char *output = strltrim("   alfabetazulu");
    if (strcmp(output, "alfabetazulu") != 0)
        printf("ERROR testing function: strltrim (0)\n");

    char *output1 = strltrim("");
    if (strcmp(output1, "") != 0)
        printf("ERROR testing function: strltrim (1)\n");

    char *output2 = strltrim("   ");
    if (strcmp(output2, "") != 0)
        printf("ERROR testing function: strltrim (2)\n");
}

void test_strrtrim(void)
{
    printf("testing function: strrtrim\n");
    char *output = strrtrim("alfabetazulu   ");
    if (strcmp(output, "alfabetazulu") != 0)
        printf("ERROR testing function: strrtrim (0)\n");

    char *output1 = strrtrim("");
    if (strcmp(output1, "") != 0)
        printf("ERROR testing function: strrtrim (1)\n");

    char *output2 = strrtrim("   ");
    if (strcmp(output2, "") != 0)
        printf("ERROR testing function: strrtrim (2)\n");
}

void test_strtrim(void)
{
    printf("testing function: strtrim\n");
    char *output = strtrim("   alfabetazulu   ");
    if (strcmp(output, "alfabetazulu") != 0)
        printf("ERROR testing function: strtrim (0)\n");

    char *output1 = strtrim("");
    if (strcmp(output1, "") != 0)
        printf("ERROR testing function: strtrim (1)\n");

    char *output2 = strtrim("   ");
    if (strcmp(output2, "") != 0)
        printf("ERROR testing function: strtrim (2)\n");
}

void test_strupper(void)
{
    printf("testing function: strupper\n");
    char *output = strupper("true_123");
    if (strcmp(output, "TRUE_123") != 0)
        printf("ERROR testing function: strupper\n");
}

void test_validaValor(void)
{
    printf("testing function: validaValor\n");
    bool ok = validaValor("123456.89");
    if (!ok)
        printf("ERROR testing function: validaValor (0)\n");

    ok = validaValor("123.456.89");
    if (ok)
        printf("ERROR testing function: validaValor (1)\n");
}

void test_formataValor(void)
{
    printf("testing function: formataValor\n");
    //char *valor101 = "123.89";
    char *output = formataValor("123.89");
    if (strcmp(output, "123.89") != 0)
        printf("ERROR testing function: formataValor (0)\n");

    char *output1 = formataValor("123.8");
    if (strcmp(output1, "123.80") != 0)
        printf("ERROR testing function: formataValor (1)\n");

    char *output2 = formataValor("123.");
    if (strcmp(output2, "123.00") != 0)
        printf("ERROR testing function: formataValor (2)\n");

    char *output3 = formataValor(".");
    if (strcmp(output3, "0.00") != 0)
        printf("ERROR testing function: formataValor (3)\n");

    char *output4 = formataValor("0.");
    if (strcmp(output4, "0.00") != 0)
        printf("ERROR testing function: formataValor (4)\n");

    char *output5 = formataValor("");
    if (strcmp(output5, "0.00") != 0)
        printf("ERROR testing function: formataValor (5)\n");

    char *output6 = formataValor("123");
    if (strcmp(output6, "123.00") != 0)
        printf("ERROR testing function: formataValor (6)\n");
}

void test_valorNegativo(void)
{
    printf("testing function: valorNegativo\n");
    bool negativo = valorNegativo("-123456.89");
    if (!negativo)
        printf("ERROR testing function: valorNegativo (1)\n");

    negativo = valorNegativo("123456.89");
    if (negativo)
        printf("ERROR testing function: valorNegativo (3)\n");
}

void test_adicionaSufixoDeGrupoMil(void)
{
    printf("testing function: adicionaSufixoDeGrupoMil\n");
    char *input = "oito";
    char *output = adicionaSufixoDeGrupoMil(input, 2);
    if (strcmp(output, "oito milhões") != 0)
        printf("ERROR testing function: adicionaSufixoDeGrupoMil (0)\n");

    char *input1 = "um";
    char *output1 = adicionaSufixoDeGrupoMil(input1, 4);
    if (strcmp(output1, "um bilião") != 0)
        printf("ERROR testing function: adicionaSufixoDeGrupoMil (1)\n");

    char *output2 = adicionaSufixoDeGrupoMil(input1, 5);
    if (strcmp(output2, "uma dezena de bilião") != 0)
        printf("ERROR testing function: adicionaSufixoDeGrupoMil (2)\n");

    char *input2 = "dois";
    char *output3 = adicionaSufixoDeGrupoMil(input2, 4);
    if (strcmp(output3, "dois biliões") != 0)
        printf("ERROR testing function: adicionaSufixoDeGrupoMil (3)\n");

    char *output4 = adicionaSufixoDeGrupoMil(input2, 5);
    if (strcmp(output4, "duas dezenas de bilião") != 0)
        printf("ERROR testing function: adicionaSufixoDeGrupoMil (4)\n");
}

void test_obtemQualificadorParteDecimal(void)
{
    printf("testing function: obtemQualificadorParteDecimal\n");
    char *input = "123";
    char *output = obtemQualificadorParteDecimal(input, false);
    if (strcmp(output, "centimos") != 0)
        printf("ERROR testing function: obtemQualificadorParteDecimal\n");
}

void test_obtemQualificadorParteInteira(void)
{
    printf("testing function: obtemQualificadorParteInteira\n");
    char *input = "123";
    char *output = obtemQualificadorParteInteira(input, false);
    if (strcmp(output, "euros") != 0)
        printf("ERROR testing function: obtemQualificadorParteInteira\n");
}

void test_obtemCentenas(void)
{
    printf("testing function: obtemCentenas\n");
    char *output = obtemCentenas(2, 1, 3);
    if (strcmp(output, "duzentos") != 0)
        printf("ERROR testing function: obtemCentenas\n");
}

void test_obtemDezenas(void)
{
    printf("testing function: obtemDezenas\n");
    char *output = obtemDezenas(1, 2);
    if (strcmp(output, "doze") != 0)
        printf("ERROR testing function: obtemDezenas\n");
}

void test_obtemUnidades(void)
{
    printf("testing function: obtemUnidades\n");
    char *output = obtemUnidades(8, 2);
    if (strcmp(output, "oito") != 0)
        printf("ERROR testing function: obtemUnidades\n");
}

void test_juntaCentenasDezenasUnidades(void)
{
    printf("testing function: juntaCentenasDezenasUnidades\n");
    char *output = juntaCentenasDezenasUnidades("oitocentos", "setenta", "seis");
    if (strcmp(output, "oitocentos e setenta e seis") != 0)
        printf("ERROR testing function: juntaCentenasDezenasUnidades\n");
}

void test_descodificaCardinal(void)
{
    printf("testing function: descodificaCardinal\n");
    char *output = descodificaCardinal("123", 2);
    if (strcmp(output, "cento e vinte e três milhões") != 0)
        printf("ERROR testing function: descodificaCardinal\n");
}

void test_removeUltimasVirgulasEmExcesso(void)
{
    printf("testing function: removeUltimasVirgulasEmExcesso\n");
    char *output = removeUltimasVirgulasEmExcesso("123456789, , , ");
    if (strcmp(output, "123456789") != 0)
        printf("ERROR testing function: removeUltimasVirgulasEmExcesso\n");
}

void test_juntaTodosGruposDeMil(void)
{
    printf("testing function: juntaTodosGruposDeMil\n");
    char *phrases[] = {"alfa", "beta", "zulu"};
    char *output = juntaTodosGruposDeMil(phrases, 3, false);
    if (strcmp(output, "alfa, beta e zulu") != 0)
        printf("ERROR testing function: juntaTodosGruposDeMil (1)\n");

    printf("testing function: juntaTodosGruposDeMil\n");
    char *phrases1[] = {"alfa", "beta", ""};
    char *output1 = juntaTodosGruposDeMil(phrases1, 3, false);
    if (strcmp(output1, "alfa e beta") != 0)
        printf("ERROR testing function: juntaTodosGruposDeMil (2)\n");

}

void test_divideEmGruposDeMil(void)
{
    printf("testing function: divideEmGruposDeMil\n");
    struct grupoCDU *resultadogrp = divideEmGruposDeMil("123456789012345");
    int sizegrp = resultadogrp->size;
    if (sizegrp != 5)
        printf("ERROR testing function: divideEmGruposDeMil (n)\n");
    char *g0 = resultadogrp->array[0];
    char *g1 = resultadogrp->array[1];
    char *g2 = resultadogrp->array[2];
    char *g3 = resultadogrp->array[3];
    char *g4 = resultadogrp->array[4];
    if (strcmp(g0, "123") != 0)
        printf("ERROR testing function: divideEmGruposDeMil (0)\n");
    if (strcmp(g1, "456") != 0)
        printf("ERROR testing function: divideEmGruposDeMil (1)\n");
    if (strcmp(g2, "789") != 0)
        printf("ERROR testing function: divideEmGruposDeMil (2)\n");
    if (strcmp(g3, "012") != 0)
        printf("ERROR testing function: divideEmGruposDeMil (3)\n");
    if (strcmp(g4, "345") != 0)
        printf("ERROR testing function: divideEmGruposDeMil (4)\n");
}

void test_divideEmPartesInteiraDecimal()
{
    printf("testing function: divideEmPartesInteiraDecimal\n");
    struct partes *resultadoPrt1 = divideEmPartesInteiraDecimal("1234567.89");
    char *p10 = resultadoPrt1->array[0];
    char *p11 = resultadoPrt1->array[1];
    if (strcmp(p10, "1234567") != 0)
        printf("ERROR testing function: divideEmPartesInteiraDecimal (0)\n");
    if (strcmp(p11, "89") != 0)
        printf("ERROR testing function: divideEmPartesInteiraDecimal (1)\n");
}

void test_converte(void)
{
    printf("testing function: converte\n");
    char *input = "123456789.87";
    char *output = converte(input, false, false);
    if (strcmp(output, "cento e vinte e três milhões, quatrocentos e cinquenta e seis mil, setecentos e oitenta e nove euros e oitenta e sete centimos") != 0)
        printf("ERROR testing function: converte (0)\n");

    char *input1 = "2500000000000000.00";
    char *output1 = converte(input1, false, false);
    if (strcmp(output1, "duas dezenas de bilião e quinhentos biliões de euros e zero centimos") != 0)
        printf("ERROR testing function: converte (1)\n");
}
