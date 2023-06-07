#ifndef instrucoes6502.h
#define instrucoes6502.h
#include <stdint.h>

uint16_t LDA = 0xA9;  //LDA com imediato
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


#endif instrucoes6502.h
