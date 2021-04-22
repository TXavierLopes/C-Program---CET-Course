//
//  main.c
//  TF_Programação
//
//  Created by Marcel Carvalho on 01/04/14.
//  Copyright (c) 2014 Marcel Carvalho. All rights reserved.
//

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <pwd.h>        // getpwuid()
#include <unistd.h>     // getuid()
#include "Informacao.h"
#include "Ficheiro.h"


#define kComandoGuardar         '5'
#define kComandoListarLigacoes  '4'
#define kComandoListarEquip     '3'
#define kApagarEntrada          '2'
#define kComandoNovo            '1'
#define kComandoSair            '0'


/*********************************************************************************************************************
 
 -- Falta no menu, ver se meto mais apelativo (Xavier) [DONE]
 -- Falta adicionar "Lista Simples" e "Lista Completa", logo alterar o "kComandoListar" que tenho para um dos anteriores e adicionar o outro que falta.
 -- Código para guardar nos ficheiros que o prof pediu, e mais outro caso seja nessesário.
 -- Chamar (código para ler) para "Listar Simples" os ficheiros necessários e para "Listar Completo" todos, devidamente organizados (procurar o código da percentagem para criar espeaçamentos
 -- No caso de adicionar, ver bem que função guardará em que ficheiro, ver que coisas são necessárias o utilizador fazer input no programa.
 -- Coisas a INSERIR:
 --     Equipamento Terminal (Listar Simples) 256
 --     Descrição 256
 --     Endereço IP 256
 --     Switch (Listar Simples)
 --     Porta no Switch (Listar Simples) (Dar dica para instroduzir em formato "Fa0/X")
 -- Ver se é preciso haver uma opção para editar as entradas a pedido do utilizador
 
 *********************************************************************************************************************/

int Menu(void)
{
    printf("            ********************************************\n");
    printf("            *                                          *\n");
    printf("            *      1-Criar nova entrada                *\n");
    printf("            *        2-Apagar entrada (ñ funciona)     *\n");
    printf("            *       3-Listar Equipamentos              *\n");
    printf("            *       4-Listar Ligações                  *\n");
    printf("            *       5-Guardar Ficheiros                *\n");
    printf("            *        0-Sair e Guardar                  *\n");
    printf("            *                                          *\n");
    printf("            ********************************************\n");
    printf("\n >> Qual é a opção: ");
    return 0;
}


char AdquirirComando( char *prompt );
int definirPastaGuardar( void );


int main (int argc, const char * argv[])
{
    system("clear"); //Limpar logo seja o que estiver na janela do terminal
    
    // define a pasta onde vai guardar os ficheiros para "Ambiente de Trabalho"/"Desktop"
    if ( definirPastaGuardar() != 0
        || chdir( "./Desktop" ) != 0 ) {
        perror( "Não deu para 'chdir' para o ~/Desktop" );
        exit( 1 );
    }
	
    LerFicheiroLigacoes();
    LerFicheiroEquipamentos();
	
	char comando;
	while ( (comando = AdquirirComando( Menu()) ) != kComandoSair ) {
		switch( comando ) {
			case kComandoNovo:
                AddEquipamentos(LerEstrutura());
				AddLigacoes( LerEstruturaLigacoes() );
                printf("\n\n >> Dados Adicionados com sucesso");
				break;
            case kApagarEntrada: // NÃO FUNCIONA
                //ApagarEquipamento();
                break;
			case kComandoListarEquip: // NÃO FUNCIONA
                ListarEquipamentos();
				break;
            case kComandoListarLigacoes:
                ListarLigacoes();
                break;
            case kComandoGuardar:
                EscreverFicheiroEquipamentos();
                EscreverFicheiroLigacoes();
                break;
		}
        printf( "\n----------\n" );
	}
	
    EscreverFicheiroEquipamentos();
	EscreverFicheiroLigacoes();
	
	printf( "A sair do programa e guardar os ficheiros, aguarde...\n" );
	
	return 0;
}


/*****************
 AdquirirComando()
 
 Função para ler um único caracter do comando para
 stdin e devolve o resultado como um carater para o
 chamador, ou faz kComandoSair se achar um erro.

 */
char AdquirirComando( char *prompt )
{
    char buffer[ 100+1 ];
    if ( fgets( buffer, sizeof(buffer), stdin ) == NULL )
        return kComandoSair;
    return *TrimLine( buffer );
}

/*******************************
 definirPastaGuardar()
 
 Retorna 0 se tiver sucesso.
 Define a área de trabalho para a pasta ambiente de trabalho do utilizador atual.
 
 */
int definirPastaGuardar( void )
{
    struct passwd *pw = getpwuid( getuid() );
    assert( pw!=NULL );     // verifica se o utilizador atual é válido
    return chdir( pw->pw_dir );
}
