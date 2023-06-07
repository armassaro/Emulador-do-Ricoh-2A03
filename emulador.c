#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <ncurses.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>
#include "instrucoes6502.h"

typedef struct {

    uint8_t acumulador;  //valores iniciais para os registradores
    uint8_t indicex;
    uint8_t indicey;
    uint8_t stackpointer;
    uint8_t statusregister;
    uint16_t programcounter;
    int carry;

} Processador;

uint8_t bus[0xFFFF]; //declara um array de 64 kb

void bus_write(uint16_t enderecopc, uint8_t enderecoinstrucao);//escrever da memoria

void instrucaoLDA(Processador processador){
    
    processador.programcounter = 0x0600;  //pega o valor inicial de program counter

    bus_write(0x0600, 0xA9); // LDAbus_write(0x0601, 0x00); // 0x00

    return;

}

void bus_write(uint16_t enderecopc, uint8_t enderecoinstrucao) {

    
}

int main() {
    
    Processador processador;
    initscr();
    cbreak();
    noecho();
    curs_set(FALSE);
    processador.programcounter = 0x0600;

    int xterminal;
    int yterminal;

    getmaxyx(stdscr, yterminal, xterminal);

    mvprintw(yterminal / 2, xterminal / 2 - 4, "Carregando...\n");
    mvprintw((yterminal / 2) - 2, 2, "[");
    mvprintw((yterminal / 2) - 2, xterminal - 2, "]");
    refresh();

    for(int a = 4; a <= xterminal - 4; a++) {  //tela de carregamento

        mvprintw((yterminal / 2) - 2, a, ">");
        
        refresh();
        usleep(20000);

        mvprintw((yterminal / 2) - 2, a, "|");

        refresh();

        usleep(5000);

    }

    for(int a = 4; a <= xterminal - 4; a++) {  //preenche risco com hashtag

        mvprintw((yterminal / 2) - 2, a, "#");
        
        refresh();

        usleep(6000);

    }

    clear();

    mvprintw((yterminal / 2) - 2, xterminal / 2, "#");

    for(int a = yterminal / 2; a <= yterminal - 4; a++) {  //move um asterisco centralizado pra baixo

        mvprintw(a, xterminal / 2, "#");
        
        refresh();

        usleep(10000);

        clear();

    }

    for(int a = xterminal / 2; a <= xterminal - 4; a++) {  //move o asterisco pra direita

        mvprintw(yterminal - 4, a, "#");
        
        refresh();

        usleep(10000);

        clear();

    }

    for(int a = yterminal - 4; a >= 4; a--) {  //sobe e preenche coluna direita

        mvprintw(a, xterminal - 4, "#");
        
        refresh();

        usleep(10000);

    }

    for(int a = xterminal - 4; a >= 4; a--) {  //vai pra esquerda e preenche linha de cima

        mvprintw(4, a, "-");
        refresh();

        usleep(10000);

    }

    for(int a = 5; a <= yterminal - 4; a++) {  //preenche coluna esquerda

        mvprintw(a, 4, "#");
        
        refresh();

        usleep(10000);

    }

    for(int a = 4; a <= xterminal - 4; a++) {  //preenche linha inferior

        mvprintw(yterminal - 4, a, "-");
        refresh();

        usleep(10000);

    }
    WINDOW *borda = newwin(yterminal - 7, xterminal - 7, 4, 4);

    mvwprintw(borda,yterminal / 2 - 8, xterminal / 2 - 18, " _                __  _  _ __ \n");
    mvwprintw(borda, yterminal / 2 - 7, xterminal / 2 - 18, "|_) o  _  _ |_     _)|_|/ \\__)\n");
    mvwprintw(borda, yterminal / 2 - 6, xterminal / 2 - 18, "| \\ | (_ (_)| |   /__| |\\_/__)\n");

    wrefresh(borda);

    wborder(borda, '#', '#', '-', '-', '-', '-', '-', '-');
    wrefresh(borda);

    WINDOW *menu = newwin(10, 15, yterminal / 2 + 1, xterminal / 2 - 6);
    refresh();

    char *menuopcoes[] = {"Printa", "Sair", "botafogo", "flamengo"};
    int opcoes = sizeof(menuopcoes) / sizeof(*menuopcoes);
    int opcao;
    int highlight = 0;

// Habilitar captura de teclas especiais
keypad(menu, TRUE);

// Loop principal do menu
while (1) {
    // Limpar a janela e imprimir as opções do menu
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

    // Capturar a tecla pressionada
    opcao = wgetch(menu);

    // Processar a tecla pressionada
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

        case '\n':  // Tecla Enter
            // Realizar a ação correspondente à opção selecionada
            if (highlight == 0) {

                clear();
                refresh();
                mvprintw(yterminal / 2, xterminal / 2, "fodase");
                curs_set(FALSE);
                getch();
                endwin();
                goto FIM;

            }
            // Coloque aqui o código para realizar a ação desejada para cada opção
            break;
    }
}

FIM:

    endwin();

    return 0;
}