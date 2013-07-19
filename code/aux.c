/**
 * @file aux.c
 * @author André Santos, Helena Alves, Pedro Faria
 * @date 18 de Maio de 2011
 */


/**
 * A funcao 'verificaN' é uma função auxiliar utilizada no documento 'rect.c'. Esta função verifica se um determinado rectângulo já foi criado, ou seja, se já está presente na lista de rectângulos.
 * @param 'L' Lista de rectângulos.
 * @param 'n' nome do rectângulo.
 * @returns A funcao retorna '0' se o rectângulo ainda não existir e '1' caso contrário.
 */

int verificaN (LRect L, char* n)
{ 
	int v=0;
	while (L && v==0) 
	{
		if (strcmp(L->n,n)==0) v=1; /* Se existir v passa a verdade */
		L = L -> seg;
	}
	return v;
}

/**
 * A funcao 'verificaA' é uma função auxiliar utilizada no documento 'rect.c'. Esta função verifica se uma determinada área já foi criada, ou seja, se já está presente na lista de áreas.
 * @param 'A' Lista de áreas.
 * @param 'n' nome da área.
 * @returns A funcao retorna '0' se a área ainda não existir e '1' caso contrário.
 */
 
int verificaA (LArea A, char* n)
{ 
	int v=0;
	while (A && v==0) 
	{
		if (strcmp(A->n,n)==0) v=1; /* Se existir v passa a verdade */
		A = A -> seg;
	}
	return v;
}

/**
 * A funcao 'adicionaR' é uma função auxiliar utilizada no documento 'rect.c'. Esta função adiciona um rectângulo à lista de rectângulos.
 * Primeiramente verifica-se se a lista de rectângulos está nula ou se, alfabeticamente, o rectângulo pertencer à primeira posição, este é inserido nesta mesma posição. Caso contrario, vai avançando posições.
 * @param 'L' Lista de rectângulos.
 * @param 'n' nome do rectângulo.
 * @param 'x' largura do rectângulo
 * @param 'y' comprimento do rectângulo
 * @returns A funcao retorna uma nova lista já com o novo rectângulo adicionado se verificar todas as condições.
 */
LRect adicionaR (LRect L,char* n, int x, int y, int r)
{
	LRect aux;
	
	if ((!L) || (strcmp(L->n,n)>0)) /* Se estiver na primeira pos. ou ordenado */
	{
		
		aux = (LRect) malloc (sizeof(NodoR)); /* Alocar Espaço */
		
		strcpy(aux -> n , n);
		aux -> x = x;
		aux -> y = y;
		
		if (r=='s') aux -> r = 1;  /* 1 se sim, 0 se não */
		else aux -> r = 0;
		
		aux -> seg = L;
		L = aux;
		return L;
	}
	else
	{
		L -> seg = adicionaR ((L -> seg),n,x,y,r); /* Avança uma posição */
		return L;
	}
}

/**
 * A funcao 'sobreposto' é uma função auxiliar utilizada na função 'COL'. Esta função verifica se o rectângulo que vai ser colocado não fica sobreposto sobre qualquer outro.
 * @param 'L' Lista de rectângulos.
 * @param 'x1' posição do eixo do x onde o rectangulo irá começar.
 * @param 'x2' posição do eixo do x onde o rectangulo irá terminar.
 * @param 'y1' posição do eixo do y onde o rectangulo irá começar.
 * @param 'y2' posição do eixo do y onde o rectangulo irá terminar.
 * @param 'n' nome do rectângulo.
 * @returns A funcao retorna '1' se o rectângulo está sobreposto e '0' caso contrário.
 */
int sobreposto (LRect L, int x1, int y1, int x2, int y2, char* n)
{
	int r=0;
	
	while (L && r==0)
	{
		/* Verifica Sobreposição */
		if ((!(strcmp(L->n,n)==0)) && (!(x2<L->x1 || y2<L->y1 || L->x2<x1 || L->y2<y1))) r=1; 
		L = L -> seg;
	}
	return r;
}

/**
 * A funcao 'restr' é uma função auxiliar utilizada na função 'vrestr'. Esta função verifica com qual das restrições estamos a lidar, ou seja, a restrição 1 corresponde ao comando 'Dir', 2-'ESQ', 3-'CIM', 4-'BX', 5-'CLD', 6-'SEP', 7-'DENTRO', 8-'FORA'.
 * Conforme cada restrição verifica-se se ela se verifica. Por exemplo, na restrição 1 do comando 'DIR' verificamos se o rectângulo A está à direita do B, retornando '0' caso isso aconteça e '1' caso contrário.
 * @param 'R' Lista de restrições.
 * @param 'x1A' posição do eixo do x onde o rectangulo A irá começar.
 * @param 'x2A' posição do eixo do x onde o rectangulo A irá terminar.
 * @param 'y1A' posição do eixo do y onde o rectangulo A irá começar.
 * @param 'y2A' posição do eixo do y onde o rectangulo A irá terminar.
 * @param 'x1B' posição do eixo do x onde o rectangulo B irá começar.
 * @param 'x2B' posição do eixo do x onde o rectangulo B irá terminar.
 * @param 'y1B' posição do eixo do y onde o rectangulo B irá começar.
 * @param 'y2B' posição do eixo do y onde o rectangulo B irá terminar.
 * @returns A funcao retorna '0' se a restrição for validada e '1' caso contrário.
 */
