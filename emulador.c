#include "instrucoes6502.h"

void LerArquivo(Processador *processador, char *caminhoarquivo, FILE *arquivoBin, FILE *arquivoTexto, int yterminal, int xterminal, int yborda, int xborda);
void InterfaceGrafica(WINDOW *borda, Processador *processador, char *caminhoarquivo, FILE *arquivoBin, int yterminal, int xterminal, int yborda, int xborda);

int main() {
    
    Processador processador;
    initscr();
    cbreak();
    noecho();
    curs_set(FALSE);
    processador.programcounter = 0x0600;  //valor inicial do program counter
    processador.acumulador = processador.indicex = processador.indicey = processador.stackpointer = processador.statusregister = 0x000;

    int xterminal;
    int yterminal;
    char caminhoarquivo[200]; //string que indica o nome ou o caminho do arquivo binário
    FILE *arquivoBin;

    getmaxyx(stdscr, yterminal, xterminal);

    // mvprintw(yterminal / 2, xterminal / 2 - 4, "Carregando...\n");
    // mvprintw((yterminal / 2) - 2, 2, "[");
    // mvprintw((yterminal / 2) - 2, xterminal - 2, "]");
    // refresh();

    // for(int a = 4; a <= xterminal - 4; a++) {  //tela de carregamento

    //     mvprintw((yterminal / 2) - 2, a, ">");
        
    //     refresh();
    //     usleep(20000);

    //     mvprintw((yterminal / 2) - 2, a, "|");

    //     refresh();

    //     usleep(5000);

    // }

    // for(int a = 4; a <= xterminal - 4; a++) {  //preenche risco com hashtag

    //     mvprintw((yterminal / 2) - 2, a, "#");
        
    //     refresh();

    //     usleep(6000);

    // }

    // clear();

    // mvprintw((yterminal / 2) - 2, xterminal / 2, "#");

    // for(int a = yterminal / 2; a <= yterminal - 4; a++) {  //move um asterisco centralizado pra baixo

    //     mvprintw(a, xterminal / 2, "#");
        
    //     refresh();

    //     usleep(10000);

    //     clear();

    // }

    // for(int a = xterminal / 2; a <= xterminal - 4; a++) {  //move o asterisco pra direita

    //     mvprintw(yterminal - 4, a, "#");
        
    //     refresh();

    //     usleep(10000);

    //     clear();

    // }

    // for(int a = yterminal - 4; a >= 4; a--) {  //sobe e preenche coluna direita

    //     mvprintw(a, xterminal - 4, "#");
        
    //     refresh();

    //     usleep(10000);

    // }

    // for(int a = xterminal - 4; a >= 4; a--) {  //vai pra esquerda e preenche linha de cima

    //     mvprintw(4, a, "-");
    //     refresh();

    //     usleep(10000);

    // }

    // for(int a = 5; a <= yterminal - 4; a++) {  //preenche coluna esquerda

    //     mvprintw(a, 4, "#");
        
    //     refresh();

    //     usleep(10000);

    // }

    // for(int a = 4; a <= xterminal - 4; a++) {  //preenche linha inferior

    //     mvprintw(yterminal - 4, a, "-");
    //     refresh();

    //     usleep(10000);

    // }

    noecho();
    cbreak();
    refresh();

    WINDOW *borda = newwin(yterminal - 7, xterminal - 7, 4, 4);
    getmaxyx(borda, yborda, xborda);

    mvwprintw(borda, yterminal / 2 - 8, (xterminal - strlen(logopt1)) / 2, "%s", logopt1);  //print da logo do menu inicial
    mvwprintw(borda, yterminal / 2 - 7, (xterminal - strlen(logopt2)) / 2, "%s", logopt2);
    mvwprintw(borda, yterminal / 2 - 6, (xterminal - strlen(logopt3)) / 2, "%s", logopt3);
    wborder(borda, '#', '#', '-', '-', '-', '-', '-', '-');

    wrefresh(borda);

    WINDOW *menu = newwin(4, 15, yterminal / 2 + 1, (xterminal - 10) / 2);
    refresh();

    char *menuopcoes[] = {"Iniciar", "Sair"};
    int opcoes = 2;
    int opcao;
    int highlight = 0;

keypad(menu, TRUE);

while (1) {

    for (int i = 0; i < opcoes; i++) {

        if (i == highlight) {

            wattron(menu, A_REVERSE);

        }

        int x = (15 - strlen(menuopcoes[i])) / 2;
        mvwprintw(menu, i + 1, x, "%s", menuopcoes[i]);
        wattroff(menu, A_REVERSE);

    }

    wborder(menu, '#', '#', '-', '-', '-', '-', '-', '-');
    wrefresh(menu);

    opcao = wgetch(menu);

    switch (opcao) {

        case KEY_UP:
            highlight--;
            if (highlight < 0) {

                highlight = 0;

            }
            break;

        case KEY_DOWN:
            highlight++;

            if (highlight >= opcoes) {

                highlight = opcoes - 1;

            }

            break;

        case '\n': 

            if (highlight == 0) {

                nocbreak();  //habilita a entrada de informação até o usuário digitar enter
                echo(); 
                curs_set(TRUE);
                refresh();

                WINDOW *JanelaString = newwin(1, xterminal - 5, yterminal / 2, 6);
                keypad(JanelaString, TRUE);
                EntradaInfo = newwin(3, xborda - 30, yterminal / 2, (xterminal - (xborda - 30)) / 2);

                clear();
                refresh();
                wclear(borda);
                wborder(borda, '#', '#', '-', '-', '-', '-', '-', '-');
                wrefresh(borda);
                wborder(EntradaInfo, '#', '#', '-', '-', '-', '-', '-', '-');
                wrefresh(EntradaInfo);
                mvwprintw(borda, yborda / 2 - 3, (xborda - strlen("Digite o caminho do arquivo contendo o codigo-fonte")) / 2, "Digite o caminho do arquivo contendo o codigo-fonte");
                wrefresh(borda);
                move(yterminal / 2 + 1, (xterminal - (xborda - 30)) / 2 + 2);
                refresh();
                getnstr(caminhoarquivo, 200);  //função de coleta de string pra biblioteca ncurses q nn deixa caractere \n como final
                setbuf(stdin, NULL);

                arquivoBin = fopen(caminhoarquivo, "rb");

                fread(processador.programcounter, sizeof(uint16_t), 1, arquivoBin);  //coleta do program counter

                if(arquivoBin == NULL) {

                    wclear(borda);
                    refresh();
                    curs_set(FALSE);
                    wborder(borda, '#', '#', '-', '-', '-', '-', '-', '-');
                    mvwprintw(borda, yborda / 2, (xborda - strlen("Erro na abertura de arquivo! Pressione qualquer tecla")) / 2, "Erro na abertura de arquivo! Pressione qualquer tecla");
                    wrefresh(borda);
                    getch();

                    endwin();
                    return 1;

                }
                else { 

                    curs_set(FALSE);
                    wclear(borda);
                    wborder(borda, '#', '#', '-', '-', '-', '-', '-', '-');
                    mvwprintw(borda, yborda / 2, (xborda - strlen("Sucesso na abertura do arquivo! Pressione qualquer tecla para prosseguir")) / 2, "Sucesso na abertura do arquivo! Pressione qualquer tecla para prosseguir");
                    wrefresh(borda);
                    getch();
                    InterfaceGrafica(borda, &processador, caminhoarquivo, arquivoBin, yterminal, xterminal, yborda, xborda);

                }


            }

    }
}

    endwin();

    return 0;
}

