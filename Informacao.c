//
//  Informacao.c
//  TF_Programação
//
//  Created by Marcel Carvalho on 01/04/14.
//  Copyright (c) 2014 Marcel Carvalho. All rights reserved.
//

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <pwd.h>        // getpwuid()
#include <unistd.h>     // getuid()
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "Informacao.h"


/* Global Variables */
struct Ligacoes *gInicioApontadorLiga;
static struct Ligacoes *gFimApontadorLiga;

struct Equipamentos *gInicioApontadorEquip;
static struct Equipamentos *gFimApontadorEquip;



struct Equipamentos *LerEstrutura( void )
{
    
    struct Equipamentos *infoApontador;
    
    bool            infoBoa;
    char            buffer[ 500+1 ];
	
	infoApontador = NovoEquipamento();
	system("clear");
	printf( "\nInserir nome do Equipamento Terminal:  " );
    infoBoa = ( fgets( buffer, sizeof(buffer), stdin ) != NULL );
    if ( infoBoa ) {
        strlcpy( infoApontador->equipamentoTerminal, TrimLine( buffer ), sizeof(infoApontador->equipamentoTerminal) );
        
        if ( ! infoBoa ) {
            free( infoApontador );
            infoApontador = NULL;
        }
    }
    
	return( infoApontador );
}


struct Ligacoes *LerEstruturaLigacoes( void )
{
	struct Ligacoes  *infoApontadorLiga;
    
    bool            infoAceitavel;
    char            buffer[ 500+1 ];
	
	infoApontadorLiga = NovaLigacao();
	
	printf( "Inserir descrição:  " );
    infoAceitavel = ( fgets( buffer, sizeof(buffer), stdin ) != NULL );
    if ( infoAceitavel ) {
        strlcpy( infoApontadorLiga->descricao, TrimLine( buffer ), sizeof(infoApontadorLiga->descricao) );
        
        printf( "Inserir Endereço IP:  " );
        infoAceitavel = ( fgets( buffer, sizeof(buffer), stdin ) != NULL );
    }
    if ( infoAceitavel ) {
        strlcpy( infoApontadorLiga->enderecoIP, TrimLine( buffer ), sizeof(infoApontadorLiga->enderecoIP) );
        
        printf( "Inserir Switch:  " );
        infoAceitavel = ( fgets( buffer, sizeof(buffer), stdin ) != NULL );
    }
    if ( infoAceitavel ) {
        strlcpy( infoApontadorLiga->switchs, TrimLine( buffer ), sizeof(infoApontadorLiga->switchs) );
        
        int num;
        do {
            printf( "Inserir número da porta no Switch:  Fa0/" );
            infoAceitavel = ( fgets( buffer, sizeof(buffer), stdin ) != NULL );
            num = atoi( TrimLine( buffer ) );
        }
        while ( ( num < 1) || ( num > 25) || ! infoAceitavel );
        infoApontadorLiga->porta= num;
        
    }
    
    if ( ! infoAceitavel ) {
        free( infoApontadorLiga );
        infoApontadorLiga = NULL;
    }
    
	return( infoApontadorLiga );
}



void AddLigacoes( struct Ligacoes *ListarApontadorLigacoes )
{
    if ( gInicioApontadorLiga == NULL )
        gInicioApontadorLiga = ListarApontadorLigacoes;
    else
        gFimApontadorLiga->proximaLigacao = ListarApontadorLigacoes;
    
    ListarApontadorLigacoes->proximaLigacao = NULL;
    gFimApontadorLiga = ListarApontadorLigacoes;
}


void AddEquipamentos( struct Equipamentos *ListarApontador )
{
	if ( gInicioApontadorEquip == NULL )
		gInicioApontadorEquip = ListarApontador;          // Primeira struct na lista
	else
		gFimApontadorEquip->proximoEquip = ListarApontador;    // Adiciona ao fim da lista
    
	ListarApontador->proximoEquip = NULL;
	gFimApontadorEquip = ListarApontador;
}

/*****************
 ListarEquipamentos() e ListarLigacoes()

 Funções para fazer print dos dados nos ficheiros/estruturas
 */
void ListarEquipamentos( void )
{
	
    struct Equipamentos *ListarApontador;
	
	if ( gInicioApontadorEquip == NULL ) {
		printf( "Ainda não foram inseridos dados...\n" );
    }else {
        
        
		for ( ListarApontador = gInicioApontadorEquip; ListarApontador != NULL; ListarApontador = ListarApontador->proximoEquip ) {
            if ( ListarApontador != gInicioApontadorEquip )
                printf( "--------\n" );
            
			printf( "\nEquipamento Terminal:   %s  \n", ListarApontador->equipamentoTerminal );
            
		}
	}
    
}

void ListarLigacoes( void )
{
	struct Ligacoes *ListarApontadorLigacoes;
	
    
    if ( gInicioApontadorLiga == NULL ) {
		printf( "Ainda não foram inseridos dados...\n" );
        
	} else {
		for ( ListarApontadorLigacoes = gInicioApontadorLiga; ListarApontadorLigacoes != NULL; ListarApontadorLigacoes = ListarApontadorLigacoes->proximaLigacao ) {
            if ( ListarApontadorLigacoes != gInicioApontadorLiga )
                printf( "--------\n" );
            
            printf( "\nDescrição:     %s \n", ListarApontadorLigacoes->descricao );
            printf( "Endereço IP:   %s \n", ListarApontadorLigacoes->enderecoIP );
			printf( "Switch:        %s \n", ListarApontadorLigacoes->switchs );
			printf( "Porta:         Fa0/%d \n", ListarApontadorLigacoes->porta );
		}
	}
    
}


/******************
 
 Devolve apontadores para estrutura de ligações
 e de equipamentos
 
 */
struct Ligacoes *NovaLigacao( void )
{
    struct Ligacoes *novoApontadorLigacoes;
    
    novoApontadorLigacoes = calloc( 1, sizeof( struct Ligacoes ) );
    if ( novoApontadorLigacoes==NULL ) {
        fprintf( stderr, "Out of memory!\n" );
        exit( 1 );
    }
    
    return novoApontadorLigacoes;
}


struct Equipamentos *NovoEquipamento(void)
{
    struct Equipamentos *NovoApontador;
    
    NovoApontador = calloc( 1, sizeof( struct Equipamentos ) );
    if ( NovoApontador==NULL ) {
        fprintf( stderr, "Out of memory!\n" );
        exit( 1 );
    }
    return NovoApontador;
}

/***************************************************
 TrimLine( char *line )

 Substitui qualquer espaço em branco ao fim
 da linha com '\0'
 
 Salta qualquer espaço em branco no início da string
 dando de volta um pontador para o primeiro caratar 
 após espaço em branco

 */
char *TrimLine( char *line )
{
    
    // Verifica se o último caracter na string é
    // espaço em branco. Se sim, substitui por "\0"
    // e repete.
    size_t length = strlen( line );
    while ( length > 0 && isspace( line[length-1] )) {
        line[length-1] = '\0';
        length--;       // A string é agora um caracter mais curto
    }
    
    char *head = line;
    while ( isspace( *head ) )
        head++;
    
    return head;
};


