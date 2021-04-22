//
//  Informacao.h
//  TF_Programação
//
//  Created by Marcel Carvalho on 01/04/14.
//  Copyright (c) 2014 Marcel Carvalho. All rights reserved.
//

#ifndef TF_Programac_a_o_Informacao_h
#define TF_Programac_a_o_Informacao_h

/**************/
/* definições */
/**************/
#define kMaxSwitch              256
#define kMaxDescricao           256
#define kMaxComprimentoEquip    256
#define kMaxEnderecoIP          256



/*****************************/
/* Declaração das Estruturas */
/*****************************/

struct Equipamentos //Estrutura somente para Equipamentos Terminais
{
    char                equipamentoTerminal[ kMaxComprimentoEquip ];
    struct Equipamentos *proximoEquip;
};

struct Ligacoes
{
	char			descricao[ kMaxDescricao ];
    char            enderecoIP[ kMaxEnderecoIP ];
	char			switchs[ kMaxSwitch ];
	char			porta;
	struct Ligacoes	*proximaLigacao;
};


/*****************************/
/* Funções Públicas/Externas */
/*****************************/

extern struct Equipamentos *LerEstrutura( void );
extern void AddEquipamentos( struct Equipamentos *ListarApontador );
extern struct Equipamentos *NovoEquipamento( void );


extern struct Ligacoes *LerEstruturaLigacoes( void );
extern void AddLigacoes( struct Ligacoes *ListarApontadorLigacoes );
extern struct Ligacoes *NovaLigacao( void );


extern void ListarEquipamentos( void );
extern void ListarLigacoes( void );

extern char *TrimLine( char *line );

/**********************/
/* Variáveis Públicas */
/**********************/

extern struct Ligacoes *gInicioApontadorLiga;
extern struct Equipamentos *gInicioApontadorEquip;

#endif
