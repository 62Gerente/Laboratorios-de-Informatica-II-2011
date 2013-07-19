/**
 * @file rect.c
 * @author André Santos, Helena Alves, Pedro Faria
 * @date 18 de Maio de 2011
 */

#include "Estruturas.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "erro.c"
#include "aux.c"

/**
 * A funcao 'cDIM' cria uma área. Esta função vai ser executada quando for introduzido o comando 'DIM' e vai receber os respectivos parametros, neste caso, a largura (x) e o comprimento (y) da área. Este carácter vai fazer com que ao utilizar o comando 'DIM', este só pode ser seguido por dois parâmetros, caso aconteça o contrário, a função retorna uma mensagem de erro.
 * Caso seja a primeira vez que esteja a ser inicializado o comando 'DIM', este funciona normalmente. Caso contrário, ou seja, o comando já ter sido utilizado, a função retorna uma mensagem de erro.  
 * @param 'command' comando 'DIM'.
 * @param 'params' recebe os argumentos relativos à dimensão da área.
 * @returns A funcao retorna uma estrutura DIM com os valores da dimenasão criada guardados.
 */
DIM cDIM (char* params, DIM D)
{
	char v; /* Variavel para verificar numero de parametros */
	int x, y, nparams = sscanf (params, "%d %d %c",&x, &y, &v);
	
	if ((D->u) == 1) /* Verificar se ja foi inicializada */
	{
		printf ("NAO\n");
		mensagem_de_erro (6);
	}
	else
	{
		if (nparams != 2) /* Verificar numero de parametros */
		{
			printf ("NAO\n");
			mensagem_de_erro (2);
		}
		else
		{
			D->u = 1; /* Dim passa a estar usado */ 
			D->x = x; 
			D->y = y;
			printf ("SIM\n"); 
		}
	}
	return D;
}

/**
 * A funcao 'cRect' verifica se a dimensão ja foi inicializada, posteriormente  se o número de parâmetros estão correctos e por fim se o rectângulo já existe dentro da dimensão. Caso exista ou o número de parâmetros estejam incorrectos a função retorna uma mensegem de erro. Se não existir e o número de parâmetros inserido estiverem correctos, é inserido o rectângulo.
 * @param 'params' recebe os argumentos necessários à criação de um rectângulo.
 * @param 'L' recebe uma lista de rectângulos.
 * @param 'D' recebe a dimensão.
 * @returns A funcao retorna uma lista de rectângulos com o respectivo rectangulo criado.
 */
LRect cRECT (char* params, LRect L, DIM D)
{
	char v,r,n[15];
	int x,y, nparams = sscanf (params, "%s %d %d %c %c",n, &x, &y, &r, &v);

	if (D->u == 0) /* Verificar se ja foi inicializada */
	{
		printf ("NAO\n");
		mensagem_de_erro (3);
	}
	else
	{
		if (nparams!=4) /* Verificar nr params */
		{
			printf ("NAO\n");
			mensagem_de_erro (2);
		}
		else
		{
			if (x>D->x || y>D->y ) /* Verifica se maior que a dimensão */
			{
				printf ("NAO");
				mensagem_de_erro (12);
			}
			else
			{
				if (verificaN(L,n)) /* 0 se não encontrar, 1 se encontrar*/
				{
					printf ("NAO\n");
					mensagem_de_erro (6);
				}
				else
				{
					if (!(r=='s' || r=='n')) /* 4º parametro ser s ou n */
					{
						printf ("NAO\n");
						mensagem_de_erro (11);
					}
					else
					{
						adicionaR (L,n,x,y,r); /* Insere rectângulo */
						printf ("SIM\n");
					}
				}
			}
		}
	}
	return L;
}

