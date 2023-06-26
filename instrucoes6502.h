#ifndef instrucoes6502
#define instrucoes6502
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <ncurses.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>
#include <string.h>

WINDOW *EntradaInfo;
int yborda, xborda;

char *logopt1 = " _                __  _  _ __ \n";
char *logopt2 = "|_) o  _  _ |_     _)|_|/ \\__)\n";
char *logopt3 = "| \\ | (_ (_)| |   /__| |\\_/__)\n";

char StringAux[20];

typedef struct {

    bool carry;
    bool zero;
    bool interruptDisable;
    bool decimalMode;
    bool breakCommand;
    bool overflow;

} Flags;

typedef struct {

    Flags flags;
    uint8_t acumulador;  //valores iniciais para os registradores
    uint8_t indicex;
    uint8_t indicey;
    uint8_t stackpointer;
    uint8_t statusregister;
    uint16_t programcounter;
    bool carry; //TRUE = 1, FALSE = 0
    uint8_t ram[2048];

} Processador;

uint8_t addressBus; //variavel responsavel por transferir endereços de memória, quando necessário em instruções de acesso a memória

// As variáveis que não possuirem o formato uintX_t são aquelas que representam as instruções com opcodes de 3 bytes
// Os opcodes no NES podem variar entre 1 a 3 bytes

// INSTRUÇÕES DA ULA
uint8_t ADC = 0x65;  //ADC, adiciona o acumulador a algum outro registrador. Instrução de 2 bytes
uint8_t ADChash = 0x69; //ADC#, adiciona imediato ao acumulador. Instrução de 2 bytes
uint8_t SBChash = 0xE9;  //SBC#, subtrai o acumulador por um imediato. Instrução de 2 bytes
uint8_t ANDY = 0x39;  //ANDY, realiza operação lógica AND entr eo acumulador e o índice Y. Instrução de 3 bytes
uint8_t ORAX = 0x1D;  //ORAX, realiza operação lógica OR entre o acumulador e o índice X. Instrução de 3 bytes
uint8_t EORX = 0x5D;  //EORX, realiza operação lógica XOR entre o acumulador e o índice X. Instrução de 3 bytes
//não possui instrução nor nativa
//não possui instrução slt nativa
//não possui instrução sll nativa
uint8_t ASL = 0x0E; //ASL (arithmetic shift left), realiza a operação de shift, deslocando os bits do acumulador para a esquerda e preenchendo o bit mais à direita com 0. Instrução de 1 byte
uint8_t LSR = 0x4A;  //LSR (shift pra direita). Instrução de 1 byte
uint8_t ANDI = 0x29; //ANDI(AND com imediato), realiza a operação AND entr eum valor imediato e um acumulador. Instrução de 2 bytes
uint8_t ORAhash = 0x09; //ORA#, realiza operação OR enrte acumulador e valor imediato. Instrução de 2 bytes
uint8_t EORhash = 0x49; //EOR#, realiza operação XOR entre acumulador e valor imediato. Instrução de 2 bytes
uint8_t CMPhash = 0xC9;  //CMP, realiza a operação de comparação entre oq está no acumulador e um valor imediato. Instrução de 2 bytes
uint8_t CMPX = 0xDD; //CMPX, realiza comparação entre acumulador e indice x. Instrução de 3 bytes
uint8_t CMPY = 0xD9;  //CMPY, realiza comparação entre acumulador e indice y. Instrução de 3 bytes

typedef enum {
    eADC = 0x65,    // ADC, adiciona o acumulador a algum outro registrador
    eADChash = 0x69,    // ADC#, adiciona imediato ao acumulador
    eSBChash = 0xE9,    // SBC#, subtrai o acumulador por um imediato
    eANDY = 0x39,    // ANDY, realiza operação lógica AND entre o acumulador e o índice Y
    eORAX = 0x1D,    // ORAX, realiza operação lógica OR entre o acumulador e o índice X
    eEORX = 0x5D,    // EORX, realiza operação lógica XOR entre o acumulador e o índice X
    eASL = 0x0E,    // ASL (arithmetic shift left), realiza a operação de shift, deslocando os bits do acumulador para a esquerda e preenchendo o bit mais à direita com 0
    eLSR = 0x4A,    // LSR (shift pra direita)
    eANDI = 0x29,    // ANDI (AND com imediato), realiza a operação AND entre um valor imediato e um acumulador
    eORAhash = 0x09,    // ORA#, realiza operação OR entre acumulador e valor imediato
    eEORhash = 0x49,    // EOR#, realiza operação XOR entre acumulador e valor imediato
    eCMPhash = 0xC9,    // CMP, realiza a operação de comparação entre o que está no acumulador e um valor imediato
    eCMPX = 0xDD,    // CMPX, realiza comparação entre acumulador e índice x
    eCMPY = 0xD9    // CMPY, realiza comparação entre acumulador e índice y
} InstrucoesULA;