int restr (LRestr R,int x1A,int y1A,int x2A,int y2A,int x1B,int y1B,int x2B,int y2B)
{
	int res=0;
	
	if (R->n==1) /*DIR*/
	{
		if (x1A>x2B) res=0; else res=1;
	}
	else
	{
		if (R->n==2) /*ESQ*/
		{
			if (x2A<x1B) res=0; else res=1;
		}
		else
		{
			if (R->n==3) /*CIM*/
			{
				if (y2A<y1B) res=0; else res=1;
			}
			else
			{
				if (R->n==4) /*BX*/
				{
					if (y1A>y2B) res=0; else res=1;
				}
				else
				{
					if(R->n==5) /*CLD*/
					{
						if (( x2B+1 == x1A && ((y1A>=y1B && y1A<=y2B)
						    || (y2A>=y1B && y2A<=y2B)))
			               ||  ( x2A == x1B-1 && ((y1B>=y1A && y1B<=y2A)
						    || (y2B>=y1A && y2B<=y2A)))
			               ||  ( y2B == y1A-1 && ((x1A>=x1B && x1A<=x2B)
						    || (x2B>=x1B && x2A<=x2B)))
			               ||  ( y2A+1 == y1B && ((x1B>=x1A && x1B<=x2A)
						    || (x2B>=x1A && x2B<=x2A))))
							res=0; else res=1;
					}
					else
					{
						if(R->n==6) /*SEP*/
						{
							if (( x2B+1 == x1A && ((y1A>=y1B && y1A<=y2B)
						    || (y2A>=y1B && y2A<=y2B)))
		               	  ||  ( x2A == x1B-1 && ((y1B>=y1A && y1B<=y2A)
						    || (y2B>=y1A && y2B<=y2A)))
			              ||  ( y2B == y1A-1 && ((x1A>=x1B && x1A<=x2B)
						    || (x2B>=x1B && x2A<=x2B)))
		               	  ||  ( y2A+1 == y1B && ((x1B>=x1A && x1B<=x2A)
						    || (x2B>=x1A && x2B<=x2A))))
				         res=1; else res=0;
						}
						else
						{
							if(R->n==7) /*DENTRO*/
							{
								if (x1A>=x1B && y1A>=y1B && x2A<=x2B && y2A<=y2B) 
									res=0; else res=1;
							}
							else
							{
								if(R->n==8) /*FORA*/
								{
									if ((y2A<=y1B) || (x2B<=x1A) || (y2B<=y1A) || (x2A<=x1B) )  
	                                	 res=0; else res=1;
								}
							}
						}
					}
				}
			}
		}
	}	
	return res;
}

/**
 * A funcao 'vrestr' é uma função auxiliar utilizada em funções deste documento. Esta função verifica com qual das restrições estamos a lidar, ou seja, a restrição 1 corresponde ao comando 'Dir', 2-'ESQ', 3-'CIM', 4-'BX', 5-'CLD', 6-'SEP', 7-'DENTRO', 8-'FORA'.
 * Primeiro verifica-se na lista de restrições se existe alguma respectiva ao rectângulo que estamos a inserir. Caso exista, verifica-se se existe na lista de rectângulos o segundo rectângulo também pertencente à restrição. Se existe e onde quer que os rectângulo esteja colocado, verifica-se se valida a restrição através do 'restr'.
 * E, acontece o mesmo caso esteja-se a lidar com áreas.
 * @param 'R' Lista de restrições.
 * @param 'A' Lista de áreas.
 * @param 'L' Lista de rectaângulos.
 * @param 'n' nome do rectângulo.
 * @param 'x1' posição do eixo do x onde o rectangulo irá começar.
 * @param 'x2' posição do eixo do x onde o rectangulo irá terminar.
 * @param 'y1' posição do eixo do y onde o rectangulo irá começar.
 * @param 'y2' posição do eixo do y onde o rectangulo irá terminar.
 * @returns A funcao retorna '0' se a restrição for validada e '1' caso contrário.
 */
int vrestr (LRestr R,LArea A, LRect L, char* n,int x1,int y1,int x2,int y2)
{
	LRect auxR = L;
	LArea auxA = A;
	int res =0;
	
	while (R  && res ==0)
	{
		if (strcmp(R->c1,n)==0) /*Se estiver no 1º parametro do comando*/
		{
			if (R->n < 7) /* Verifica se é relativa a rectangulos apenas */
			{
				while (L  && res ==0)
				{
					if (strcmp(L->n,R->c2)==0 && L->c==1 ) /* Procura Rectangulo e verifica se está colocado */
					{
						res = restr(R,x1,y1,x2,y2,L->x1,L->y1,L->x2,L->y2); 
					}
					L= L->seg;
				}
				L = auxR;
			}
			else
			{
				while (A  && res ==0)
				{
					if (strcmp(A->n,R->c2)==0) /* Procura Area */
					{
						res = restr(R,x1,y1,x2,y2,A->x1,A->y1,A->x2,A->y2);
					}
					A= A->seg;
				}
				A = auxA;
			}
		}
		else if (strcmp(R->c2,n)==0)
		{
			while (L  && res ==0 )
			{
				if (strcmp(L->n,R->c1)==0 && L->c==1 )/* Procura Rectangulo e verifica se está colocado */
				{
					res = restr(R,L->x1,L->y1,L->x2,L->y2,x1,y1,x2,y2);
				}
				L= L->seg;
			}
			L= auxR;
		}
		R= R->seg;
	}
	
	return res;
}

/**
 * A funcao 'insStack' é uma função auxiliar utilizada em funções deste documento. Esta função adiciona um rectângulos com o seu nome e suas coordenadas à Stack.
 * Nesta Stack são guardados as condições que dizem respeito aos comandos COL, COLR e AREA. 
 * @param 'S' Stack.
 * @param 't' número que é atribuido ao comando.
 * @param 'n' nome do rectângulo.
 * @param 'x1' posição do eixo do x onde o rectangulo irá começar.
 * @param 'x2' posição do eixo do x onde o rectangulo irá terminar.
 * @param 'y1' posição do eixo do y onde o rectangulo irá começar.
 * @param 'y2' posição do eixo do y onde o rectangulo irá terminar.
 * @returns A funcao retorna uma nova lista já com o novo rectângulo adicionado.
 */
void insStack (Stack* S, int t,char* n,int x1, int y1, int x2,int y2)
{
	Stack aux = (Stack) malloc (sizeof(NStack)); /* Aloca Espaço */
	/* Atribui Valores */
	strcpy(aux->n,n);
	aux->t=t;
	aux->x1=x1;
	aux->y1=y1;
	aux->x2=x2;
	aux->y2=y2;	
	aux-> seg = *S;
	*S = aux;
}

/**
 * A funcao 'COL' é uma função auxiliar utilizada na função 'cCOL' do documento rect.c. Esta função tem como objectivo colocar um rectângulo. 
 * Primeiramente, começa por verifivar se o rectângulo já foi criado, se fica dentro da dimensão inicial e se não fica sobreposto. Posteriormente, verificamos se não há nenhuma restrição que impeça o rectângulo de ser colocado. Caso isso aconteça, coloca-se o rectângulo e inserimo-lo na Stack.
 * @param 'L' Lista de rectângulos.
 * @param 'aux' Lista auxiliar de rectângulos.
 * @param 'R' Lista de restrições.
 * @param 'A' Lista de áreas.
 * @param 'D' Dimensão inicial.
 * @param 'n' Nome do rectângulo.
 * @param 'x' posição x do rectângulo.
 * @param 'y' posição y do rectângulo.
 * @returns A função retorna a lista de restrições. 
 */