/**
 * A funcao 'cCOL' verifica se a dimensão ja foi inicializada e se o número de parametros estão correctos. Caso isto não aconteça, a função retorna uma mensagem de erro.
 * Se tudo se verificar executa-se a função COL. 
 * @param 'params' recebe os argumentos necessários à colocação de um rectângulo.
 * @param 'L' recebe uma lista de rectangulos.
 * @param 'A' recebe uma lista de areas.
 * @param 'D' recebe a dimensão.
 * @param 'R' recebe uma lista de restrições.
 * @param 'S' recebe uma stack.
 * @returns A funcao retorna 0 se não coloca e 1 se coloca. 
 */
int cCOL (char* params, LRect L, LArea A, DIM D, LRestr R, Stack* S)
{
	char v,n[15];
	int x,y, nparams = sscanf (params, "%s %d %d %c",n, &x, &y, &v), band=1;
	
	if (D->u == 0) /* Verificar se ja foi inicializada */
	{
		band=0;
		printf ("NAO\n");
		mensagem_de_erro (3);
	}
	else
	{
		if (nparams!=3) /* Verificar nr params */
		{
			band=0;
			printf ("NAO\n");
			mensagem_de_erro (2);
		}
		else
		{
			band = COL (L,L,R,A,D,S,n,x,y); /* Coloca rectangulo */
		}
	}
	return band;
}

/**
 *A funcao 'cCOLR' verifica se a dimensão ja foi inicializada e se o número de parametros estão correctos. Caso isto não aconteça, a função retorna uma mensagem de erro.
 * Se tudo se verificar executa-se a função COLR. 
 * @param 'params' recebe os argumentos necessários à colocação de um rectângulo.
 * @param 'L' recebe uma lista de rectangulos.
 * @param 'A' recebe uma lista de areas.
 * @param 'D' recebe a dimensão.
 * @param 'R' recebe uma lista de restrições.
 * @param 'S' recebe uma stack.
 * @returns A funcao retorna 0 se não coloca e 1 se coloca. 
 */
int cCOLR (char* params, LRect L, LArea A, DIM D, LRestr R, Stack* S)
{
	char v,n[15];
	int x,y, nparams = sscanf (params, "%s %d %d %c",n, &x, &y, &v), band=1;

	if (D->u == 0) /* Verificar se ja foi inicializada */
	{
		band=0;
		printf ("NAO\n");
		mensagem_de_erro (3);
	}
	else
	{
		if (nparams!=3) /* Verificar nr params */
		{
			band=0;
			printf ("NAO\n");
			mensagem_de_erro (2);
		}
		else
		{
			band= COLR (L,L,R,A,D,S,n,x,y); /* Coloca rectangulo rodado */
		}
	}
	return band;
}

void cESTADO (LRect L)
{
	while (L)
	{
		if (L->c==1)
		{
			printf ("%15s ",L->n);
			printf ("%5d ",L->x1);
			printf ("%5d ",L->y1);
			printf ("%5d ",L->x2);
			printf ("%5d\n",L->y2);
		}
		L = L->seg;
	}
	
}

/**
 * A funcao 'cDIR' verifica o número de parametros estão correctos. Caso isto não aconteça, a função retorna uma mensagem de erro. Caso se verificar executa-se a função DIR. 
 * @param 'params' recebe o nome dos dois rectângulos.
 * @param 'L' recebe uma lista de rectangulos.
 * @param 'R' recebe uma lista de restrições.
 * @returns A funcao retorna lista de rectângulos. 
 */
LRestr cDIR (char* params, LRect L, LRestr R)
{
	char r1[15], r2[15], v;
	int nparams = sscanf (params, "%s %s %c",r1, r2, &v);
	
	if (nparams!=2) /* Verifica parametros */
	{
		printf ("NAO\n");
		mensagem_de_erro (2);
	}
	else
	{
		vDIR (L,R,r1,r2); /* Verifica se está a direita */
	}
	return R;
}