// INSTRUÇÕES DE ACESSO A MEMÓRIA
uint8_t LDAhash = 0xA9;  //LDA com imediato. Instrução de 2 bytes
uint8_t LDA = 0xAD;  //LDA com endereço de memória. Instrução de 3 bytes
uint8_t LDXhash = 0xA2;  //LDX, carrega índice x com imediato. Instrução de 2 bytes
uint8_t LDX = 0xAE;  //LDX, carrega indice x com endereço de memória. Instrução de 3 bytes
uint8_t LDYhash = 0xA0;  //LDY, carrega índice y com imediato. Instrução de 2 bytes
uint8_t LDY = 0xAC;  //LDY, carrega indice y com endreço de memória. Instrução de 3 bytes
uint8_t STA = 0x85;  //STA, armazena o valor do acumlador para um endereço de memória da ram. Instrução de 3 bytes
uint8_t STX = 0x86; //STX, armazena o índice x em um endereço de memória no vetor de memória ram. Instrução de 3 bytes
uint8_t STY = 0x8C;  //STY, armazena o índice y em um endereço de memória. Instrução de 3 bytes

typedef enum {
    eLDAhash = 0xA9,  //LDA com imediato
    eLDA = 0xAD,  //LDA com endereço de memória
    eLDXhash = 0xA2,  //LDX, carrega índice x com imediato
    eLDX = 0xAE,  //LDX, carrega índice x com endereço de memória
    eLDYhash = 0xA0,  //LDY, carrega índice y com imediato
    eLDY = 0xAC,  //LDY, carrega índice y com endereço de memória
    eSTA = 0x85,  //STA, armazena o valor do acumulador para um endereço de memória da RAM
    eSTX = 0x86, //STX, armazena o índice x em um endereço de memória no vetor de memória RAM
    eSTY = 0x8C  //STY, armazena o índice y em um endereço de memória
} InstrucoesMemoria;


//INSTRUÇÕES DE SALTO CONDICIONAL
uint8_t BEQ = 0xF0;  //BEQ, salta pra label se a condição de igualdade for verdadeira, a instrução a ser executada antes da mesma deve ser CMP para a definição de flag. Instrução de 2 bytes
uint8_t BNE = 0xD0;  //BNE, salta pra label se a condição de igualdade não for verdadeira. Instrução de 2 bytes
uint8_t BCC = 0x90;  //BCC, salta pra label se o bit de carry estiver definido como zero. Instrução de 2 bytes
uint8_t BCS = 0xB0;  //BCS, salta pra label se o bit de carry estiver definido como 1. Instrução de 2 bytes

typedef enum {
    eBEQ = 0xF0,  //BEQ, salta para label se a condição de igualdade for verdadeira
    eBNE = 0xD0,  //BNE, salta para label se a condição de igualdade não for verdadeira
    eBCC = 0x90,  //BCC, salta para label se o bit de carry estiver definido como zero
    eBCS = 0xB0   //BCS, salta para label se o bit de carry estiver definido como 1
} InstrucoesSaltoCondicional;

//INSTRUÇÕES DE SALTO INCONDICIONAL
uint8_t JMP = 0x4C;  //JMP, salta incondicionalmente para o endereço de memória definido. Instrução de 3 bytes
uint8_t JSR = 0x20;  //JSR, salta incondicionalmente para o endreço de memória definido e salva endereço de memória para retornar ao ponto de chamada. Instrução de 3 bytes
uint8_t RTS = 0x60;  //RTS, retorna ao endereço de retorno estabelecido após JSR. Instrução de 1 byte

typedef enum {
    eJMP = 0x4C,  //JMP, salta incondicionalmente para o endereço de memória definido
    eJSR = 0x20,  //JSR, salta incondicionalmente para o endereço de memória definido e salva endereço de memória para retornar ao ponto de chamada
    eRTS = 0x60   //RTS, retorna ao endereço de retorno estabelecido após JSR
} InstrucoesSaltoIncondicional;
 

#endif
