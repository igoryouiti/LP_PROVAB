// Programa Escola de Natação - Prova B1 - 17/09/2014 - Turma da Tarde
//
#include "Escola.h"
//	Entry point do programa
//
void main(void)
{
	int nPeriodo,								// periodo da aula de natação
		nRaia,									// raia da piscina
		nQtdeRaiasDaPiscina,					// quantidade de raias da piscina
		nQtdeTotalDeRaias,						// qtde total de raias nos três períodos
		i, j;									// índices genéricos
	char cOpcao,								// opcao do operador
		cNomeAluno[] = "Igor Youiti Sato",
		cRA_Aluno[] = "1840481613004",
		cWork[200];								// para sprintf_s
	SYSTEMTIME stTime;							// para data e hora do sistema
	// vetores dos periodos e raias das piscinas
	bool vetRaiasLivres[QTDE_RAIAS_DA_PISCINA * QTDE_PERIODOS];	// vetor que indica se raia livre ou ocupada
												// true - indica ocupada e false indica livre
	char vetSobrenomes[QTDE_RAIAS_DA_PISCINA * QTDE_PERIODOS][TAMANHO_SOBRENOME];	// vetor de sobrenomes
	double vetMensalidades[QTDE_RAIAS_DA_PISCINA * QTDE_PERIODOS];	// vetor mensalidades
	// para duas casas decimais nos valores
	double dAuxiliar = 0;						//auxiliar double para somar a mensalidade
	setlocale(LC_ALL, "portuguese_brazil");		// para acentuação brasileira
	// <<<1>>> - Preencher as variáveis com seu nome e RA - OK
	// <<<2>>> - Fazer um loop indicando que todas as raias de todos os períodos estão desocupadas - OK
	
	i = 0;
	do
	{
		vetRaiasLivres[i] = false;
		i++;

	} while (i < QTDE_PERIODOS*QTDE_RAIAS_DA_PISCINA);
	
	//			 
	//			 Não se esquecer do seguinte:
	//				No período da manhã temos a raia 1 até Qtde de Raias da Piscina, no período da tarde de
	//				1 até a Qtde de Raias da Piscina, idem no período da noite.
	//
	//	Loop Infinito

	while(true)
	{
		LIMPAR_TELA;
		GetLocalTime(&stTime);						// data e hora do sistema
		sprintf_s(cWork, 
			"\tFATEC-Escola de Natação %02d/%02d/%04d às %02d:%02d:%02d\n\tOperador: %s Matrícula: %s",
			stTime.wDay, stTime.wMonth, stTime.wYear, 
			stTime.wHour, stTime.wMinute, stTime.wSecond,
			cNomeAluno, cRA_Aluno);
		cout << cWork << endl;
		// exibir o menu
		cout << MATRICULAR_ALUNO << " - Matricular aluno em um período desejado" << endl
			<< CANCELAR_MATRICULA << " - Cancelar a matrícula de um aluno" << endl
			<< LANCAR_DESPESA << " - Lançar despesas em um aluno matriculado" << endl
			<< LISTAR_PERIODO << " - Listar os alunos de um dado período" << endl
			<< SAIR_DO_PROGRAMA << " - Sair do programa" << endl
			<< "\tSelecione: ";
		cin  >> cOpcao;
		cOpcao = toupper(cOpcao);					// converte para maiúscula
		switch(cOpcao)								// avalia a opção escolhida
		{
			case MATRICULAR_ALUNO:
				// <<<5>>> - pedir um período válido (desejado pelo aluno) através da função  - OK
				//				BuscarPeriodo
				LIMPAR_TELA;

				if (BuscarPeriodo(&nPeriodo, QTDE_PERIODOS, &cOpcao) == false)
				{
					cout << "Cancelado" << endl;

					PAUSA;
					break;
				}
							
				// <<<6>>> - chamar a função que verifica se tem uma raia livre no 
				//			 período desejado e se não houver uma livre, esta função, devolve zero e
				//			 caso contrário, devolve o número da raia livre no período desejado
				//			 Se não houver uma raia livre cancelar esta ação de matricular aluno
				//				(volta ao menu principal) - OK

				nRaia = BuscarRaiaLivreNoPeriodo(vetRaiasLivres, nPeriodo, QTDE_RAIAS_DA_PISCINA);

				if (nRaia == 0)
				{
					cout << "Não há raias livres neste período.";
					PAUSA;
					break;
				}
					
				
				nRaia--;
				

				// <<<7>>> - pedir o sobrenome do aluno sendo matriculado.
				//			 verificar se existe o mesmo sobrenome nas raias ocupadas. Para
				//			 cada parente encontrado será dado um desconto de 10% limitado ao
				//			 máximo de 40%.
				//			 Assim: Se houver um só ou o primeiro aluno a mensalidade é cheia (100%); 
				//			  se houver mais um 10% de desconto, se houver
				//				mais um 20%; mais um 30% e apartir quarto todos terão 40% de desconto


				cout << "Insira o sobrenome do aluno que será matriculado: ";
				cin >> vetSobrenomes[nRaia];


				for (j = 0, i = 0; i < QTDE_PERIODOS*QTDE_RAIAS_DA_PISCINA; i++)
				{
					if (strcmp(vetSobrenomes[nRaia], vetSobrenomes[i]) == 0)
						j++;
					if (j == 5)
						break;
				}

				j--;
				
				cout << "Este aluno terá $" << j * VALOR_DESCONTO_POR_PARENTE << "% de desconto." << endl;

				PAUSA;

				// <<<8>>>	Associar este aluno ao período e à raia desejada (ocupar a raia com a bool true
				//			no vetor de livre/ocupada, sobrenome que está nesta raia, valor da mensalidade
				//			Indicar a raia e o período onde o aluno foi matriculado
				//			Dar uma pausa e
				//			Voltar ao menu 
				//

				LIMPAR_TELA;

				vetRaiasLivres[nRaia] = true;
			
					vetMensalidades[nRaia] = VALOR_MENSALIDADE - (VALOR_MENSALIDADE / VALOR_DESCONTO_POR_PARENTE) *j;
			
				
				
				cout << "Aluno/a: " << vetSobrenomes[nRaia] << endl << " Está matrículado na raia: "
					<< nRaia % QTDE_RAIAS_DA_PISCINA + 1 << " no período: " << nPeriodo << "." << endl
					<< "O valor de sua mensalidade é de: $" << vetMensalidades[nRaia] << ".\n";


				PAUSA;


				break;								// cai fora do switch
			case CANCELAR_MATRICULA:				
				// <<<9>>>  Chamar a função que pede o periodo e a raia indicando que a ação é
				//			Cancelamento de Matrícula
				LIMPAR_TELA;

				if(PedirPeriodoRaia(&nPeriodo, &nRaia, QTDE_PERIODOS, QTDE_RAIAS_DA_PISCINA, &cOpcao) == false)
					break;




				// <<<10>>> Verificar se a raia está ocupada e se estiver livre avisar ao operador e
				//			cancelar está ação voltando ao menu
				//			Se a raia estiver ocupada exibir o sobrenome, valor da matrícula

				

				if (vetRaiasLivres[nRaia + (nPeriodo*QTDE_RAIAS_DA_PISCINA - QTDE_RAIAS_DA_PISCINA) - 1] == false)
				{
					cout << "A raia selecionada está vazia." << endl << endl << "Cancelando - " << cOpcao
						<< " - Cancelamento de Matrícula." << endl;
					PAUSA;
					break;
				}
				cout << "O aluno/a: " << vetSobrenomes[nRaia + (nPeriodo*QTDE_RAIAS_DA_PISCINA - QTDE_RAIAS_DA_PISCINA) - 1]
					<< " está ocupando a raia " << nRaia << " do período " << nPeriodo << ". \n"
					<< "Sua matrícula é no valor de $" << vetMensalidades[nRaia + (nPeriodo*QTDE_RAIAS_DA_PISCINA - QTDE_RAIAS_DA_PISCINA) - 1]
					<< ".\n";

				
				// <<<11>>> Pedir a confirmação do cancelamento da matrícula e havendo a confirmação
				//			apenas indicar que esta raia deste periodo está livre. Caso contrário
				//			voltar ao menu principal

				cout << "Gostaria de cancelar está matrícula? (S ou N)";

					do
					{
						cout << "Insira uma opção válida: ";
						cin >> cOpcao;
							cOpcao = toupper(cOpcao);
					} while (cOpcao != 'S' && cOpcao != 'N');

					if (cOpcao == 'S')
					{
						vetRaiasLivres[nRaia + (nPeriodo*QTDE_RAIAS_DA_PISCINA - QTDE_RAIAS_DA_PISCINA) - 1] = false;
						cout << "A raia " << nRaia << " do período " << nPeriodo << " está livre. \n";
						PAUSA;
						break;
					}
					cout << "Ação cancelada.";
				PAUSA;									
				break;								// cai fora do switch
			case LANCAR_DESPESA:
				// Não codificar ????????????????????????????????????????????
				// <<<12>>> Chamar a função que pede o periodo e a raia indicando que a ação é
				//			Lançamento de Despesa
				// <<<13>>> Verificar se a raia está ocupada e se estiver livre avisar ao operador e
				//			cancelar está ação voltando ao menu
				// <<<14>>> Se a raia estiver ocupada exibir o Sobrenome e as despesas até o momento
				//			Pedir o valor da despesa
				//			Somar o valor informado às despesas anteriores deste aluno
				//			Voltar ao menu
				break;								// cai fora do switch
			case LISTAR_PERIODO:				
				// <<<15>>> Pedir um período válido ou zero para cancelar a ação de listar
				//			Se foi informado um período válido listar todos as raias ocupadas
				//			no seguinte formato:
				//				Listagem das raias do periodo: ppppppp
				//			Raia Sobrenome  Mensalidade 
				//			 RR  SSSSSSSSS  MMMMMM,MM	
				//			.....
				//			.....
				//					       Total Mensalidades: TTTTTT,TT
				//			Onde: PPPPPPP - periodo: "Manhã", "Tarde" ou "Noite"
				//				  RR - raia ocupada ( 1 a Qtde de Raias da Piscina)
				//				  SSSSSSSSS - sobrenome do aluno
				//				  MMMMM - valor da mensalidade
				//				  TTTTTT,TT - valor total de todas as mensalidades

				if (BuscarPeriodo(&nPeriodo, QTDE_PERIODOS, &cOpcao) == true)
				{
					cout << "\tListagem das raias do período: " << nPeriodo <<endl <<"Raia   Sobrenome   Mensalidade" << endl;

					
					for (i = nPeriodo*QTDE_RAIAS_DA_PISCINA - QTDE_RAIAS_DA_PISCINA; i < nPeriodo*QTDE_RAIAS_DA_PISCINA; i++)
					{
						if (vetRaiasLivres[i] == true)
						{
							nRaia = i - (nPeriodo*QTDE_RAIAS_DA_PISCINA - QTDE_RAIAS_DA_PISCINA) + 1;
							sprintf_s(cWork, sizeof(cWork), "%2d	%-6s	    %6.2f", nRaia, vetSobrenomes[i], vetMensalidades[i]);
							cout << cWork << endl << endl;
							dAuxiliar = dAuxiliar + vetMensalidades[i];
						
						}
					}
					cout << "Valor total de todas as mensalidades: \n" << dAuxiliar << endl;
				}

								
				//	<<<16>>> Pausa para visualização e voltar ao menu
				PAUSA;
				break;								// cai fora do switch
			case SAIR_DO_PROGRAMA:					
				cout << "Vai sair realmente? (S ou N): ";
				cin >> cOpcao;
				if(cOpcao == 's' || cOpcao == 'S')	// sair realmente?
					return;			
				break;								// cai fora do switch
			default:
				cout << "Opção inválida!" << endl;
				PAUSA;
		} // switch
	} // while
} // main
// 
// Funções do Programa
//
// Função que pede um período válido e uma raia da piscina válida
// Parâmetros:
//	Entrada: int *ptrPeriodo - ponteiro para receber o período desejado
//			 int *ptrRaia - ponteiro para receber a raia da piscina desejada
//			 int nQtdePeriodos - quantidade de períodos da Escola de Natação
//			 int nQtRaiasPiscina - quantidade de raias que tem a piscina da Escola de Natação
//			 char *ptrAcao - ponteiro de um string que contém a ação que está sendo executada
//	Retorno: bool - true - indica que foi informado um período e uma raia válidos
//					false - indica que o operador desistiu da ação que iria executar
//							digitando periodo zero
bool PedirPeriodoRaia(int *ptrPeriodo, int *ptrRaia, 
					  int nQtdePeriodos, int nQtRaiasPiscina, char *ptrAcao)
{

	int i;

	cout << *ptrAcao << " - Cancelamento de matrícula" << endl << endl
		<< PERIODO_MANHA << " - para periodo da manhã" << endl
		<< PERIODO_TARDE << " - para periodo da tarde" << endl
		<< PERIODO_NOITE << " - para periodo da noite" << endl
		<< "0" << " - para voltar" << endl;
	do
	{
		cout << "Insira o período desejado: ";
		cin >> *ptrPeriodo;
	} while (*ptrPeriodo < 0 || *ptrPeriodo > PERIODO_NOITE);
	if (*ptrPeriodo == 0)
		return false;

	
	cout << endl << "Insira uma raia válida de 1 a " << QTDE_RAIAS_DA_PISCINA << " do período " 
		<< *ptrPeriodo << ", ou 0 para voltar: ";

	do
	{
		cin >> *ptrRaia;

	} while (*ptrRaia < 0 || *ptrRaia > 10);

	if (*ptrRaia == 0)
		return false;


	return true;							// ???? para não dar erro de compilação
}