/**
 * A funcao 'cESQ' verifica o número de parametros estão correctos. Caso isto não aconteça, a função retorna uma mensagem de erro. Caso se verificar executa-se a função ESQ. 
 * @param 'params' recebe o nome dos dois rectângulos.
 * @param 'L' recebe uma lista de rectangulos.
 * @param 'R' recebe uma lista de restrições.
 * @returns A funcao retorna lista de rectângulos. 
 */
LRect cESQ (char* params, LRect L, LRestr R)
{
	char r1[15], r2[15], v;
	int nparams = sscanf (params, "%s %s %c",r1, r2, &v);
	
	if (nparams!=2) /* Verifica parametros */
	{
		printf ("NAO\n");
		mensagem_de_erro (2);
	}
	else
	{
		vESQ (L,R,r1,r2); /* Verifica se está a esquerda */
	}
	return L;
}

/**
 * A funcao 'cCIM' verifica o número de parametros estão correctos. Caso isto não aconteça, a função retorna uma mensagem de erro. Caso se verificar executa-se a função CIM. 
 * @param 'params' recebe o nome dos dois rectângulos.
 * @param 'L' recebe uma lista de rectangulos.
 * @param 'R' recebe uma lista de restrições.
 * @returns A funcao retorna lista de rectângulos. 
 */
LRect cCIM (char* params, LRect L, LRestr R)
{
	char r1[15], r2[15], v;
	int nparams = sscanf (params, "%s %s %c",r1, r2, &v);
	
	if (nparams!=2) /* Verifica parametros */
	{
		printf ("NAO\n");
		mensagem_de_erro (2);
	}
	else
	{
		vCIM (L,R,r1,r2); /* Verifica se está a cima */
	}
	return L;
}

/**
 * A funcao 'cBX' verifica o número de parametros estão correctos. Caso isto não aconteça, a função retorna uma mensagem de erro. Caso se verificar executa-se a função BX. 
 * @param 'params' recebe o nome dos dois rectângulos.
 * @param 'L' recebe uma lista de rectangulos.
 * @param 'R' recebe uma lista de restrições.
 * @returns A funcao retorna lista de rectângulos. 


 */
LRect cBX (char* params, LRect L, LRestr R)
{
	char r1[15], r2[15], v;
	int nparams = sscanf (params, "%s %s %c",r1, r2, &v);
	
	if (nparams!=2) /* Verifica parametros */
	{
		printf ("NAO\n");
		mensagem_de_erro (2);
	}
	else
	{
		vBX (L,R,r1,r2); /* Verifica se está a direita */
	}
	return L;
}

/**
 * A funcao 'cCLD' verifica o número de parametros estão correctos. Caso isto não aconteça, a função retorna uma mensagem de erro. Caso se verificar executa-se a função CLD. 
 * @param 'params' recebe o nome dos dois rectângulos.
 * @param 'L' recebe uma lista de rectangulos.
 * @param 'R' recebe uma lista de restrições.
 * @returns A funcao retorna lista de rectângulos. 
 */
LRect cCLD (char* params, LRect L, LRestr R)
{
	char r1[15], r2[15], v;
	int nparams = sscanf (params, "%s %s %c",r1, r2, &v);
	
	if (nparams!=2) /* Verifica parametros */
	{
		printf ("NAO\n");
		mensagem_de_erro (2);
	}
	else
	{
		vCLD (L,R,r1,r2); /* Verifica se está a direita */
	}
	return L;
}

/**
 * A funcao 'cSEP' verifica o número de parametros estão correctos. Caso isto não aconteça, a função retorna uma mensagem de erro. Caso se verificar executa-se a função SEP. 
 * @param 'params' recebe o nome dos dois rectângulos.
 * @param 'L' recebe uma lista de rectangulos.
 * @param 'R' recebe uma lista de restrições.
 * @returns A funcao retorna lista de rectângulos. 
 */