int COL (LRect L, LRect aux, LRestr R,LArea A , DIM D,Stack* S, char* n, int x, int y)
{
	int band=1;
	if (strcmp(L->n,n)==0) /* Se encontrou o rectangulo */
	{
		if (!(x >= 1 && y >= 1 && x+ L->x -1 <= D->x && y+ L->y -1 <= D->y )) /* Verifica se fica dentro da dimençao */
		{
			band=0;
			printf ("NAO\n");
			mensagem_de_erro (9);
		}
		else
		{
			if (sobreposto(aux,x,y,x+ L->x-1 ,y+ L->y-1,n )) /* Verifica se não fica sobreposto */
			{
				band=0;
				printf("NAO\n");
				mensagem_de_erro (10);
			}
			else
			{
				if (vrestr (R,A,aux,n,x,y,x+ L->x -1,y+ L->y -1)) /*Verifica Restrição*/
				{
					band=0;
					printf("NAO\n");
					mensagem_de_erro (12);
				}
				else
				{
					insStack (S,1,n,x,y,x+ L->x -1,y+ L->y -1); /*Insere na Stack*/
					L->x1 = x;
					L->y1 = y;
					L->x2 = x+ L->x -1;
					L->y2 = y+ L->y -1;
					L->c  = 1;		
					printf ("SIM\n");
				}
			}
		}
	}
	else 
	{
		if (L->seg)
		{
			band = COL (L->seg,aux,R,A,D,S,n,x,y); /* Continua a procurar o rectangulo que quer colocar */
		}
		else
		{
			band=0;
			printf ("NAO\n");
			mensagem_de_erro (5);
		}
	}
	return band;
}

/**
 * A funcao 'COLR' é uma função auxiliar utilizada na função 'cCOLR' do documento rect.c. Esta função tem como objectivo colocar um rectângulo rodado. 
 * Primeiramente, começa por verifivar se o rectângulo já foi criado, se fica dentro da dimensão inicial e se não fica sobreposto. Posteriormente, verificamos se não há nenhuma restrição que impeça o rectângulo de ser colocado. Caso isso aconteça, coloca-se o rectângulo e inserimo-lo na Stack.
 * @param 'L' Lista de rectângulos.
 * @param 'aux' Lista auxiliar de rectângulos.
 * @param 'R' Lista de restrições.
 * @param 'A' Lista de áreas.
 * @param 'D' Dimensão inicial.
 * @param 'n' Nome do rectângulo.
 * @param 'x' Posição x do rectângulo.
 * @param 'y' Posição y do rectângulo.
 * @returns A função retorna a lista de restrições. 
 */
int COLR (LRect L, LRect aux, LRestr R,LArea A , DIM D,Stack* S, char* n, int x, int y)
{
	int band= 1;
	if (strcmp(L->n,n)==0)/* Se encontrou rectangulo */
	{
		if (!L->r) /* Verifica se pode rodar */
		{
			band=0;
			printf ("NAO\n");
			mensagem_de_erro (8);
		}
		else
		{
			if (!(x >= 1 && y >= 1 && x+ L->y -1 <= D->x && y+ L->x -1 <= D->y )) /* Verifica se fica dentro da dimensao */
			{
				band=0;
				printf ("NAO\n");
				mensagem_de_erro (9);
			}
			else
			{
				if (sobreposto(aux,x,y,x+ L->y-1 ,y+ L->x-1, n)) /* Verifica se está sobreposto */
				{
					band=0;
					printf("NAO\n");
					mensagem_de_erro (10);
				}
				else
				{
					if (vrestr (R,A,aux,n,x,y,x+ L->y -1,y+ L->x -1)) /* Verifica Restrição */
					{
						band=0;
						printf("NAO\n");
						mensagem_de_erro (12);
					}				
					else
					{
						insStack (S,2,n,x,y,x+ L->y -1,y+ L->x -1); /* Insere Stack */
						L->x1 = x;
						L->y1 = y;
						L->x2 = x+ L->y -1;
						L->y2 = y+ L->x -1;
						L->c  = 1;		
						printf ("SIM\n");
					}
				}
			}
		}
	}
	else 
	{
		if (L->seg)
		{
			COLR(L->seg,aux,R,A,D,S,n,x,y); /* Continua a procurar o rectangulo que quer colocar */
		}
		else
		{
			band=0;
			printf ("NAO\n");
			mensagem_de_erro (5);
		}
	}
	return band;
}
/**
 * A funcao 'insererestr' é uma função auxiliar utilizada nas funções 'DIR', 'ESQ', 'CIM', 'BX, 'CLD', 'SEP', DENTRO', 'FORA'. Esta função insere na lista de restrições uma nova restrição.
 * @param 'R' Lista de restrições.
 * @param 'n' Nome da restrição, sendo que esta está codificado em número.gulo.
 * @param 'c1' Nome do primeiro rectângulo.
 * @param 'c2' Nome do segundo rectângulo.
 * @returns A funcao retorna a lista de restrições.
 */
LRestr insererestr (LRestr R, int n, char* c1, char* c2)
{
	LRestr aux;
	
	if (!R) /* Se estiver na primeira pos */
	{
		
		aux = (LRestr) malloc (sizeof(NodoRestr)); /* Alocar Espaço */
		/* Atribui Valores */
		aux->n = n;
		strcpy(aux -> c1 , c1);
		strcpy(aux -> c2 , c2);

		aux -> seg = R;
		R = aux;
		printf ("SIM\n");
		return R;
	}
	else
	{
		if (R->n==n && (strcmp (R->c1,c1)==0) && (strcmp (R->c2,c2)==0))
		{
			printf ("NAO\n");
			mensagem_de_erro (6);
			return R;
		}
		else
		{
			R -> seg = insererestr ((R -> seg),n,c1,c2); /* Avança uma posição */
			return R;
		}
	}
}

/**
 * A funcao 'vDIR' é função auxiliar utilizada na função 'cDIR' do documento rect.c. Esta função tem como objectivo verificar se um rectângulo está à direita de outro. 
 * Primeiramente, começa por encontrar os dois rectângulos na lista de rectângulos, caso os encontre verifica se algum ponto não foi gravado, ou seja, verifica se algum dos rectângulos existentes na lista de rectângulos não foi colocado. Neste caso, a função retorna sim e a restrição é guardada na lista de restrições.
 * Se os dois rectângulos já estiverem colocados a função verifica se o primeiro está à direita do outro.  
 * @param 'L' Lista de rectângulos.
 * @param 'R' Lista de restrições.
 * @param 'r1' Nome do primeiro rectângulo.
 * @param 'r2' Nome do segundo rectângulo.
 * @returns A função retorna a lista de restrições. 
 */
