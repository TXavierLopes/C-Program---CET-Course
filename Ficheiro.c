//
//  Ficheiro.c
//  TF_Programação
//
//  Created by Marcel Carvalho on 01/04/14.
//  Copyright (c) 2014 Marcel Carvalho. All rights reserved.
//

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include "Informacao.h"
#include "Ficheiro.h"


/* Constantes */
#define kEquipamentos        "Equipamentos.txt"
#define kEquipamentosTemp    "Equipamentos.temp"

#define kLigacoes       "Ligacoes.txt"
#define kLigacoesTemp   "Ligacoes.temp"


/* Função Local */
static struct Ligacoes *LerEstruturaFicheiroLigacoes( FILE *fp );
static struct Equipamentos *LerEstruturaFicheiroEquipamentos( FILE *fpEquip );



/********************  TENTATIVE DE APAGAR ENTRADA
 
 
void ApagarEquipamento(void)
{
    
    struct Equipamentos	*infoApontador;
    char            buffer[ 500+1 ];

    printf("Apagar dados");
    char pc_id[15];
    //int procurado = 0;
    printf("Indinque o registo que quer guardar (os outros dados serao todos apagados) ");fflush(stdin);
    gets(pc_id);
    FILE *fp, *temporario;
    fp = fopen("arquivo.txt","rb");
    temporario = fopen("temporario.txt", "wb");
    while(fread(infoApontador->equipamentoTerminal, sizeof(buffer),1,fp) == 1){
        if(strcmp(pc_id, infoApontador->equipamentoTerminal) == 0){
            fwrite(infoApontador->equipamentoTerminal,sizeof(buffer),1,temporario);
        }
    }
    fclose(fp);
    fclose(temporario);
    remove("arquivo.txt");
    rename("temporario.txt","arquivo.txt");
    printf("Os dados foram bem apagados");
    return;
}


 
void ApagarEquipamento( void )         //Delete Staff Profile
{
    FILE *fRead, *fWrite;
    char c;
    int Delete_Id, temp = 1;
    
    fRead = fopen(kEquipamentosTemp, "r");
    c = getc(fRead);
    
    while (c != EOF){
        printf("%c", c);
        c = getc(fRead);
    }
    
    rewind(fRead);
    
    printf("\nDelete Staff with ID: ");
    scanf("%d", &Delete_Id);
    
    Delete_Id=Delete_Id+1;
    
    fWrite = fopen( kEquipamentos, "w");
    c = getc(fRead);
    while (c != EOF) {
        c = getc(fRead);
        if (c == '\n')
            temp++;
        if (temp != Delete_Id){
            putc(c, fWrite);
        }
    }
    
    fclose(fRead);
    fclose(fWrite);
    
    remove(kEquipamentos);
    
    rename("copy.c", kEquipamentos);
    printf("\nThe contents of file after being modified are as follows:\n");
    
    fRead = fopen(kEquipamentos, "r");
    c = getc(fRead);
    while (c != EOF) {
        printf("%c", c);
        c = getc(fRead);
    }
    
    fclose(fRead);
}


*********************/


/************************
 EscreverFicheiroEquipamentos() e EscreverFicheiroLigacoes()
 
 Escreve o conteudo dos ficheiros para ficheiros temporarios
 com a informação atual das listas com link para gInicioApontadorEquip e gInicioApontadorLiga

 Se tiver sucesso, substitui os ficheiros originais isto se
 já houver ficheiros com o novo
 */

void EscreverFicheiroEquipamentos( void ) // Função para guardar ficheiro Equipamentos.txt
{
	FILE			*fpEquip;
	struct Equipamentos	*infoApontador;
    int             error = 0;
	
    // Escreve o conteudo das estruturas para um ficheiro temporário
	fpEquip = fopen( kEquipamentosTemp, "w" );
    if ( fpEquip == NULL )
        error = errno;
    
    for ( infoApontador=gInicioApontadorEquip; infoApontador!=NULL && !error; infoApontador=infoApontador->proximoEquip ) {
        if (   fprintf( fpEquip, "%s\n", infoApontador->equipamentoTerminal ) < 0  ) {
            error = errno;
        }
    }
	
    if ( fpEquip != NULL ) {
        if ( fclose( fpEquip ) != 0 )
            error = errno;
    }
    
    if ( ! error ) {
        // Substitui o ficheiro original pelo temporário
        unlink( kEquipamentos );
        if ( rename( kEquipamentosTemp, kEquipamentos ) != 0 ) {
            error = errno;
            unlink( kEquipamentosTemp );
        }
        // Se rename() tiver sucesso, quer dizer que o ficheiro original
        // não existia ou o unlink() teve sucesso.
    }
    
    if ( error )
        fprintf( stderr, "Não deu para guardar ficheiro Equipamentos.txt: %s\n", strerror(error) );
}



