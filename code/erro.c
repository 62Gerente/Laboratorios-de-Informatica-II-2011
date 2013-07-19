#include <stdio.h>
#include "erro.h"

typedef struct erro
{
  char *err_code;
  char *mensagem;
} ERRO;

static ERRO erro[] =
{
  {"E_NOERR",	"Tudo normal"},
  {"E_COMANDO",	"Comando nao existe"},
  {"E_ARGS",	"Erro de argumentos a mais ou a menos"},
  {"E_NO_DIM",	"A area ainda nao foi inicializada"},
  {"E_DIM",		"Erro de dimensoes"},
  {"E_NAO_EXISTE",	"Nao existe"},
  {"E_JA_EXISTE",	"Ja existe"},
  {"E_COL",		"Rectangulo nao colocado"},
  {"E_ROD",		"Rectangulo nao pode rodar"},
  {"E_FORA",	"Colocado fora"},
  {"E_SOBREP",	"Rectangulo sobreposto a outro"},
  {"E_INVARGS",	"Argumentos invalidos"},
  {"E_RESTR",	"Violacao de restricoes"},
  {"E_NOSOL",	"Nao ha solucao"}
};

/**
 * Reporta o erro escrevendo uma mensagem no standard error
 * @param erro_num O nmero do erro que vem da tabela de erros. Usar SEMPRE o define e no o valor numrico para maior legibilidade.
 */
int mensagem_de_erro(int erro_num)
{
  (void) fprintf(stderr, "%s: %s\n",
    erro[erro_num].err_code, erro[erro_num].mensagem);
  return erro_num;
}
