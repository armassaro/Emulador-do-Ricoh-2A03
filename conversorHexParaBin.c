#include "instrucoes6502.h"

int main() {

    FILE *arquivo;
    FILE *arquivobin;
    char StringAux[20];

    uint8_t byteLido;
    uint16_t opcode;

    arquivo = fopen("hexadecimal", "r");

    if(arquivo == NULL) {

        printf("Erro na abertura de arquivo\n");

    }

    arquivobin = fopen("binario.dat", "wb");

    if(arquivobin == NULL) {

        printf("Erro na abertura de arquivo binario\n");

    }

    fscanf(arquivo, "%s: ", StringAux);  //coleta de program counter inicial
    opcode = strtol(StringAux, NULL, 16);
    fwrite(&opcode, sizeof(uint16_t), 1, arquivobin);

    while(feof(arquivo) == 0) { //coleta de operandos e opcodes

        fscanf(arquivo, "%s ", StringAux);
        byteLido = strtol(StringAux, NULL, 16);
        fwrite(&byteLido, sizeof(uint8_t), 1, arquivobin);

    }

    return 0;
    
}