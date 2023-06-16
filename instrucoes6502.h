#ifndef instrucoes6502
#define instrucoes6502
#include <stdint.h>

WINDOW *EntradaInfo;
int yborda, xborda;

char *logopt1 = " _                __  _  _ __ \n";
char *logopt2 = "|_) o  _  _ |_     _)|_|/ \\__)\n";
char *logopt3 = "| \\ | (_ (_)| |   /__| |\\_/__)\n";

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

} Processador;

uint8_t ram[0x07D0]; //declaração da memória ram com 4kb de armazenamento

// As variáveis que não possuirem o formato uintX_t são aquelas que representam as instruções com opcodes de 3 bytes
// Os opcodes no NES podem variar entre 1 a 3 bytes

// INSTRUÇÕES DA ULA
uint16_t ADC = 0x65;  //ADC, adiciona o acumulador a algum outro registrador
uint16_t ADChash = 0x69; //ADC#, adiciona imediato ao acumulador
uint16_t SBChash = 0xE9;  //SBC#, subtrai o acumulador por um imediato
unsigned int ANDY = 0x39;  //ANDY, realiza operação lógica AND entr eo acumulador e o índice Y
unsigned int ORAX = 0x1D;  //ORAX, realiza operação lógica OR entre o acumulador e o índice X
unsigned int EORX = 0x5D;  //EORX, realiza operação lógica XOR entre o acumulador e o índice X
//não possui instrução nor nativa
//não possui instrução slt nativa
//não possui instrução sll nativa
uint8_t ASL = 0x0E; //ASL (arithmetic shift left), realiza a operação de shift, deslocando os bits do acumulador para a esquerda e preenchendo o bit mais à direita com 0
uint8_t LSR = 0x4A;  //LSR (shift pra direita)
uint16_t ANDI = 0x29; //ANDI(AND com imediato), realiza a operação AND entr eum valor imediato e um acumulador
uint16_t ORAhash = 0x09; //ORA#, realiza operação OR enrte acumulador e valor imediato
uint16_t EORhash = 0x49; //EOR#, realiza operação XOR entre acumulador e valor imediato
uint16_t CMPhash = 0xC9;  //CMP, realiza a operação de comparação entre oq está no acumulador e um valor imediato
unsigned int CMPX = 0xDD; //CMPX, realiza comparação entre acumulador e indice x
unsigned int CMPY = 0xD9;  //CMPY, realiza comparação entre acumulador e indice y

// INSTRUÇÕES DE ACESSO A MEMÓRIA
uint16_t LDA = 0xA9;  //LDA com imediato
unsigned int LDA = 0xAD;  //LDA com endereço de memória
uint16_t LDXhash = 0xA2;  //LDX, carrega índice x com imediato
unsigned int LDX = 0xAE;  //LDX, carrega indice x com endereço de memória
uint16_t LDYhash = 0xA0;  //LDY, carrega índice y com imediato
unsigned int LDY = 0xAC;  //LDY, carrega indice y com endreço de memória
unsigned int STA = 0x85;  //STA, armazena o valor do acumlador para um endereço de memória da ram
unsigned int STX = 0x86; //STX, armazena o índice x em um endereço de memória no vetor de memória ram
unsigned int STY = 0x8C;  //STY, armazena o índice y em um endereço de memória


//INSTRUÇÕES DE SALTO CONDICIONAL
uint16_t BEQ = 0xF0;  //BEQ, salta pra label se a condição de igualdade for verdadeira, a instrução a ser executada antes da mesma deve ser CMP para a definição de flag
uint16_t BNE = 0xD0;  //BNE, salta pra label se a condição de igualdade não for verdadeira
uint16_t BCC = 0x90;  //BCC, salta pra label se o bit de carry estiver definido como zero
uint16_t BCS = 0xB0;  //BCS, salta pra label se o bit de carry estiver definido como 1

//INSTRUÇÕES DE SALTO INCONDICIONAL
unsigned int JMP = 0x4C;  //JMP, salta incondicionalmente para o endereço de memória definido
unsigned int JSR = 0x20;  //JSR, salta incondicionalmente para o endreço de memória definido e salva endereço de memória para retornar ao ponto de chamada
uint8_t RTS = 0x60;  //RTS, retorna ao endereço de retorno estabelecido após JSR
 

#endif