LRect cSEP (char* params, LRect L, LRestr R)
{
	char r1[15], r2[15], v;
	int nparams = sscanf (params, "%s %s %c",r1, r2, &v);
	
	if (nparams!=2) /* Verifica parametros */
	{
		printf ("NAO\n");
		mensagem_de_erro (2);
	}
	else
	{
		vSEP (L,R,r1,r2); /* Verifica se está a direita */
	}
	return L;
}

/**
 * A funcao 'cAREA' verifica se a dimensão ja foi inicializada, de seguida se o número de parâmetros estão correctos e por fim se a área já existe. Caso exista ou o número de parâmetros estejam incorrectos a função retorna uma mensegem de erro. Se não existir e o número de parâmetros inserido estiverem correctos, é inserido a área.
 * @param 'params' recebe os argumentos necessários à criação de uma área.
 * @param 'A' recebe uma lista de áreas.
 * @param 'D' recebe a dimensão.
 * @param 'S' recebe uma stack.
 * @returns A funcao retorna lista de áreas. 
 */
LArea cAREA (char* params, LArea A, DIM D, Stack* S)
{
	char v,n[15];
	int x,y,c,l, nparams = sscanf (params, "%s %d %d %d %d %c",n, &x, &y, &l, &c, &v);

	if (D->u == 0) /* Verificar se ja foi inicializada */
	{
		printf ("NAO\n");
		mensagem_de_erro (3);
	}
	else
	{
		if (nparams!=5) /* Verificar nr params */
		{
			printf ("NAO\n");
			mensagem_de_erro (2);
		}
		else
		{
			if (verificaA(A,n)) /* 0 se não encontrar, 1 se encontrar*/
			{
				printf ("NAO\n");
				mensagem_de_erro (6);
			}
			else	
			{
				adicionaA (A,S,n,x,y,l,c); /* Insere area */
				printf ("SIM\n");
			}
		}
	}
	return A;
}

/**
 *A funcao 'cDENTRO' verifica se a dimensão ja foi inicializada e se o número de parametros estão correctos. Caso isto não aconteça, a função retorna uma mensagem de erro.
 * Se tudo se verificar executa-se a função DENTRO. 
 * @param 'params' recebe o nome de um rectângulo e o nome de uma área.
 * @param 'L' recebe uma lista de rectângulos.
 * @param 'R' recebe uma lista de restrições.
 * @param 'A' recebe uma lista de áreas.
 * @param 'D' recebe a dimensão.
 * @returns A funcao retorna lista de áreas. 
 */
LArea cDENTRO (char* params, LRect L , LRestr R, LArea A, DIM D)
{
	char v,r[15],a[15];
	int nparams = sscanf (params, "%s %s %c",r,a,&v);

	if (D->u == 0) /* Verificar se ja foi inicializada */
	{
		printf ("NAO\n");
		mensagem_de_erro (3);
	}
	else
	{
		if (nparams!=2) /* Verificar nr params */
		{
			printf ("NAO\n");
			mensagem_de_erro (2);
		}
		else
		{
			DENTRO (L,R,A,r,a); /* Verifica se está Dentro */
		}
	}
	return A;
}

/**
 *A funcao 'cFORA' verifica se a dimensão ja foi inicializada e se o número de parametros estão correctos. Caso isto não aconteça, a função retorna uma mensagem de erro.
 * Se tudo se verificar executa-se a função FORA. 
 * @param 'params' recebe o nome de um rectângulo e o nome de uma área.
 * @param 'L' recebe uma lista de rectângulos.
 * @param 'R' recebe uma lista de restrições.
 * @param 'A' recebe uma lista de áreas.
 * @param 'D' recebe a dimensão.
 * @returns A funcao retorna lista de áreas. 
 */
