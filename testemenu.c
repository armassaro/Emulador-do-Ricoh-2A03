#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <stdint.h>
#include <string.h>

int main() {

    initscr();
    cbreak();
    noecho();
    curs_set(FALSE);

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

    WINDOW *menu = newwin(yterminal - 7, xterminal - 7, 4, 4);

    int xmenu, ymenu;

    char *stringlogopt1 = "  __                                                             \n";
    char *stringlogopt2 = " (_ _|_ ._ _   _. ._ _  o ._   _    |\\/|  _. ._   _.  _   _  ._ \n";
    char *stringlogopt3 = " __) |_ | (/_ (_| | | | | | | (_|   |  | (_| | | (_| (_| (/_ |   \n";
    char *stringlogopt4 = "                               _|                     _|         \n";

    getmaxyx(menu, ymenu, xmenu);

    mvwprintw(menu, ymenu / 2 - 7, xmenu / 2 - 30, "%s", stringlogopt1);
    mvwprintw(menu, ymenu / 2 - 6, xmenu / 2 - 30, "%s", stringlogopt2);
    mvwprintw(menu, ymenu / 2 - 5, xmenu / 2 - 30, "%s", stringlogopt3);
    mvwprintw(menu, ymenu / 2 - 4, xmenu / 2 - 30, "%s", stringlogopt4);

    wrefresh(menu);

    wborder(menu, '#', '#', '-', '-', '-', '-', '-', '-');

    wrefresh(menu);

    WINDOW *menuopcoes = newwin(10, 15, yterminal / 2 + 1, xterminal / 2 - 5);
    refresh();

    char *menuescolhas[] = {"Iniciar", "Sair"};
    int opcoes = 2;
    int opcao;
    int highlight = 0;
    keypad(menuopcoes, TRUE);

    werase(menuopcoes);

    while(1) {

        for(int a = 0; a < opcoes; a++) {

            if(a == highlight) {

                wattron(menuopcoes, A_REVERSE);

            }

            int x = (15 - strlen(menuescolhas[a])) / 2;
            mvwprintw(menuopcoes, a + 1, x, "%s", menuescolhas[a]);
            wattroff(menuopcoes, A_REVERSE);

        }

        wborder(menuopcoes, '#', '#', '-', '-', '-', '-', '-', '-');

        wrefresh(menuopcoes);

        opcao = wgetch(menuopcoes);
        switch(opcao) {

            case KEY_UP:
            highlight--;
            if(highlight < 0) {

                highlight = 0;

            }
            break;

            case KEY_DOWN:
            highlight++;
            if(highlight >= opcoes) {

                highlight = opcoes - 1;

            }
            break;

            case '\n': 
            if (highlight == 0) {

                clear();
                refresh();
                mvprintw(yterminal / 2, xterminal / 2, "fodase");
                curs_set(FALSE);
                getch();
                endwin();
                goto FIM;

            }
            if(highlight == 1) {

                return 0;

            }
            break;
        }

    }

    FIM:

    curs_set(TRUE);

    endwin();

    return 0;

}