LRestr vDIR (LRect L, LRestr R, char* r1, char* r2)
{
	int x1A=0, x2B=0;
	int flagA = 0, flagB = 0;
	
	while (L && (flagA==0 || flagB==0)) /* Verifica se já gravou os 2 pontos */
	{
		if (strcmp(r1,L->n)==0) /* Se encontrou o 1º rectangulo */
		{
			flagA = 1;
			x1A = L->x1;
		}
		else if (strcmp(r2,L->n)==0) /* Se encontrou o 2º rectangulo */
		{
			flagB = 1;
			x2B = L->x2;
		}
	L=L->seg;
	}
	
	if (flagA == 1 && flagB ==1)
	{
		if (x1A==0 || x2B==0) /* Se algum ponto nao foi gravado */
		{
			insererestr (R,1,r1,r2); /* Guarda Restrição */
		}
		else if (x1A>x2B) printf ("SIM\n"); else printf ("NAO\n"); /* Verifica se está à direita */
	}
	else
	{
		printf ("NAO\n");
		mensagem_de_erro (5);
	}
	
	return R; 
}

/**
 * A funcao 'vESQ' é função auxiliar utilizada na função 'cESQ' do documento rect.c. Esta função tem como objectivo verificar se um rectângulo está à esquerda de outro. 
 * Primeiramente, começa por encontrar os dois rectângulos na lista de rectângulos, caso os encontre verifica se algum ponto não foi gravado, ou seja, verifica se algum dos rectângulos existentes na lista de rectângulos não foi colocado. Neste caso, a função retorna sim e a restrição é guardada na lista de restrições.
 * Se os dois rectângulos já estiverem colocados a função verifica se o primeiro está à esquerda do outro.  
 * @param 'L' Lista de rectângulos.
 * @param 'R' Lista de restrições.
 * @param 'r1' Nome do primeiro rectângulo.
 * @param 'r2' Nome do segundo rectângulo.
 * @returns A função retorna 'SIM' se o o primeiro rectângulo está à esquerda do outro e quando é guardada a restrição, e retorna 'NAO' caso contrário. 
 */
void vESQ (LRect L, LRestr R, char* r1, char* r2)
{
	int x2A=0, x1B=0;
	int flagA=0, flagB=0;
	
	while (L && (flagA==0 || flagB==0)) /* Verifica se já gravou os 2 pontos */
	{
		if (strcmp(r1,L->n)==0) /* Se encontrou o 1º rectangulo */
		{
			flagA=1;
			x2A = L->x2;
		}
		else if (strcmp(r2,L->n)==0) /* Se encontrou o 2º rectangulo */
		{
			flagB=1;
			x1B = L->x1;
		}
	L=L->seg;
	}
	
	if(flagA==1 && flagB==1) /* Se encontrou os dois */
	{
	
		if (x2A==0 || x1B==0) /* Se algum ponto nao foi gravado */
		{
			insererestr (R,2,r1,r2); /* Guarda Restrição */
		}
		else if (x2A<x1B) printf ("SIM\n"); else printf ("NAO\n"); /* Verifica se está á esquerda */ 
	}
	else
	{
		printf ("NAO\n");
		mensagem_de_erro (5);
	}
}

/**
 * A funcao 'vCIM' é função auxiliar utilizada na função 'cCIM' do documento rect.c. Esta função tem como objectivo verificar se um rectângulo está acima de outro. 
 * Primeiramente, começa por encontrar os dois rectângulos na lista de rectângulos, caso os encontre verifica se algum ponto não foi gravado, ou seja, verifica se algum dos rectângulos existentes na lista de rectângulos não foi colocado. Neste caso, a função retorna sim e a restrição é guardada na lista de restrições.
 * Se os dois rectângulos já estiverem colocados a função verifica se o primeiro está acima do outro.  
 * @param 'L' Lista de rectângulos.
 * @param 'R' Lista de restrições.
 * @param 'r1' Nome do primeiro rectângulo.
 * @param 'r2' Nome do segundo rectângulo.
 * @returns A função retorna 'SIM' se o o primeiro rectângulo está acima do outro e quando é guardada a restrição, e retorna 'NAO' caso contrário.  
 */
void vCIM (LRect L, LRestr R, char* r1, char* r2)
{
	int y2A=0, y1B=0;
	int flagA=0, flagB=0;
	
	while (L && (flagA==0 || flagB==0)) /* Verifica se já gravou os 2 pontos */
	{
		if (strcmp(r1,L->n)==0) /* Se encontrou o 1º rectangulo */
		{
			flagA=1;
			y2A = L->y2;
		}
		else if (strcmp(r2,L->n)==0) /* Se encontrou o 2º rectangulo */
		{
			flagB=1;
			y1B = L->y1;
		}
	L=L->seg;
	}
	
	if(flagA==1 && flagB==1) /* Se encontrou os dois */
	{
		
		if (y2A==0 || y1B==0) /* Se algum ponto nao foi gravado */
		{
			insererestr (R,3,r1,r2); /* Guarda Restrição */
		}
		else if (y2A<y1B) printf ("SIM\n"); else printf ("NAO\n"); /* Verifica se está acima */ 
	}
	else
	{
		printf ("NAO\n");
		mensagem_de_erro (5);
	}
}

/**
 * A funcao 'vBX' é função auxiliar utilizada na função 'cBX' do documento rect.c. Esta função tem como objectivo verificar se um rectângulo está abaixo de outro. 
 * Primeiramente, começa por encontrar os dois rectângulos na lista de rectângulos, caso os encontre verifica se algum ponto não foi gravado, ou seja, verifica se algum dos rectângulos existentes na lista de rectângulos não foi colocado. Neste caso, a função retorna sim e a restrição é guardada na lista de restrições.
 * Se os dois rectângulos já estiverem colocados a função verifica se o primeiro está abaixo do outro.  
 * @param 'L' Lista de rectângulos.
 * @param 'R' Lista de restrições.
 * @param 'r1' Nome do primeiro rectângulo.
 * @param 'r2' Nome do segundo rectângulo.
 * @returns A função retorna 'SIM' se o o primeiro rectângulo está abaixo do outro e quando é guardada a restrição, e retorna 'NAO' caso contrário.  
 */
