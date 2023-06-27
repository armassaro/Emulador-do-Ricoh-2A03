#include "instrucoes6502.h"

void RecebeString(char stringFunction[30]) {

    fgets(stringFunction, 30, stdin);
    stringFunction[strcspn(stringFunction, "\n")] = '\0';
    setbuf(stdin, NULL);

    return;

}

void ExecutaArquivo(Processador *processador, FILE *arquivoBin) {

    char StringAux[40];
    char StringAux1[40];
    uint8_t operando1;
    uint8_t operando2;
    char nomeInstrucao[10];
    int tamanhoArquivo;
    uint16_t indiceHex;

    processador->acumulador = 0x00;
    processador->indicex = 0x00;
    processador->indicey = 0x00;
    processador->stackpointer = 0x00;
    processador->statusregister = 0x00;
    processador->programcounter = 0x00;
    processador->flags.carry = false;
    processador->flags.zero = false;
    processador->flags.interruptDisable = false;
    processador->flags.decimalMode = false;
    processador->flags.breakCommand = false;
    processador->flags.overflow = false;

    fread(&processador->programcounter, sizeof(uint16_t), 1, arquivoBin);

        while(!feof(arquivoBin)) { 

        getchar();
        fread(&operando1, sizeof(uint8_t), 1, arquivoBin);
        processador->programcounter = processador->programcounter + sizeof(uint8_t);

        switch(operando1) {  //switch

            //INSTRUÇÕES DE LÓGICA E ARITMÉTICA
            case eADC:
             
            break;

            case eADChash:
             
            break;

            case eSBChash:
             
            break;

            case eANDY:
             
            break;

            case eORAX:
             
            break;

            case eEORX:
             
            break;
        
            case eASL:
             
            break;

            case eLSR:
             
            break;

            case eANDI:
             
            break;

            case eORAhash:
             
            break;

            case eEORhash:
             
            break;

            case eCMPhash:
             
            break;

            case eCMPX:
             
            break;

            case eCMPY:
             
            break;

            //INSTRUÇÕES DE ACESSO A MEMÓRIA
            case eLDAhash:
            fread(&operando2, sizeof(uint8_t), 1, arquivoBin);
            processador->programcounter = processador->programcounter + sizeof(LDAhash);
            printf("Instrução executada = LDA #$%02x\n", operando2);  //copia string que contém a informação da instrução que está sendo executada
            processador->acumulador = operando2;
            break;

            case eLDA:
            fread(&operando1, sizeof(uint8_t), 1, arquivoBin);  //coleta o byte de ordem inferior 
            processador->programcounter = processador->programcounter + sizeof(LDA);
            fread(&operando2, sizeof(uint8_t), 1, arquivoBin);  //coleta o byte de ordem superior
            processador->programcounter = processador->programcounter + sizeof(LDA);
            sprintf(StringAux, "%02x%02x", operando2, operando1);  //organiza os bytes de ordem superior e inferior em uma string
            indiceHex = (operando2 << 8) | operando1;
            printf("IndiceHex = %i\n", indiceHex);
            printf("Instrução executada = LDA $%s\n", StringAux);  //copia string que contém a informação da instrução que está sendo executada
            processador->acumulador = processador->ram[indiceHex];
            break;

            case eLDXhash:
            fread(&operando1, sizeof(uint8_t), 1, arquivoBin);
            processador->programcounter = processador->programcounter + sizeof(LDXhash);
            printf("Instrução executada = LDX #$%02x\n", operando1);  //copia string que contém a informação da instrução que está sendo executada
            processador->indicex = operando1;
            break;

            case eLDX:
            fread(&operando2, sizeof(uint8_t), 1, arquivoBin);  //coleta o byte de ordem inferior 
            processador->programcounter = processador->programcounter + sizeof(LDX);
            fread(&operando1, sizeof(uint8_t), 1, arquivoBin);  //coleta o byte de ordem superior
            processador->programcounter = processador->programcounter + sizeof(LDX);
            sprintf(StringAux, "%02x%02x", operando1, operando2);  //organiza os bytes de ordem superior e inferior em uma string
            operando2 = strtol(StringAux, NULL, 16);
            printf("Instrução executada = LDX $%s\n", StringAux);  //copia string que contém a informação da instrução que está sendo executada
            processador->indicex = processador->ram[operando2];
            break;

            case eLDYhash:
            fread(&operando2, sizeof(uint8_t), 1, arquivoBin);
            processador->programcounter = processador->programcounter + sizeof(LDYhash);
            printf("Instrução executada = LDY #$%02x\n", operando2);  //copia string que contém a informação da instrução que está sendo executada
            processador->indicey = operando2;
            break;

            case eLDY:
            fread(&operando2, sizeof(uint8_t), 1, arquivoBin);  //coleta o byte de ordem inferior 
            processador->programcounter = processador->programcounter + sizeof(LDY);
            fread(&operando1, sizeof(uint8_t), 1, arquivoBin);  //coleta o byte de ordem superior
            processador->programcounter = processador->programcounter + sizeof(LDY);
            sprintf(StringAux, "%x%x", operando1, operando2);//organiza os bytes de ordem superior e inferior em uma string
            sscanf(StringAux, "%x", operando2);  //converte de string para inteiro
            printf("Instrução executada = LDY $%02x\n", operando2);  //copia string que contém a informação da instrução que está sendo executada
            processador->indicey = processador->ram[operando2];
            break;

            case eSTA:
            fread(&operando2, sizeof(uint8_t), 1, arquivoBin);  //coleta o byte de ordem inferior 
            processador->programcounter = processador->programcounter + sizeof(STA);
            fread(&operando1, sizeof(uint8_t), 1, arquivoBin);  //coleta o byte de ordem superior
            processador->programcounter = processador->programcounter + sizeof(STA);
            sprintf(StringAux, "%02x%02x", operando1, operando2);  //organiza os bytes de ordem superior e inferior em uma string
            indiceHex = (operando2 << 8) | operando1;
            printf("IndiceHex = %x\n", indiceHex);
            printf("Instrução executada = STA $%s\n", StringAux);  //copia string que contém a informação da instrução que está sendo executada
            processador->ram[indiceHex] = processador->acumulador;
            break;

            case eSTX:
            fread(&operando2, sizeof(uint8_t), 1, arquivoBin);  //coleta o byte de ordem inferior 
            processador->programcounter = processador->programcounter + sizeof(STX);
            fread(&operando1, sizeof(uint8_t), 1, arquivoBin);  //coleta o byte de ordem superior
            processador->programcounter = processador->programcounter + sizeof(STX);
            sprintf(StringAux, "%02x%02x", operando1, operando2);  //organiza os bytes de ordem superior e inferior em uma string
            operando2 = strtol(StringAux, NULL, 16);
            printf("Instrução executada = STX $%s\n", StringAux);  //copia string que contém a informação da instrução que está sendo executada
            processador->ram[operando2] = processador->indicex;
            break;

            case eSTY:
            fread(&operando2, sizeof(uint8_t), 1, arquivoBin);  //coleta o byte de ordem inferior 
            processador->programcounter = processador->programcounter + sizeof(STY);
            fread(&operando1, sizeof(uint8_t), 1, arquivoBin);  //coleta o byte de ordem superior
            processador->programcounter = processador->programcounter + sizeof(STY);
            sprintf(StringAux, "%02x%02x", operando1, operando2);  //organiza os bytes de ordem superior e inferior em uma string
            operando2 = strtol(StringAux, NULL, 16);
            printf("Instrução executada = STY $%s\n", StringAux);  //copia string que contém a informação da instrução que está sendo executada
            processador->ram[operando2] = processador->indicey;
            break;

            //INSTRUÇÕES DE SALTO CONDICIONAL
            case eBEQ:
            if(processador->flags.zero == true) {

                fread(&operando1, sizeof(uint8_t), 1, arquivoBin);  //leitura de operando
                printf("Instrução executada = BEQ #$%x\n", operando1);  //copia string que contém a informação da instrução que está sendo executada
                processador->programcounter = processador->programcounter + operando1;  //adiciona ao program counter
                fseek(arquivoBin, operando1 * sizeof(uint8_t), SEEK_CUR);

            }
            else {

                fread(&operando1, sizeof(uint8_t), 1, arquivoBin);
                printf("Instrução executada = BEQ #$%x\n", operando1);  //copia string que contém a informação da instrução que está sendo executada
                processador->programcounter = processador->programcounter + 2;

            }
            break;

            case eBNE:
            if(processador->flags.zero == false) {

                fread(&operando1, sizeof(uint8_t), 1, arquivoBin);  //leitura de operando
                printf("Instrução executada = BNE #$%x\n", operando1);  //copia string que contém a informação da instrução que está sendo executada
                processador->programcounter = processador->programcounter + operando1;  //adiciona ao program counter
                fseek(arquivoBin, -sizeof(uint8_t), SEEK_CUR);  //retorna o ponteiro pra instrução
                fseek(arquivoBin, operando1 * sizeof(uint8_t), SEEK_CUR);

            }
            else {

                fread(&operando1, sizeof(uint8_t), 1, arquivoBin);
                printf("Instrução executada = BNE #$%x\n", operando1);  //copia string que contém a informação da instrução que está sendo executada
                processador->programcounter = processador->programcounter + sizeof(BNE);

            }
            break;

            case eBCC:
            if(processador->flags.carry == false) {

                fread(&operando1, sizeof(uint8_t), 1, arquivoBin);  //leitura de operando
                printf("Instrução executada = BCC #$%x\n", operando1);  //copia string que contém a informação da instrução que está sendo executada
                processador->programcounter = processador->programcounter + operando1;  //adiciona ao program counter
                fseek(arquivoBin, -sizeof(uint8_t), SEEK_CUR);  //retorna ponteiro pra instrução
                fseek(arquivoBin, operando1 * sizeof(uint8_t), SEEK_CUR);

            }
            else {

                fread(&operando1, sizeof(uint8_t), 1, arquivoBin);
                printf("Instrução executada = BCC #$%x\n", operando1);  //copia string que contém a informação da instrução que está sendo executada
                processador->programcounter = processador->programcounter + sizeof(BCC);

            }
            break;

            case eBCS:
            if(processador->flags.carry == true) {

                fread(&operando1, sizeof(uint8_t), 1, arquivoBin);  //leitura de operando
                printf("Instrução executada = BCS #$%x\n", operando1);  //copia string que contém a informação da instrução que está sendo executada
                processador->programcounter = processador->programcounter + operando1;  //adiciona ao program counter
                fseek(arquivoBin, -sizeof(uint8_t), SEEK_CUR);  //retorna ponteiro pra instrução
                fseek(arquivoBin, operando1 * sizeof(uint8_t), SEEK_CUR);

            }
            else {

                fread(&operando1, sizeof(uint8_t), 1, arquivoBin);
                printf("Instrução executada = BCS #$%x\n", operando1);  //copia string que contém a informação da instrução que está sendo executada
                processador->programcounter = processador->programcounter + sizeof(BCS);

            }
            break;

            //INSTRUÇÕES DE SALTO INCONDICIONAL
            case eJMP:
            printf("Instrução: JMP\n");
            // Lógica para salto incondicional JMP
            break;
            case eJSR:
            printf("Instrução: JSR\n");
            // Lógica para salto incondicional JSR
            break;
            case eRTS:
            printf("Instrução: RTS\n");
            // Lógica para salto incondicional RTS
            break;

            default:
            printf("Opcode de instrução não encontrado\n");
            break;

        }  //switch#

        printf("Acumulador = %x\n", processador->acumulador);
        printf("X = %x\n", processador->indicex);
        printf("Y = %x\n", processador->indicey);
        printf("Stack pointer = %x\n", processador->stackpointer);
        printf("Status register = %x\n", processador->statusregister);
        printf("Program counter = %x\n", processador->programcounter);
        printf("Flag carry = %d\n", processador->flags.carry);
        printf("Flag zero = %d\n", processador->flags.zero);
        printf("Flag interrupt disable = %d\n", processador->flags.interruptDisable);
        printf("Flag decimal mode = %d\n", processador->flags.decimalMode);
        printf("Flag break command = %d\n", processador->flags.breakCommand);
        printf("Flag overflow = %d\n", processador->flags.overflow);


    }  //while#

}

int main() {

    char caminhoarquivo[30];
    Processador processador;

    printf("Bem vindo ao emulador do Ricoh 2A03! Digite o nome do arquivo binário: ");
    RecebeString(caminhoarquivo);

    FILE *arquivoBin = fopen(caminhoarquivo, "rb");

    ExecutaArquivo(&processador, arquivoBin);

    return 0;

}