//
// Função que verifica se tem uma raia livre no período desejado
//	Parâmetros:
//		Entrada: bool *ptrVetLivreOcup - ponteiro do vetor de bool que indica se a raia está 
//										 livre ou ocupada
//				 int nPeriodo - período desejado
//				 int nQtRaiasPiscina - quantidade de raia que a piscina te´m
//		Retorno: int - Número da raia que está livre ou zero se não existir nenhuma
//						raia livre no período desejado
int BuscarRaiaLivreNoPeriodo(bool *ptrVetLivreOcup, int nPeriodo, int nQtRaiasPiscina)
{
	int i;
	
	for (i = nPeriodo*nQtRaiasPiscina - nQtRaiasPiscina; i < nPeriodo*nQtRaiasPiscina; i++)
	{
		if (!*(ptrVetLivreOcup + i))
			return i + 1;
	}
	
		
	return 0;							// ???? para não dar erro de compilação
}



// Parâmetros:
//	Entrada: int *ptrPeriodo - endereço de uma inteira que receberá o periodo desejado
//			 int nQtdePeriodos - quantidade de periodos
//			 char *ptrAcao - ponteiro de um string que contém a ação em execução
//	Retorno: bool - true - foi indicado um período válido
//					false - foi indicado um periodo zero que indica cancelar a ação desejada
bool BuscarPeriodo(int *ptrPeriodo, int nQtdePeriodos, char *ptrAcao)
{
	
		LIMPAR_TELA;

		cout << "Opção - " << *ptrAcao << endl << endl;

	cout << endl << PERIODO_MANHA << " - para periodo da manhã" << endl
		<< PERIODO_TARDE << " - para periodo da tarde" << endl
		<< PERIODO_NOITE << " - para periodo da noite" << endl
		<< "0" << " - para voltar" << endl;
	do
	{
		cout << "Insira o período desejado: ";
		cin >> *ptrPeriodo;
	} while (*ptrPeriodo < 0 || *ptrPeriodo > PERIODO_NOITE);
	if(*ptrPeriodo == 0)
		return false;
	else
		return true;
}