void vBX (LRect L, LRestr R, char* r1, char* r2)
{
	int y1A=0, y2B=0;
	int flagA=0, flagB=0;
	
	while (L && (flagA==0 || flagB==0 )) /* Verifica se já gravou os 2 pontos */
	{
		if (strcmp(r1,L->n)==0) /* Se encontrou o 1º rectangulo */
		{
			flagA=1;
			y1A = L->y1;
		}
		else if (strcmp(r2,L->n)==0) /* Se encontrou o 2º rectangulo */
		{
			flagB=1;
			y2B = L->y2;
		}
	L=L->seg;
	}
	if(flagA==1 && flagB==1)
	{
		if (y1A==0 || y2B==0) /* Se algum ponto nao foi gravado */
		{ 
			insererestr (R,4,r1,r2); /* Guarda Restrição */
		}
		else if (y1A>y2B) printf ("SIM\n"); else printf ("NAO\n"); /* Verifica se está abaixo */ 
	}
	else
	{
		printf ("NAO\n");
		mensagem_de_erro (5);
	}
}

/**
 * A funcao 'vCLD é função auxiliar utilizada na função 'cCIM' do documento rect.c. Esta função tem como objectivo verificar se um rectângulo está colado a outro. 
 * Primeiramente, começa por encontrar os dois rectângulos na lista de rectângulos, caso os encontre verifica se algum ponto não foi gravado, ou seja, verifica se algum dos rectângulos existentes na lista de rectângulos não foi colocado. Neste caso, a função retorna sim e a restrição é guardada na lista de restrições.
 * Se os dois rectângulos já estiverem colocados a função verifica se os rectângulos estão colados.
 * @param 'L' Lista de rectângulos.
 * @param 'R' Lista de restrições.
 * @param 'r1' Nome do primeiro rectângulo.
 * @param 'r2' Nome do segundo rectângulo.
 * @returns A função retorna 'SIM' se os rectângulos estão colados e quando é guardada a restrição, e retorna 'NAO' caso contrário.  
 */
void vCLD (LRect L, LRestr R, char* r1, char* r2)
{
	int y1A=0, y2B=0, y2A=0, y1B=0, x1A=0, x1B=0, x2A=0, x2B=0;
	int flagA=0, flagB=0;
	
	while (L && (flagA==0 || flagB==0)) /* Verifica se já gravou os 2 pontos */
	{
		if (strcmp(r1,L->n)==0) /* Se encontrou o 1º rectangulo */
		{
			flagA=1;
			y1A = L->y1;
			y2A = L->y2;
			x1A = L->x1;
			x2A = L->x2;
		}
		else if (strcmp(r2,L->n)==0) /* Se encontrou o 2º rectangulo */
		{
			flagB=1;
			y2B = L->y2;
			y1B = L->y1;
			x1B = L->x1;
			x2B = L->x2;
		}
	L=L->seg;
	}
	if(flagA==1 && flagB==1)
	{
		if (y1A==0 || y2B==0) /* Se algum ponto nao foi gravado */
		{ 
			insererestr (R,5,r1,r2); /* Guarda Restrição */
		}
		else if (( x2B+1 == x1A && ((y1A>=y1B && y1A<=y2B)
						    || (y2A>=y1B && y2A<=y2B)))
			||  ( x2A == x1B-1 && ((y1B>=y1A && y1B<=y2A)
						    || (y2B>=y1A && y2B<=y2A)))
			||  ( y2B == y1A-1 && ((x1A>=x1B && x1A<=x2B)
						    || (x2B>=x1B && x2A<=x2B)))
			||  ( y2A+1 == y1B && ((x1B>=x1A && x1B<=x2A)
						    || (x2B>=x1A && x2B<=x2A))))
				 printf ("SIM\n"); else printf ("NAO\n"); /* Verifica se está colado */ 
	}
	else
	{
		printf ("NAO\n");
		mensagem_de_erro (5);
	}
}

/**
 * A funcao 'vCLD é função auxiliar utilizada na função 'cCIM' do documento rect.c. Esta função tem como objectivo verificar se um rectângulo está separado de outro. 
 * Primeiramente, começa por encontrar os dois rectângulos na lista de rectângulos, caso os encontre verifica se algum ponto não foi gravado, ou seja, verifica se algum dos rectângulos existentes na lista de rectângulos não foi colocado. Neste caso, a função retorna sim e a restrição é guardada na lista de restrições.
 * Se os dois rectângulos já estiverem colocados a função verifica se os rectângulos estão separados.
 * @param 'L' Lista de rectângulos.
 * @param 'R' Lista de restrições.
 * @param 'r1' Nome do primeiro rectângulo.
 * @param 'r2' Nome do segundo rectângulo.
 * @returns A função retorna 'SIM' se os rectângulos estão separados e quando é guardada a restrição, e retorna 'NAO' caso contrário.  
 */
void vSEP (LRect L, LRestr R, char* r1, char* r2)
{
	int y1A=0, y2B=0, y2A=0, y1B=0, x1A=0, x1B=0, x2A=0, x2B=0;
	int flagA=0, flagB=0;
	
	while (L && (flagA==0 || flagB==0)) /* Verifica se já gravou os 2 pontos */
	{
		if (strcmp(r1,L->n)==0) /* Se encontrou o 1º rectangulo */
		{
			flagA=1;
			y1A = L->y1;
			y2A = L->y2;
			x1A = L->x1;
			x2A = L->x2;
		}
		else if (strcmp(r2,L->n)==0) /* Se encontrou o 2º rectangulo */
		{
			flagB=1;
			y2B = L->y2;
			y1B = L->y1;
			x1B = L->x1;
			x2B = L->x2;
		}
	L=L->seg;
	}
	
	if(flagA==1 && flagB==1) /* Se encontrou os dois */
	{
		if (y1A==0 || y2B==0) /* Se algum ponto nao foi gravado */
		{
			insererestr (R,6,r1,r2); /* Guarda Restrição */
		}
		else if (( x2B+1 == x1A && ((y1A>=y1B && y1A<=y2B)
							|| (y2A>=y1B && y2A<=y2B)))
			||  ( x2A == x1B-1 && ((y1B>=y1A && y1B<=y2A)
						    || (y2B>=y1A && y2B<=y2A)))
			||  ( y2B == y1A-1 && ((x1A>=x1B && x1A<=x2B)
						    || (x2B>=x1B && x2A<=x2B)))
			||  ( y2A+1 == y1B && ((x1B>=x1A && x1B<=x2A)
						    || (x2B>=x1A && x2B<=x2A))))
				 printf ("NAO\n"); else printf ("SIM\n"); /* Verifica se está a baixo */ 
	}
	else
	{
		printf ("NAO\n");
		mensagem_de_erro (5);
	}
}

