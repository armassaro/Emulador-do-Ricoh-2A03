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

void LerArquivo(Processador *processador, char *caminhoarquivo, FILE *arquivobin, int yterminal, int xterminal);

uint8_t ram[0x07D0]; //declaração da memória ram com 4kb de armazenamento

int main() {
    
    Processador processador;
    initscr();
    cbreak();
    noecho();
    curs_set(FALSE);
    processador.programcounter = 0x0600;  //valor inicial do program counter

    int xterminal;
    int yterminal;
    char caminhoarquivo[100]; //string que indica o nome ou o caminho do arquivo binário
    FILE *arquivobinario;

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

    mvwprintw(borda,yterminal / 2 - 8, xterminal / 2 - 18, " _                __  _  _ __ \n");
    mvwprintw(borda, yterminal / 2 - 7, xterminal / 2 - 18, "|_) o  _  _ |_     _)|_|/ \\__)\n");
    mvwprintw(borda, yterminal / 2 - 6, xterminal / 2 - 18, "| \\ | (_ (_)| |   /__| |\\_/__)\n");

    wrefresh(borda);

    wborder(borda, '#', '#', '-', '-', '-', '-', '-', '-');
    wrefresh(borda);

    WINDOW *menu = newwin(10, 15, yterminal / 2 + 1, xterminal / 2 - 6);
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
                refresh();

                WINDOW *JanelaString = newwin(1, xterminal - 5, yterminal / 2, 6);
                keypad(JanelaString, TRUE);

                clear();
                refresh();

                setbuf(stdin, NULL);
                wprintw(JanelaString, "Digite o caminho do arquivo binário: ");
                curs_set(TRUE);
                wmove(JanelaString, 1, 40);

                refresh();
                wgetstr(JanelaString, caminhoarquivo);
                // caminhoarquivo[strcspn(caminhoarquivo, "\n")] = '\0';
                setbuf(stdin, NULL);

                arquivobinario = fopen(caminhoarquivo, "rb");
                if(arquivobinario == NULL) {

                    clear();
                    refresh();

                    curs_set(FALSE);

                    mvprintw(yterminal / 2, xterminal / 2 - 28, "Erro na abertura de arquivo! Pressione qualquer tecla.\n");
                    refresh();
                    getch();

                    endwin();
                    return 1;

                }
                else { 

                    mvprintw(yterminal / 2 - 2, xterminal / 2, "Sucesso na abertura do arquivo!");

                }

                LerArquivo(&processador, caminhoarquivo, arquivobinario, yterminal, xterminal);

            }

            break;

    }
}

FIM:

    endwin();

    return 0;
}

void LerArquivo(Processador *processador, char *caminhoarquivo, FILE *arquivobin, int yterminal, int xterminal) {

    int resultadoleitura;

    noecho();
    cbreak();

    while(arquivobin != EOF) {

        fread(&resultadoleitura, sizeof(int), 8, arquivobin);

        if(resultadoleitura == LDA) {

            clear();
            refresh();

            mvprintw(yterminal / 2, xterminal / 2, "LDA");
            refresh();
            getch();

        }

    }

    return;

}
