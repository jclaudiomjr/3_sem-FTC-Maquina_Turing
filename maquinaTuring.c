#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define t 10

void moverCabeca(int _posicaoCabeca, int _estadoAtual, int _elementoAtual, char *_moverCabeca[][t])
{
	if (_moverCabeca[_estadoAtual][_elementoAtual] == '>')
		*_posicaoCabeca++;
	else
		*_posicaoCabeca--;
}

void gravarElemento(char *_palavra, int _posicaoCabeca, int _estadoAtual, int _elementoAtual, char *_gravarElemento)
{
	_palavra[_posicaoCabeca] = _gravarElemento[_estadoAtual][_elementoAtual];
}

void alterarEstado(int *_estadoAtual, int _elementoAtual, int *_novoEstado)
{
	*_estadoAtual = _novoEstado[_estadoAtual][_elementoAtual];
}

int procurarElemento(char *_palavra, int _posicaoCabeca, char *_alfabeto)
{
	int i;
	
	for (i=0 ; i < strlen(palavra); i++)
		if (_palavra[_posicaoCabeca] == _alfabeto[i])
			return (i);
		else
			return (-1)
}

int verificarFalso(int _estadoAtual, int _elementoAtual, char *_gravarElemento)
{
	if (_gravarElemento[_estadoAtual][_elementoAtual] == 'F')
		return (1);
	else
		return (0);
}

void inicializarTabela(char *_gravarElemento)
{
	int i, j;
	
	for (i=0 ; i < t; i++)
		for (j=0 ; j < t ; t++)
			_gravarElemento[i][j]='F';
}

int reconhecerPalavra(char *_palavra, int *_estadoFinal, int _qtTrans, int _qtEstadoFinal, char *_alfabeto, char *_gravarElemento, char *_moverCabeca, int *_novoEstado)
{
	int posicaoCabeca=0, j, estadoAtual, elementoAtual;
	int flag=0;
	
	for (estadoAtual=0 ; ;)
	{
		/*Vai mostrando as mudancas na fita*/
		puts(_palavra);
		printf("\n");
		
		/*Verifica qual eh o elemento atual, que marca as colunas da tabela (das matrizes)*/
		elementoAtual = procurarElemento(_palavra, posicaoCabeca, _alfabeto);
		
		/*Caso elementoAtual seja == -1, significa que a letra na fita nao pertence ao alfabeto informado*/
		if (elementoAtual == -1)
			flag=2;
		
		/*Verifica se existe ou nao uma transicao no estado atual lido o elemento atual*/
		if (verificarFalso(estadoAtual, elementoAtual, _gravarElemento))
			flag=2;
		
		gravarElemento(_palavra, posicaoCabeca, estadoAtual, elementoAtual, _gravarElemento);
		moverCabeca(&posicaoCabeca, estadoAtual, elementoAtual, _moverCabeca);
		alterarEstado(&estadoAtual, elementoAtual, _novoEstado);
		
		/*Se for lido um elemento vazio (B) na fita em um estado final, ativa a flag, significando que o processo de reconhecimento acabou*/
		for (j=0; j <  _qtEstadoFinal ; j++)
			if (estadoAtual == _estadoFinal[j])
				if (_palavra[posicaoCabeca] == 'B')
				{
					flag=1;
					break;
				}
				
		/*flag==1, tudo ok, acaba o processo de reconhecimento*/
		if (flag == 1)
		{
			puts(_palavra);
			printf("\n");
			return (1);
		}
		/*flag==2, alguma coisa aconteceu de errado, a palavra nao eh reconhecida*/
		else if (flag == 2)
			return (0);
	}
}

int main()
{
	int rmkPalavra, rmkRegra, qtEstado, qtTrans, qtEstadoFinal, i, *estadoFinal, novoEstado[t][t];
	char alfabeto[t], palavra[50], gravarElemento[t][t], moverCabeca[t][t];
	
	for (;;)
	{
		inicializarTabela(gravarElemento, moverCabeca, novoEstado);
		
		printf("Informe o alfabeto, mais o elemento vazio (B) no final: FORMATO: abcB\n");
		gets(alfabeto);
		fflush(stdin);
		
		printf("Informe a quantidade de estados:\n");
		scanf("%d", &qtEstado);
		
		/*printf("Informe a quantidade de transições:\n");
		scanf("%d", &qtTrans);*/

		printf("Informe a quantidade de estados finais:\n");
		scanf("%d", &qtEstadoFinal);
		
		printf("Informe os estados finais:\n");
		/*Alocacao dinamica de um vetor para armezenar os estados finais de acordo com a quantidade de estados finais*/
		estadoFinal = (int *) malloc(sizeof(int)*qtEstadoFinal);
		for (i=0 ; i < qtEstadoFinal ; i++)
			scanf("%d", &estadoFinal[i]);
		
		/*Informar as transicoes da gramatica*/
		for (i=0 ; i < qtEstado ; i++)
			for (x=0 ; x < strlen(alfabeto); x++)
			{
				printf("No estado %d lendo o elemento %c: FORMATO: a>1 (Grava o elemento 'a', move para direita e vai para o estado 1.)\n", i, alfabeto[x]);
				scanf("%c%c%d", &gravarElemento[i][x], &moverCabeca[i][x], novoEstado[i][x]);
				fflush(stdin);
			}
			
		for (;;)
		{
			printf("Informe a palavra que se deseja reconhecer:\n");
			gets(palavra);
			fflush(stdin);
			
			if (reconhecerPalavra(palavra, estadoFinal, qtTrans, qtEstadoFinal, alfabeto, gravarElemento, moverCabeca, novoEstado))
				printf("Palavra reconhecida por essa MT!\n");
			else
				printf("Palavra nao reconhecida por essa MT...\n");
			
			/*Escolher outra palavra para reconhecer*/
			printf("Deseja reconhecer outra palavra? (0 nao, 1 sim)\n");
			scanf("%d", &rmkPalavra);
			if (rmkPalavra)
				continue;
			else
				break;
		}
		
		free(estadoFinal);
		
		/*Recomecar o programa*/
		printf("Deseja inserir novas regras na maquina?\n (0 nao, 1 sim)");
		scanf("%d", &rmkRegra);
		if (rmkRegra)
			continue;
		else
			break;
	}
	
 return 0;
}