/**
 * A funcao 'adicionaA' é uma função auxiliar utilizada no documento 'rect.c'. Esta função adiciona uma área à lista de áreas.
 * Primeiramente verifica-se se a lista de áreas está nula ou se, alfabeticamente, a área pertencer à primeira posição, esta é inserida nesta mesma posição. Caso contrario, vai avançando posições.
 * @param 'A' Lista d áreas.
 * @param 'S' Stack.
 * @param 'n' Nome da área.
 * @param 'x' posição x onde a área irá começar.
 * @param 'y' posição y onde a área irá começar.
 * @param 'l' Larfura da área.
 * @param 'c' Comprimento da área.
 * @returns A funcao retorna uma nova lista já com a nova área adicionada.
 */
LArea adicionaA (LArea A,Stack* S,char* n, int x, int y, int l,int c)
{
	LArea aux;
	
	if ((!A) || (strcmp(A->n,n)>0)) /* Se estiver na primeira pos. ou ordenado */
	{	
		aux = (LArea) malloc (sizeof(NodoA)); /* Alocar Espaço */
		insStack(S,3,n,0,0,0,0); /* Insere Stack */
		/* Atribui Valores */
		strcpy(aux -> n , n);
		aux -> x1 = x;
		aux -> y1 = y;
		aux -> x2 = x+l-1;
		aux -> y2 = y+c-1;
		aux -> seg = A;
		A = aux;
		return A;
	}
	else
	{
		A -> seg = adicionaA ((A -> seg),S,n,x,y,l,c); /* Avança uma posição */
		return A;
	}
}

/**
 * A funcao 'DENTRO' é função auxiliar utilizada na função 'cDENTRO' do documento rect.c. Esta função tem como objectivo verificar se um rectângulo está dentro de uma dada área. 
 * Primeiramente, começa por encontrar o rectângulo na lista de rectângulos e a área na lista de áreas, caso os encontre verifica se algum ponto não foi gravado, ou seja, verifica se o rectângulo existente na lista de rectângulos não foi colocado. Neste caso, a função retorna sim e a restrição é guardada na lista de restrições.
 * Se o rectângulo já estiver colocado a função verifica se este está dentro da área.
 * @param 'L' Lista de rectângulos.
 * @param 'R' Lista de restrições.
 * @param 'r1' Nome do primeiro rectângulo.
 * @param 'r2' Nome do segundo rectângulo.
 * @returns A função retorna 'SIM' se o rectângulo está dentro da área e quando é guardada a restrição, e retorna 'NAO' caso contrário.  
 */
void DENTRO (LRect L, LRestr R, LArea A, char* r, char* a)
{
	int y1A=0, y2A=0, y2R=0, y1R=0, x1A=0, x1R=0, x2A=0, x2R=0;
	int flagA=0, flagB=0;
		
	while (L && (flagA==0)) /* Verifica se já gravou os 2 pontos */
	{
		if (strcmp(r,L->n)==0) /* Se encontrou o 1º rectangulo */
		{
			flagA=1;
			y1R = L->y1;
			y2R = L->y2;
			x1R = L->x1;
			x2R = L->x2;
		}
	L=L->seg;
	}

	while (A && (flagB==0)) /* Verifica se já gravou o ponto */
	{
		if (strcmp(a,A->n)==0) /* Se encontrou a Area */
		{
			flagB=1;
			y2A = A->y2;
			y1A = A->y1;
			x1A = A->x1;
			x2A = A->x2;
		}
	A=A->seg;
	}
	
	if(flagA==1 && flagB==1)
	{
		if (y1A==0 || y1R==0) /* Se algum ponto nao foi gravado */
		{
			insererestr (R,7,r,a); /* Guarda Restrição */
		}
		else if (x1R>=x1A && y1R>=y1A && x2R<=x2A && y2R<=y2A) 
	
				 printf ("SIM\n"); else printf ("NAO\n"); /* Verifica se está a dentro */ 
	}
	else
	{
		printf ("NAO\n");
		mensagem_de_erro (5);
	}
}

/**
 * A funcao 'FORA' é função auxiliar utilizada na função 'cFORA' do documento rect.c. Esta função tem como objectivo verificar se um rectângulo está fora de uma dada área. 
 * Primeiramente, começa por encontrar o rectângulo na lista de rectângulos e a área na lista de áreas, caso os encontre verifica se algum ponto não foi gravado, ou seja, verifica se o rectângulo existente na lista de rectângulos não foi colocado. Neste caso, a função retorna sim e a restrição é guardada na lista de restrições.
 * Se o rectângulo já estiver colocado a função verifica se este está fora da área.
 * @param 'L' Lista de rectângulos.
 * @param 'R' Lista de restrições.
 * @param 'r1' Nome do primeiro rectângulo.
 * @param 'r2' Nome do segundo rectângulo.
 * @returns A função retorna 'SIM' se o rectângulo está fora da área e quando é guardada a restrição, e retorna 'NAO' caso contrário.  
 */
void FORA (LRect L, LRestr R, LArea A, char* r, char* a)
{
	int y1A=0, y2A=0, y2R=0, y1R=0, x1A=0, x1R=0, x2A=0, x2R=0;
	int flagA=0, flagB=0;
	
	while (L && (flagA==0)) /* Verifica se já gravou os 2 pontos */
	{
		if (strcmp(r,L->n)==0) /* Se encontrou o 1º rectangulo */
		{
			flagA=1;
			y1R = A->y1;
			y2R = A->y2;
			x1R = A->x1;
			x2R = A->x2;
		}
	L=L->seg;
	}

	while (A && (flagB==0)) /* Verifica se já gravou o ponto */
	{
		if (strcmp(a,A->n)==0) /* Se encontrou a Area */
		{
			flagB=1;
			y2A = A->y2;
			y1A = A->y1;
			x1A = A->x1;
			x2A = A->x2;
		}
	A=A->seg;
	}
	
	if(flagA==1 && flagB==1) /* Se existem os dois */
	{
		
		if (y1A==0 || y1R==0) /* Se algum ponto nao foi gravado */
		{
			insererestr (R,8,r,a); /* Guarda Restrição */
		}
		else if ((y2R<=y1A) || (x2A<=x1R) || (y2A<=y1R) || (x2R<=x1A) )  
	
				 printf ("SIM\n"); else printf ("NAO\n"); /* Verifica se está a fora */ 
	}
	else
	{
		printf ("NAO\n");
		mensagem_de_erro (5);
	}
}

/**
 * A funcao 'retiraA' é uma função auxiliar utilizada na função 'DESF' do documento 'rect.c'. Esta função retira uma área à lista de áreas.
 * @param 'A' Lista de áreas.
 * @param 'S' Stack.
 * @param 'n' Nome da área.
 * @param 'x' posição x onde a área irá começar.
 * @param 'y' posição y onde a área irá começar.
 * @param 'l' Larfura da área.
 * @param 'c' Comprimento da área.
 * @returns A funcão retorna uma nova lista já com a nova área adicionada.
 */
