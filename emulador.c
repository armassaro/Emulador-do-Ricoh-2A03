#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <ncurses.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>
#include "instrucoes6502.h"

void LerArquivo(Processador *processador, char *caminhoarquivo, FILE *arquivo, int yterminal, int xterminal, int yborda, int xborda);
void InterfaceGrafica(WINDOW *borda, Processador *processador, char *caminhoarquivo, FILE *arquivo, int yterminal, int xterminal, int yborda, int xborda);

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
    FILE *arquivo;

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

    MENU:

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

                arquivo = fopen(caminhoarquivo, "rb");

                if(arquivo == NULL) {

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
                    InterfaceGrafica(borda, &processador, caminhoarquivo, arquivo, yterminal, xterminal, yborda, xborda);

                }


            }

    }
}

FIM:

    endwin();

    return 0;
}

void InterfaceGrafica(WINDOW *borda, Processador *processador, char *caminhoarquivo, FILE *arquivo, int yterminal, int xterminal, int yborda, int xborda) {

    int ContadorCiclos = 0;
    char StringAux[20];
    char StringAux1[20];

    while(arquivo != EOF) {
        
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
        
        sprintf(StringAux1, "Ciclo = %i", ContadorCiclos);
        mvwprintw(borda, (yborda - 7) / 2 + 6, (xborda - strlen(StringAux1)) / 2, StringAux1);
        
        mvwprintw(borda, (yborda - 7) / 2 + 13, (xborda - strlen("Pressione qualquer tecla para o proximo ciclo")) / 2, "Pressione qualquer tecla para o proximo ciclo");
        
        wborder(borda, '#', '#', '-', '-', '-', '-', '-', '-');
        wrefresh(borda);
        
        getch();

        LerArquivo(processador, caminhoarquivo, arquivo, yterminal, xterminal, yborda, xborda);

    }

    return;

}

void LerArquivo(Processador *processador, char *caminhoarquivo, FILE *arquivo, int yterminal, int xterminal, int yborda, int xborda) {

    int resultadoleitura;

    noecho();
    cbreak();

    fscanf(arquivo, "%x: ", processador->programcounter);
     
    while(arquivo != EOF) {

        fscanf(arquivo, "%x ", &resultadoleitura);

        switch(resultadoleitura) {

            case 0xA9:  //LDA

            break;

        }

    }

    return;

}
