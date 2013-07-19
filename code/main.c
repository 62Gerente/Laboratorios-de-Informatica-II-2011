/**
 * @file main.c
 * @brief Funcao principal do programa
 * @author André Santos, Helena Alves, Pedro Faria
 * @date 18 de Maio de 2011
 */

#include "rect.c"
#include "Estruturas.h"

/**
 * Funcao principal do programa, responsável por interpretar os comandos e executar a sua respectiva função.
 */
 
int main()
{
	char command[10], params[20], comando[30];

	LRect L = NULL;
	LArea A = NULL;	
	LRestr R = NULL;
	Stack S = NULL;
	DIM D = NULL; 
	L = (LRect) malloc (sizeof (NodoR));
	A = (LArea) malloc (sizeof (NodoA));
	R = (LRestr) malloc (sizeof (NodoRestr));
	S = (Stack) malloc (sizeof (NStack));	
	D = (DIM) malloc (sizeof (struct sDIM));
	
	
	while (fgets(comando, 30, stdin) != NULL)
		{
			sscanf(comando, "%s %[^\n]", command, params);
			
			if (strcmp(command,"DIM")==0)
			cDIM(params,D);
			
			else  if (strcmp(command,"RECT")==0)
				  cRECT(params,L,D);
		          
		          else  if (strcmp(command,"COL")==0)				  
					    cCOL(params,L,A,D,R,&S);
					    
					    else  if (strcmp(command,"DIR")==0)				  
					    cDIR(params,L,R);
					    
								else  if (strcmp(command,"ESQ")==0)				  
								cESQ(params,L,R);
					    
										else  if (strcmp(command,"CIM")==0)				  
										cCIM(params,L,R);
					    
												else  if (strcmp(command,"BX")==0)				  
												cBX(params,L,R);
					
														else  if (strcmp(command,"COLR")==0)				  
														cCOLR(params,L,A,D,R,&S);
														
															  else  if (strcmp(command,"CLD")==0)				  
															  cCLD(params,L,R);
																	 else  if (strcmp(command,"SEP")==0)				  
																	 cSEP(params,L,R);
																	
																			else  if (strcmp(command,"AREA")==0)				  
																		    cAREA(params,A,D,&S);
																					
																				  else  if (strcmp(command,"DENTRO")==0)				  
																						cDENTRO(params,L,R,A,D);
																
																						else  if (strcmp(command,"FORA")==0)				  
																							  cFORA(params,L,R,A,D);
																			
																							  else if (strcmp(command,"ESTADO")==0)
																								   cESTADO(L);
																								   else if (strcmp(command,"DESF")==0)
																								   cDESF(&S,&A,&L);					
																								   else if (strcmp(command,"RSV")==0)
																								   {
																										if(cRSV(L,L,R,R,A,D,&S,0))
																										printf ("SIM\n");
																										else
																										printf ("NAO\n");
																										mensagem_de_erro (13);
																									}																												   								  
								
																				else mensagem_de_erro (1);					 
		}
	return 0;
       
}