LArea retiraA (LArea A,char* n)
{
	LArea aux;
	if (A)
	{
		if (strcmp(A->n,n)==0) /* Se for a area procurada */
		{
			aux = A->seg;
			A=aux;
			return A;
		}
		else
		{
			A->seg = retiraA (A->seg,n); /* Avança uma posição */
			return A;
		}
	}
	return A;
}

/**
 * A funcao 'desfCOL' é uma função auxiliar utilizada na função 'DESF' do documento 'rect.c'. Esta função elimina o último comando relativo ao 'COL' ou ao 'COLR'.
 * Primeiro verifica-se se existe o rectângulo na Stack, depois procurámo-lo na lista de rectângulos. Caso exista outro comando 'COL' ou 'COLR' mesmo depois de já ter sido elimando um, passamos as coordenadas do rectângulo para as coordenadas do comando anterior.
 * Caso nao existe mais nenhum comando 'COL' ou 'COLR' o rectângulo deixa de estar colocado, passando a variável 'c' a ser 0.
 * @param 'L' Lista de rectângulos.
 * @param 'S' Stack.
 * @param 'n' Nome do rectângulo.
 */
void desfCOL (LRect L,Stack S ,char* n)
{
	int x1=0,x2=0,y1=0,y2=0;
	Stack aS=S; 
	LRect aL=L;
	int band1=0;
	
	while (S && band1==0)
	{
		if (strcmp(S->n,n)==0 && S->t<3) /* Procura COL anterior */
		{
			x1=S->x1;
			x2=S->x2;
			y1=S->y1;
			y2=S->y2;
			
			while (L && band1==0)
			{
				if (strcmp(L->n,n)==0) /* Procura Rectangulo */
				{
					L->x1=x1;
					L->y1=y1;
					L->x2=x2;
					L->y2=y2;
					band1 = 1;
				}
				L=L->seg;
			}
		}
	S=S->seg;
	}
	
	S=aS;
	L=aL;
	
	while (L && band1==0)
	{
		if (strcmp(L->n,n)==0) /* Procura Rectangulo */
		{
			L->x1=x1;
			L->y1=y1;	
			L->x2=x2;
			L->y2=y2;
			L->c=0;
			band1 = 1;
		}			
		L=L->seg;
	}
	
}

/**
 * A funcao 'COLaut' é uma função auxiliar utilizada na função 'cRSV' do documento 'rect.c'. Esta função coloca um rectângulo pronto a ser colocado.
 * Primeiro verifica-se se o rectângulo existe na lista de rectângulos, depois verificamos se este fica dentro da dimensão. Caso isto aconteça, verifica novamente se este rectângulo não fica sobreposto sobre outro e, vai verificar na lista de restrições se existe alguma que mencione o nome do rectângulo a colocar; caso mencione e a restrição for validada ele vai inserir a restrição na stack.
 * Caso inicialmente o rectângulo não tenha sido encontrado, ele continua a procurar na lista de rectângulos.
 * @param 'L' Lista de rectângulos.
 * @param 'aux' Lista de rectângulos auxiliar.
 * @param 'R' Lista de restrições.
 * @param 'A' Lista de Áreas.
 * @param 'D' Dimensão.
 * @param 'S' Apontador para a Stack.
 * @param 'n' Nome do rectângulo.
 * @param 'x' Posição inicial do rectângulo no eixo dos x.
 * @param 'y' Posição inicial do rectângulo no eixo dos y.
 * @returns A função retorna '0' caso o rectângulo não seja colocado e '1' caso contrário. 
 */
int COLaut (LRect L, LRect aux, LRestr R,LArea A , DIM D,Stack* S, char* n, int x, int y)
{
	int band=1;
	if (L)
	{
		if (strcmp(L->n,n)==0) /* Se encontrou o rectangulo */
		{
			if (!(x >= 1 && y >= 1 && x+ L->x -1 <= D->x && y+ L->y -1 <= D->y )) /* Verifica se fica dentro da dimençao */
			band=0;
			else
			{
				if (sobreposto(aux,x,y,x+ L->x-1 ,y+ L->y-1,n )) /* Verifica se não fica sobreposto */
				band=0;
				else
				{
					if (vrestr (R,A,aux,n,x,y,x+ L->x -1,y+ L->y -1)) /*Verifica Restrição*/
					band=0;
					else
					{
						insStack (S,1,n,x,y,x+ L->x -1,y+ L->y -1); /*Insere na Stack*/
						L->x1 = x;
						L->y1 = y;
						L->x2 = x+ L->x -1;
						L->y2 = y+ L->y -1;
						L->c  = 1;		
					}
				}
			}
		}
		else 
		{
			if (L->seg)
			{
				band = COLaut (L->seg,aux,R,A,D,S,n,x,y); /* Continua a procurar o rectangulo que quer colocar */
			}
			else 
			band=0;
		}
	}
	return band;
}
/**
 * A funcao 'COLRaut' é uma função auxiliar utilizada na função 'cRSV' do documento 'rect.c'. Esta função coloca um rectângulo rodado pronto já definido.
 * Primeiro verifica-se se o rectângulo existe na lista de rectângulos e se este pode rodar, depois verificamos se este fica dentro da dimensão. Caso isto aconteça, verifica novamente se este rectângulo não fica sobreposto sobre outro e, vai verificar na lista de restrições se existe alguma que mencione o nome do rectângulo a colocar; caso mencione e a restrição for validada ele vai inserir a restrição na stack.
 * Caso inicialmente o rectângulo não tenha sido encontrado, ele continua a procurar na lista de rectângulos.
 * @param 'L' Lista de rectângulos.
 * @param 'aux' Lista de rectângulos auxiliar.
 * @param 'R' Lista de restrições.
 * @param 'A' Lista de Áreas.
 * @param 'D' Dimensão.
 * @param 'S' Apontador para a Stack.
 * @param 'n' Nome do rectângulo.
 * @param 'x' Posição inicial do rectângulo no eixo dos x.
 * @param 'y' Posição inicial do rectângulo no eixo dos y.
 * @returns A função retorna '0' caso o rectângulo não seja colocado e '1' caso contrário. 
 */