void EscreverFicheiroLigacoes( void ) // Função para guardar ficheiro Ligações.txt
{
	FILE			*fp;
	struct Ligacoes	*infoApontadorLiga;
    int             error = 0;
	
    // Escreve o conteudo das estruturas para um ficheiro temporário
	fp = fopen( kLigacoesTemp, "w" );
    if ( fp == NULL )
        error = errno;
    
    for ( infoApontadorLiga=gInicioApontadorLiga; infoApontadorLiga!=NULL && !error; infoApontadorLiga=infoApontadorLiga->proximaLigacao ) {
        if (   fprintf( fp, "%s\n", infoApontadorLiga->descricao ) < 0
            || fprintf( fp, "%s\n", infoApontadorLiga->enderecoIP) < 0
            || fprintf( fp, "%s\n", infoApontadorLiga->switchs ) < 0
            || fprintf( fp, "%d\n", infoApontadorLiga->porta ) < 0 ) {
            error = errno;
        }
    }
	
    if ( fp != NULL ) {
        if ( fclose( fp ) != 0 )
            error = errno;
    }
    
    if ( ! error ) {
        // Substitui o ficheiro original pelo temporário
        unlink( kLigacoes );
        if ( rename( kLigacoesTemp, kLigacoes ) != 0 ) {
            error = errno;
            unlink( kLigacoesTemp );
        }
        // Se rename() tiver sucesso, quer dizer que o ficheiro original
        // não existia ou o unlink() teve sucesso.
    }
    
    if ( error )
        fprintf( stderr, "Não deu para guardar ficheiro Ligacoes.txt: %s\n", strerror(error) );
}



/**************************
 LerFicheiroEquipamentos() e LerFicheiroLigacoes()
 
 Abre os ficheiros e lê todo o conteudo
 
 Cada nova estrutura é feita link para as listas
 */

void LerFicheiroEquipamentos( void )
{
    FILE *fpEquip;
    
    if ( ( fpEquip = fopen( kEquipamentos, "r" ) ) == NULL ) {
        printf( "\nNão deu para abrir o ficheiro Equipamentos.txt!\n" );
        printf( "Ficheiro '%s' devia de estar em %s.\n(Irá criar novo ficheiro ao guardar)\n", kEquipamentos, getwd(NULL) );
        return;
    }
    
    struct Equipamentos *infoApontador;
    while ( ( infoApontador = LerEstruturaFicheiroEquipamentos( fpEquip ) ) != NULL ) {
        AddEquipamentos( infoApontador );
    }
    
    fclose( fpEquip );
}




void LerFicheiroLigacoes( void )
{
	FILE *fp;
	
	if ( ( fp = fopen( kLigacoes, "r" ) ) == NULL ) {
		printf( "\nNão deu para abrir o ficheiro Ligacoes.txt!\n" );
        printf( "Ficheiro '%s' devia de estar em %s.\n(Irá criar novo ficheiro ao guardar)\n", kLigacoes, getwd(NULL) );
		return;
	}
    
    struct Ligacoes *infoApontadorLiga;
    while ( ( infoApontadorLiga = LerEstruturaFicheiroLigacoes( fp ) ) != NULL ) {
        AddLigacoes( infoApontadorLiga );
    }
	
	fclose( fp );
}


/**************************
 LerEstruturaFicheirosEquipamentos ( FILE *fpequip) e LerEstruturaFicheiroLigacoes( FILE *fp )
 
 
 fp e fpEquip: Ficheiro para ler.
 
 Faz return do nova estrutura alocada se for com sucesso
 ou devolve NULL se EOF ou erro.

 */


static struct Equipamentos *LerEstruturaFicheiroEquipamentos( FILE *fpEquip )
{
    
    assert( fpEquip != NULL );       // Assume a valid fp pointer
    
    struct Equipamentos  *infoApontador;
    int             scanResultado;
    
    // Cria nova estrutura de Equipamento Terminal
    infoApontador = NovoEquipamento();
    
    scanResultado = fscanf( fpEquip, "%[^\n]\n", infoApontador->equipamentoTerminal );
    if ( scanResultado == 1 ) {
        
        return infoApontador;
    }
    
    
    if ( scanResultado != EOF ) {
        
        fprintf( stderr, "Data inválida perto do offset %lu, %d: %s\n",
                (long unsigned int)ftello(fpEquip),
                errno,
                strerror(errno) );
    }

    free( infoApontador );
    return NULL;
    
}


static struct Ligacoes *LerEstruturaFicheiroLigacoes( FILE *fp )
{
    assert( fp != NULL );       // Assume a valid fp pointer
    
    struct Ligacoes  *infoApontadorLiga;
    int             scanResultado;
    
    // Cria nova estrutura de Ligações
    infoApontadorLiga = NovaLigacao();

    scanResultado = fscanf( fp, "%[^\n]\n", infoApontadorLiga->descricao );
    if ( scanResultado == 1 ) {
        scanResultado = fscanf( fp, "%[^\n]\n", infoApontadorLiga->enderecoIP );
        if ( scanResultado == 1 ) {
            scanResultado = fscanf( fp, "%[^\n]\n", infoApontadorLiga->switchs );
            if ( scanResultado == 1 ) {
                int num;
                scanResultado = fscanf( fp, "%d\n", &num );
                if ( scanResultado == 1 ) {
                    infoApontadorLiga->porta = num;

                    return infoApontadorLiga;
                }
            }
        }
    }
    if ( scanResultado != EOF ) {

        fprintf( stderr, "Data inválida perto do offset %lu, %d: %s\n",
                (long unsigned int)ftello(fp),
                errno,
                strerror(errno) );
    }

    free( infoApontadorLiga );
    return NULL;
}
