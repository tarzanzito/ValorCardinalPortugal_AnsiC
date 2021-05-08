#ifndef TESTS_H_INCLUDED
#define TESTS_H_INCLUDED

/* declare functions */

void test_strcopy(void);
void test_substring(void);
void test_substring2(void);
void test_indexof(void);
void test_lastindexof(void);
void test_leftpad(void);
void test_strtrim(void);
void test_strltrim(void);
void test_strrtrim(void);
void test_strupper(void);

void test_validaValor(void);
void test_formataValor(void);
void test_valorNegativo(void);

void test_adicionaSufixoDeGrupoMil(void);
void test_obtemQualificadorParteDecimal(void);
void test_obtemQualificadorParteInteira(void);
void test_obtemCentenas(void);
void test_obtemDezenas(void);
void test_obtemUnidades(void);
void test_juntaCentenasDezenasUnidades(void);
void test_descodificaCardinal(void);
void test_removeUltimasVirgulasEmExcesso(void);
void test_juntaTodosGruposDeMil(void);
void test_divideEmGruposDeMil(void);
void test_divideEmPartesInteiraDecimal(void);
void test_converte(void);

void tests(void);

#endif // TESTS_H_INCLUDED