int COLRaut (LRect L, LRect aux, LRestr R,LArea A , DIM D,Stack* S, char* n, int x, int y)
{
	int band= 1;
	if (strcmp(L->n,n)==0)/* Se encontrou rectangulo */
	{
		if (!L->r) /* Verifica se pode rodar */
		band=0;
		else
		{
			if (!(x >= 1 && y >= 1 && x+ L->y -1 <= D->x && y+ L->x -1 <= D->y )) /* Verifica se fica dentro da dimensao */
			band=0;
			else
			{
				if (sobreposto(aux,x,y,x+ L->y-1 ,y+ L->x-1, n)) /* Verifica se está sobreposto */
				band=0;
				else
				{
					if (vrestr (R,A,aux,n,x,y,x+ L->y -1,y+ L->x -1)) /* Verifica Restrição */
					band=0;			
					else
					{
						insStack (S,2,n,x,y,x+ L->y -1,y+ L->x -1); /* Insere Stack */
						L->x1 = x;
						L->y1 = y;
						L->x2 = x+ L->y -1;
						L->y2 = y+ L->x -1;
						L->c  = 1;		
					}
				}
			}
		}
	}
	else 
	{
		if (L->seg)
		{
			band = COLRaut(L->seg,aux,R,A,D,S,n,x,y); /* Continua a procurar o rectangulo que quer colocar */
		}
		else
		band=0;
	}
	return band;
}

/**
 * A funcao 'areatotal' é uma função auxiliar utilizada na função 'cRSV' do documento 'rect.c'. Esta função dá como resultado a soma de todas as áreas dos rectângulos presente na lista de rectângulos.
 * @param 'L' Lista de rectângulos.
 * @returns A função retorna a área total de todos os rectângulos. 
 */
int areatotal (LRect L)
{
	int res=0;
	
	while (L)
	{
		res = res + (L->x*L->y); /* Area do rectangulo + area dos anteriores */
		L=L->seg;
	}
	return res;
}

/**
 * A funcao 'areatotal' é uma função auxiliar utilizada na função 'cRSV' do documento 'rect.c'. Esta função procura na lista de restrições se existem algumas que se contradizem, ou seja, por exemplo, se existe alguma restrição 'DIR' e 'ESQ' com os mesmos argumentos.
 Isto verifica-se,também, para os comandos 'CIM' e 'BX', 'CLD' e 'SEP' e 'DENTRO' e 'FORA'.
 * @param 'R' Lista de restrições.
 * @returns A função retorna '1' caso não encontre restrições que se contradizem e '1' caso contrário. 
 */
int RSVrestr (LRestr R)
{
	LRestr aR=R, aaR=R;
	int n=0, band=1;
	char c1[15],c2[15];
	
	while (R && band == 1)
	{
		n = R->n;
		strcpy(R->c1,c1);
		strcpy(R->c2,c2);
		
		if (n==1) /*DIR*/
		{
			while (aR && band == 1)
			{
				if (aR->n==2 && (strcmp(aR->c1,c1)==0) && (strcmp(aR->c2,c2)==0)) /*PROCURA ESQ COM MESMOS PARAMETROS*/
				{
					band = 0;
				}
				aR=aR->seg;
			}
		}
		if (n==2) /*ESQ*/
		{
			while (aR && band == 1)
			{
				if (aR->n==1 && (strcmp(aR->c1,c1)==0) && (strcmp(aR->c2,c2)==0)) /*PROCURA DIR COM MESMOS PARAMETROS*/
				{
					band = 0;
				}
				aR=aR->seg;
			}
		}
		if (n==3) /*CIM*/
		{
			while (aR && band == 1)
			{
				if (aR->n==4 && (strcmp(aR->c1,c1)==0) && (strcmp(aR->c2,c2)==0)) /*PROCURA BX COM MESMOS PARAMETROS*/
				{
					band = 0;
				}
				aR=aR->seg;
			}
		}
		if (n==4) /*BX*/
		{
			while (aR && band == 1)
			{
				if (aR->n==3 && (strcmp(aR->c1,c1)==0) && (strcmp(aR->c2,c2)==0)) /*PROCURA CIM COM MESMOS PARAMETROS*/
				{
					band = 0;
				}
				aR=aR->seg;
			}
		}
		if (n==5) /*CLD*/
		{
			while (aR && band == 1)
			{
				if (aR->n==6 && (((strcmp(aR->c1,c1)==0) && (strcmp(aR->c2,c2)==0)) || 
								 ((strcmp(aR->c1,c2)==0) && (strcmp(aR->c2,c1)==0)))) /*PROCURA SEP COM MESMOS PARAMETROS*/
				{
					band = 0;
				}
				aR=aR->seg;
			}
		}
		if (n==6) /*SEP*/
		{
			while (aR && band == 1)
			{
				if (aR->n==5 && (((strcmp(aR->c1,c1)==0) && (strcmp(aR->c2,c2)==0)) || 
								 ((strcmp(aR->c1,c2)==0) && (strcmp(aR->c2,c1)==0)))) /*PROCURA CLD COM MESMOS PARAMETROS*/
				{
					band = 0;
				}
				aR=aR->seg;
			}
		}
		if (n==7) /*DENTRO*/
		{
			while (aR && band == 1)
			{
				if (aR->n==8 && ((strcmp(aR->c1,c1)==0) && (strcmp(aR->c2,c2)==0))) /*PROCURA FORA COM MESMOS PARAMETROS*/			 
				{
					band = 0;
				}
				aR=aR->seg;
			}
		}
		if (n==8) /*FORA*/
		{
			while (aR && band == 1)
			{
				if (aR->n==7 && ((strcmp(aR->c1,c1)==0) && (strcmp(aR->c2,c2)==0)))	/*PROCURA DENTRO COM MESMOS PARAMETROS*/		 
				{
					band = 0;
				}
				aR=aR->seg;
			}
		}
		R=R->seg;
		aR=aaR;
	}
	R=aaR;
	return band;
}

/**
 * A funcao 'cDESFaut' é uma função auxiliar utilizada na função 'cRSV' do documento 'rect.c'. Esta função verifica se, caso o último comando utilizado seja 'AREA' ou 'COL' ou 'COLR', este é eliminado.
 * Caso o último comando não seja nenhum destes, a função continua à procura na stack de um dos três comandos, que foi utilizado em último.
 * @param 'S' Apontador para a Stack.
 * @param 'A' Apontador para a lista de áreas.
 * @param 'L' Apontador para a lista de rectângulos.
 */
void cDESFaut (Stack* S, LArea* A, LRect* L)
{
	if (*S)
	{
		if ((*S)->t==3) /* Se ultimo comando for AREA */
		{
			retiraA (*A,(*S)->n); /* Retira Area */
		}
		else
		{ 
			if ((*S)->t>0)/* Se for COL ou COLR */
			{
				desfCOL (*L,((*S)->seg),(*S)->n); /* Desfaz COL */
			}
		}
		(*S)=(*S)->seg;
	}
}