void InterfaceGrafica(WINDOW *borda, Processador *processador, char *caminhoarquivo, FILE *arquivoBin, int yterminal, int xterminal, int yborda, int xborda) {

    int ContadorCiclos = 0;
    char StringAux[20];
    char StringAux1[20];
    int IntAux;
    char *nomeInstrucao;

    WINDOW *console = newwin(10, 10, yborda - 4, xborda - 4);

    while(fread(IntAux, sizeof(uint16_t), 1, arquivoBin) != EOF) {
        
        wclear(borda);

        strcpy(StringAux, "X = 0x");
        sprintf(StringAux1, "%x", processador->indicex);
        strcat(StringAux, StringAux1);
        mvwprintw(borda, (yborda - 7) / 2, (xborda - strlen(StringAux)) / 2, StringAux);

        strcpy(StringAux, "Y = 0x");
        sprintf(StringAux1, "%x", processador->indicey);
        strcat(StringAux, StringAux1);
        mvwprintw(borda, (yborda - 7) / 2 + 1, (xborda - strlen(StringAux)) / 2, StringAux);
        
        strcpy(StringAux, "A = 0x");
        sprintf(StringAux1, "%x", processador->acumulador);
        strcat(StringAux, StringAux1);
        mvwprintw(borda, (yborda - 7) / 2 + 2, (xborda - strlen(StringAux)) / 2, StringAux);
        
        strcpy(StringAux, "SP = 0x");
        sprintf(StringAux1, "%x", processador->stackpointer);
        strcat(StringAux, StringAux1);
        mvwprintw(borda, (yborda - 7) / 2 + 3, (xborda - strlen(StringAux)) / 2, StringAux);
        
        strcpy(StringAux, "Status register = 0x");
        sprintf(StringAux1, "%x", processador->statusregister);
        strcat(StringAux, StringAux1);
        mvwprintw(borda, (yborda - 7) / 2 + 4, (xborda - strlen(StringAux)) / 2, StringAux);
        
        strcpy(StringAux, "Program counter = 0x");
        sprintf(StringAux1, "%x", processador->programcounter);
        strcat(StringAux, StringAux1);
        mvwprintw(borda, (yborda - 7) / 2 + 5, (xborda - strlen(StringAux)) / 2, StringAux);
        
        sprintf(StringAux1, "Instrucao executada = %s", nomeInstrucao);
        mvwprintw(borda, (yborda - 7) / 2 + 6, (xborda - strlen(StringAux1)) / 2, StringAux1);
        
        mvwprintw(borda, (yborda - 7) / 2 + 13, (xborda - strlen("Pressione qualquer tecla para o proximo ciclo")) / 2, "Pressione qualquer tecla para o proximo ciclo");
        
        wborder(console, '#', '#', '-', '-', '-', '-', '-', '-');
        wrefresh(console);
        
        wborder(borda, '#', '#', '-', '-', '-', '-', '-', '-');
        wrefresh(borda);
        
        getch();

        int resultadoleitura;

        fread(resultadoleitura, sizeof(uint8_t), 1, arquivoBin);

        switch(resultadoleitura) {

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

            case eLDAhash:
            fread(addressBus, sizeof(uint8_t), 1, arquivoBin);
            sprintf(nomeInstrucao, "LDA #$%i", addressBus);  //copia string que contém a informação da instrução que está sendo executada
            processador->acumulador = resultadoleitura;
            processador->programcounter = processador->programcounter + sizeof(LDAhash);
            break;

            case eLDA:
            fread(addressBus, sizeof(uint8_t), 1, arquivoBin);  //coleta o byte de ordem inferior 
            fread(resultadoleitura, sizeof(uint8_t), 1, arquivoBin);  //coleta o byte de ordem superior
            sprintf(StringAux, "%i%i", resultadoleitura, addressBus);  //organiza os bytes de ordem superior e inferior em uma string
            sscanf(StringAux, "%i", addressBus);  //converte de string para inteiro
            sprintf(nomeInstrucao, "LDA $%i", addressBus);  //copia string que contém a informação da instrução que está sendo executada
            processador->acumulador = processador->ram[addressBus];
            processador->programcounter = processador->programcounter + 3;
            break;

            case eLDXhash:
            fread(addressBus, sizeof(uint8_t), 1, arquivoBin);
            sprintf(nomeInstrucao, "LDX #$%i", addressBus);  //copia string que contém a informação da instrução que está sendo executada
            processador->ram[addressBus] = processador->indicex;
            processador->programcounter = processador->programcounter + sizeof(LDXhash);
            break;

            case eLDX:
            fread(addressBus, sizeof(uint8_t), 1, arquivoBin);  //coleta o byte de ordem inferior 
            fread(resultadoleitura, sizeof(uint8_t), 1, arquivoBin);  //coleta o byte de ordem superior
            sprintf(StringAux, "%i%i", resultadoleitura, addressBus);  //organiza os bytes de ordem superior e inferior em uma string
            sscanf(StringAux, "%i", addressBus);  //converte de string para inteiro
            sprintf(nomeInstrucao, "LDX $%i", addressBus);  //copia string que contém a informação da instrução que está sendo executada
            processador->indicex = processador->ram[addressBus];
            processador->programcounter = processador->programcounter + 3;
            break;

            case eLDYhash:
            fread(addressBus, sizeof(uint8_t), 1, arquivoBin);
            sprintf(nomeInstrucao, "LDY #$%i", addressBus);  //copia string que contém a informação da instrução que está sendo executada
            processador->ram[addressBus] = processador->indicey;
            processador->programcounter = processador->programcounter + sizeof(LDYhash);
            break;

            case eLDY:
            fread(addressBus, sizeof(uint8_t), 1, arquivoBin);  //coleta o byte de ordem inferior 
            fread(resultadoleitura, sizeof(uint8_t), 1, arquivoBin);  //coleta o byte de ordem superior
            sprintf(StringAux, "%i%i", resultadoleitura, addressBus);//organiza os bytes de ordem superior e inferior em uma string
            sscanf(StringAux, "%i", addressBus);  //converte de string para inteiro
            sprintf(nomeInstrucao, "LDY $%i", addressBus);  //copia string que contém a informação da instrução que está sendo executada
            processador->indicey = processador->ram[addressBus];
            processador->programcounter = processador->programcounter + 3;
            break;

            case eSTA:
            fread(addressBus, sizeof(uint8_t), 1, arquivoBin);  //coleta o byte de ordem inferior 
            fread(resultadoleitura, sizeof(uint8_t), 1, arquivoBin);  //coleta o byte de ordem superior
            sprintf(StringAux, "%i%i", resultadoleitura, addressBus);  //organiza os bytes de ordem superior e inferior em uma string
            sscanf(StringAux, "%i", addressBus);  //converte de string para inteiro
            sprintf(nomeInstrucao, "STA $%i", addressBus);  //copia string que contém a informação da instrução que está sendo executada
            processador->ram[addressBus] = processador->acumulador;
            processador->programcounter = processador->programcounter + 3;
            break;

            case eSTX:
            fread(addressBus, sizeof(uint8_t), 1, arquivoBin);  //coleta o byte de ordem inferior 
            fread(resultadoleitura, sizeof(uint8_t), 1, arquivoBin);  //coleta o byte de ordem superior
            sprintf(StringAux, "%i%i", resultadoleitura, addressBus);  //organiza os bytes de ordem superior e inferior em uma string
            sscanf(StringAux, "%i", addressBus);  //converte de string para inteiro
            sprintf(nomeInstrucao, "STX $%i", addressBus);  //copia string que contém a informação da instrução que está sendo executada
            processador->ram[addressBus] = processador->indicex;
            processador->programcounter = processador->programcounter + 3;
            break;

            case eSTY:
            fread(addressBus, sizeof(uint8_t), 1, arquivoBin);  //coleta o byte de ordem inferior 
            fread(resultadoleitura, sizeof(uint8_t), 1, arquivoBin);  //coleta o byte de ordem superior
            sprintf(StringAux, "%i%i", resultadoleitura, addressBus);  //organiza os bytes de ordem superior e inferior em uma string
            sscanf(StringAux, "%i", addressBus);  //converte de string para inteiro
            sprintf(nomeInstrucao, "STY $%i", addressBus);  //copia string que contém a informação da instrução que está sendo executada
            processador->ram[addressBus] = processador->indicey;
            processador->programcounter = processador->programcounter + 3;
            break;

            case eBEQ:
            if(processador->flags.zero == TRUE) {

                fread(resultadoleitura, sizeof(uint8_t), 1, arquivoBin);  //leitura de operando
                sprintf(nomeInstrucao, "BEQ #$%i", resultadoleitura);  //copia string que contém a informação da instrução que está sendo executada
                processador->programcounter = processador->programcounter + resultadoleitura;  //adiciona ao program counter
                fseek(arquivoBin, -sizeof(uint8_t), SEEK_CUR);  //retorna o ponteiro pra instrução
                fseek(arquivoBin, resultadoleitura * sizeof(uint8_t), SEEK_CUR);

            }
            else {

                fread(resultadoleitura, sizeof(uint8_t), 1, arquivoBin);
                processador->programcounter = processador->programcounter + 2;

            }
            break;

            case eBNE:
            if(processador->flags.zero == FALSE) {

                fread(resultadoleitura, sizeof(uint8_t), 1, arquivoBin);  //leitura de operando
                processador->programcounter = processador->programcounter + resultadoleitura;  //adiciona ao program counter
                fseek(arquivoBin, -sizeof(uint8_t), SEEK_CUR);  //retorna o ponteiro pra instrução
                fseek(arquivoBin, resultadoleitura, SEEK_CUR);  //desloca o ponteiro pro 

            }
            else {

                fread(resultadoleitura, sizeof(uint8_t), 1, arquivoBin);
                processador->programcounter = processador->programcounter + sizeof(BNE);

            }
            break;

            case eBCC:
            if(processador->flags.carry == FALSE) {

                fread(resultadoleitura, sizeof(uint8_t), 1, arquivoBin);  //leitura de operando
                processador->programcounter = processador->programcounter + resultadoleitura;  //adiciona ao program counter
                fseek(arquivoBin, -sizeof(uint8_t), SEEK_CUR);  //retorna ponteiro pra instrução
                fseek(arquivoBin, resultadoleitura, SEEK_CUR);

            }
            else {

                fread(resultadoleitura, sizeof(uint8_t), 1, arquivoBin);
                processador->programcounter = processador->programcounter + sizeof(BCC);

            }
            break;

            case eBCS:
            if(processador->flags.carry == TRUE) {

                fread(resultadoleitura, sizeof(uint8_t), 1, arquivoBin);  //leitura de operando
                processador->programcounter = processador->programcounter + resultadoleitura;  //adiciona ao program counter
                fseek(arquivoBin, -sizeof(uint8_t), SEEK_CUR);  //retorna ponteiro pra instrução
                fseek(arquivoBin, resultadoleitura, SEEK_CUR);

            }
            else {

                fread(resultadoleitura, sizeof(uint8_t), 1, arquivoBin);
                processador->programcounter = processador->programcounter + sizeof(BCS);

            }
            break;

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
            // Caso a variável não esteja listada acima
            break;

        }

    }

    return;

}
