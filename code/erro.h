#define E_NOERR		 0	/**              Tudo normal             **/
#define E_COMANDO	 1	/**          Comando nao existe          **/
#define E_ARGS		 2	/** Erro de argumentos a mais ou a menos **/
#define E_NO_DIM	 3	/**   A area ainda nao foi inicializada  **/
#define E_DIM		 4	/**          Erro de dimensoes           **/
#define E_NAO_EXISTE 5	/**              Nao existe              **/
#define E_JA_EXISTE	 6	/**              Ja existe               **/
#define E_COL		 7	/**       Rectangulo nao colocado        **/
#define E_ROD		 8	/**      Rectangulo nao pode rodar       **/
#define E_FORA		 9	/**              Colocado fora           **/
#define E_SOBREP	10	/**   Rectangulo sobreposto a outro      **/
#define E_INVARGS	11	/**        Argumentos invalidos          **/
#define E_RESTR		12	/**       Violacao de restricoes         **/
#define E_NOSOL		13	/**            Nao ha solucao            **/

/**
* Reporta o erro escrevendo uma mensagem no standard error
* @param erro_num O número do erro que vem da tabela de erros. Usar SEMPRE o define e não o valor numérico para maior legibilidade.
*/
int mensagem_de_erro(int erro_num);
