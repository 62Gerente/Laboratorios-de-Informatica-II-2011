/**
 * @file Estruturas.h
 * @brief Ficheiro .h (header) do rect.c
 * @author André Santos, Helena Alves, Pedro Faria
 * @date 18 de Maio de 2011
 */

#ifndef _ESTRUTURAS
#define _ESTRUTURAS

/**
 * @struct sDIM;
 * @brief Define a dimensão da área de trabalho.
 */
typedef struct sDIM
{
/**
 * @var x;
 * @brief Largura da área da nossa área de trabalho.
 */
	int x;
/**
 * @var y;
 * @brief Comprimento da nossa área de trabalho.
 */
	int y;
/**
 * @var u;
 * @brief Verifica se a restrição 'DIM' já foi usada.
 */
	int u;
} *DIM;

/**
 * @struct sLRestr;
 * @brief Define uma lista de restrições, onde esta defenido o número da restrição e nome dos rectângulos\áreas associados.
 */
typedef struct sLRestr
{
/**
 * @var n;
 * @brief Nome da restrição, sendo que esta está codificado em número.
 */
	int n;
/**
 * @var c1;
 * @brief Nome do rectângulo.
 */
	char c1[15];
/**
 * @var c2;
 * @brief Nome do rectângulo\área.
 */
	char c2[15];
/**
 * @var sLRestr *seg;
 * @brief O apontador para a restrição seguinte.
 */
	struct sLRestr *seg;
} *LRestr,NodoRestr;

/**
 * @struct sLRect
 * @brief Define uma lista de rectângulos: o seu nome, largura, comprimento, as suas coordenadas de inicio e do respectivo fim.
 */
typedef struct sLRect
{
/**
 * @var n;
 * @brief Nome do rectângulo.
 */
	char n[15];
/**
 * @var x
 * @brief Define a largura do rectângulo no eixo do x.
 */
	int x;
/**
 * @var y
 * @brief Define a comprimento do rectângulo no eixo do y.
 */
	int y;
/**
 * @var x1;
 * @brief Indica a posição do eixo do x onde o rectangulo irá começar.
 */
	int x1;
/**
 * @var y1;
 * @brief Indica a posição do eixo do y onde o rectangulo irá começar.
 */
	int y1;
/**
 * @var x2;
 * @brief Indica a posição do eixo do x onde o rectangulo irá terminar.
 */
	int x2;
/**
 * @var y2;
 * @brief Indica a posição do eixo do y onde o rectangulo irá terminar.
 */
	int y2;
/**
 * @var r
 * @brief Indica se o rectângulo pode ser rodado ou não.
 */
	int r;
/**
 * @var c
 * @brief Indica se o rectângulo está colocado.
 */
	int c;
/**
 * @var sLRect *seg;
 * @brief O apontador para o rectângulo seguinte.
 */
	struct sLRect *seg;
} *LRect,NodoR;

/**
 * @struct sLArea
 * @brief Define lista de áreas rectangulares que começa\termina no ponto com coordenadas(x,y).
 */

typedef struct sLArea
{
/**
 * @var n
 * @brief Indica o nome da área definida.
 */
	char n[15];
/**
 * @var x1;
 * @brief Indica a posição do eixo do x onde a área irá começar.
 */
	int x1;
/**
 * @var y1;
 * @brief Indica a posição do eixo do y onde a área irá começar.
 */
	int y1;
/**
 * @var x2;
 * @brief Indica a posição do eixo do x onde a área irá terminar.
 */
	int x2;

/**
 * @var y2;
 * @brief Indica a posição do eixo do y onde a área irá terminar.
 */
	int y2;

/**
 * @var sLArea *seg;
 * @brief O apontador para a área seguinte.
 */
	struct sLArea *seg;
} *LArea,NodoA;

/**
 * @struct sStack
 * @brief Define uma stack.
 */
typedef struct sStack
{
/**
 * @var t;
 * @brief Indica o tipo de restrição (1=COL; 2=COLR; 3=AREA)
 */
	int t;
/**
 * @var n;
 * @brief Nome do rectângulo.
 */
	char n[15];
/**
 * @var x1;
 * @brief Indica a posição do eixo do x onde a área irá começar.
 */
	int x1;
/**
 * @var y1;
 * @brief Indica a posição do eixo do y onde a área irá começar.
 */
	int y1;
/**
 * @var x2;
 * @brief Indica a posição do eixo do x onde a área irá terminar.
 */
	int x2;

/**
 * @var y2;
 * @brief Indica a posição do eixo do y onde a área irá terminar.
 */
  
	int y2;
/**
 * @var sSatck;
 * @brief O apontador para o campo seguinte.
 */
	struct sStack *seg;
}*Stack,NStack;


#endif