LArea cFORA (char* params, LRect L , LRestr R, LArea A, DIM D)
{
	char v,r[15],a[15];
	int nparams = sscanf (params, "%s %s %c",r,a,&v);

	if (D->u == 0) /* Verificar se ja foi inicializada */
	{
		printf ("NAO\n");
		mensagem_de_erro (3);
	}
	else
	{
		if (nparams!=2) /* Verificar nr params */
		{
			printf ("NAO\n");
			mensagem_de_erro (2);
		}
		else
		{
			FORA (L,R,A,r,a); /* Verifica se está Fora */
		}
	}
	return A;
}

/**
 *A funcao 'cDESF' verifica se o último introduzido é AREA, COL ou COLR e retrocede para o estado anterior do sitema.
 * @param 'S' recebe um apontador para uma stack.
 * @param 'A' recebe um apontador para uma lista de áreas.
 * @param 'L' recebe um apontador para uma lista de rectângulos.
 * @returns A funcao retorna SIM ou NÃO consoante a condição.
 */
void cDESF (Stack* S, LArea* A, LRect* L)
{
	if (*S)
	{
		if ((*S)->t==3) /* Se ultimo comando for AREA */
		{
			retiraA (*A,(*S)->n); /* Retira Area */
			printf("SIM\n");
		}
		else
		{ 
			if ((*S)->t>0)/* Se for COL ou COLR */
			{
				desfCOL (*L,((*S)->seg),(*S)->n); /* Desfaz COL */
				printf("SIM\n");
			}
			else
			{
				printf("NAO\n");
			}
		}
		(*S)=(*S)->seg;
	}
	else
	{
		printf ("NAO\n");
	}
}

/**
 *A funcao 'cRSV' verifica se a dimensão já foi inicializada, posteriormente irá fazer um comparação entre a area dos rectangulos e a dimensão. Iŕa também verificar se o rectangulo já esta colocado, caso este não estaja irá tentar coloca-lo da melhor forma possivel.
 * @param 'L' recebe uma lista de rectângulos.
 * @param 'aL' recebe uma lista de rectângulos.
 * @param 'R' recebe uma lista de restrições.
 * @param 'A' recebe uma lista de áreas.
 * @param 'D' recebe a dimensão.
 * @param 'S' recebe um apontador para uma stack.
 * @returns A função retorna 1 se tudo se processar correctamente, caso contrario retorna 0.
 */
int cRSV (LRect L,LRect aL,LRestr R,LRestr aR,LArea A,DIM D, Stack* S,int u)
{
	if (D->u==0) return 0; /* Verifica se a DIM já foi inicializada */
	
	if (u==0 && (areatotal (L))>((D->x)*(D->y)) && RSVrestr(aR)==0) return 0; /* Compara a area total dos rectangulos com a area da DIM */
	u++;
	
	if (!L) 
		return 1;
	else
	{
		if (L->c==0 && L->x!=0) /* Se não está colocado */
		{
			int xmax = D->x - L->x +1 ,ymax = D->y - L->y +1,i=1,j=1; /* Define o x e y maximo onde vai tentar colocar */
			
			while (j <= ymax)
			{
					while (i <= xmax)
					{
						if (COLaut (aL,aL,R,A,D,S,L->n,i,j)) /* Tenta colocar Rectangulo */
						{
							if (cRSV (L->seg,aL,R,R,A,D,S,u)) return 1; /* Se conseguir colocar todos os outros */
							else cDESFaut(S,&A,&L); /* Desfaz */
						}
						else
						{
							if (L->r==1) /* Se puder rodar */
							{
								if (COLRaut (aL,aL,R,A,D,S,L->n,i,j)) /* Tenta colocar rodado */
								{
									if (cRSV (L->seg,aL,R,R,A,D,S,u)) return 1; /* Se conseguir colocar todos os outros */
									else cDESFaut(S,&A,&L); /* Desfaz */
								}
							}
						}
						i++;
					}
					i=1;
					j++;
			}
			return 0;	
		}
		else
		{
			if (cRSV (L->seg,aL,R,R,A,D,S,u)) return 1; else return 0; /* Tenta colocar seguintes */
		}			
	}

}
