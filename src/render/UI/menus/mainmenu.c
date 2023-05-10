#include "mainmenu.h"
#include "util/ncurses.h"
#include "../../render.h"
#include <stdlib.h>

#define BOTOES 4
#define LARGURA_CAGE 56
#define ALTURA_CAGE 31

static char *cage[ALTURA_CAGE] = {
        "                        .#     &                       ",
        "                       #         #                     ",
        "                       /         #                     ",
        "                       .(  ##/  #                      ",
        "                          (&##.                        ",
        "                           *&,                         ",
        "                 .&#################&.                 ",
        "            #.# #  #  #    #    (  #  & #.#            ",
        "         & # .   #   /     #     .   #  ,  # #         ",
        "       # #  #   &          #     *    #   #  & #       ",
        "     *     *   #    #      #      ,    #   #  *        ",
        "    *  .  #    .    #      #      #    .    #  (  .    ",
        "    , #       ,     /      #      #     .   .   ( (    ",
        "      #  .    (     .      &      (     /       &      ",
        "      #  .    (     .      #      (     /       #      ",
        "      #  .    (                         /       #      ",
        "      #  .    (            #            /       #      ",
        "      #  .    (                         /       #      ",
        "      #  .    (            #            /       #      ",
        "      #  .    (                         /       #      ",
        "      #  .    (            #            /       #      ",
        "      #  .    (                         /       #      ",
        "      #  .    (            #            /       #      ",
        "      #  .    (                         /       #      ",
        "      #  .    (            #            /       #      ",
        "      &  .    (                         /       #      ",
        "      #  .    (     .      #      (     /       #      ",
        "      #  .    (     .      #      (     /       #      ",
        "    &##############################################&   ",
        "  /##################################################/ ",
        "  &##################################################& "
};

static unsigned short int effect = 0, botao_selecionado_principal = 0;
static char *botoes[BOTOES] = {"menu.main.new_game", "menu.main.saves", "menu.main.options", "menu.main.quit_game"};



void drawMainMenu(Menu menu) {
    

    char *botaoMaior = tamanho_maxPalavra(BOTOES, botoes);
    unsigned short int tamanhoBotaoMaior = strlen(botaoMaior);


    /* Obter onde vai ser colocada a ASCII - Cage em xOy */

    unsigned short int x_cage = xMAX/2 - LARGURA_CAGE/2;
    unsigned short int y_cage = yMAX/2 - ALTURA_CAGE/3;


    /* Printer da ASCII - Cage */

    for(int i = 0 ; i < ALTURA_CAGE ; i++) {

        for(int j = 0 ; j < LARGURA_CAGE ; j++) {

            static unsigned short int pair = 0;

            switch(cage[i][j]) {
                case '&' : case '(' : case '/' : case '*' : pair = LIGHTPLUS_GREY_LOGO; break;
                default : pair = DARKPLUS_GREY_LOGO;
            }

            wattron(menu->wnd, COLOR_PAIR(pair));

            mvwprintw(menu->wnd, y_cage + i, x_cage + j, "%c", cage[i][j]);

            wattroff(menu->wnd, COLOR_PAIR(pair));
        }

    }


    /* Cria o retângulo à volta dos botões */
    
    rectangle(menu->wnd, 
              yMAX/2 + 5           , xMAX/2 - tamanhoBotaoMaior/2 - 1,
              yMAX/2 + 5 + BOTOES*2, xMAX/2 + tamanhoBotaoMaior/2 + (g_renderstate->language == en_US ? 1 : 0)
    );


    /* Print do logo */

    printer(menu->wnd, yMAX/4 - ALTURA_LOGO, xMAX/2 - LARGURA_LOGO/2);

    /* Print dos botões com effect A_REVERSE no que está selecionado 
     +1 necessário no mvwprintw, devido aos arredondamentos para o floor e +5 devido ao circulo no topo da ASCII ART */

    for(int i = 0, separador = 0 ; i < BOTOES ; i++, separador += 1) {

        if(i == effect) 
            wattron(menu->wnd, A_REVERSE);
        
        mvwprintw(menu->wnd, yMAX/2 + separador + i + 5 +1 , xMAX/2 - strlen(get_localized_string(g_renderstate->language, botoes[i]))/2, "%s", get_localized_string(g_renderstate->language, botoes[i]));

        if(i == effect)
            wattroff(menu->wnd, A_REVERSE);
            
    }

}

void tick_MainMenu() {
    return;
}

void handle_MainMenu_keybinds(int key) {


    if(botao_selecionado_principal == 0 && key == KEY_UP) {

        botao_selecionado_principal = BOTOES - 1;
        effect = BOTOES - 1;

        return;
    }

    if(botao_selecionado_principal == BOTOES-1 && key == KEY_DOWN) {

        botao_selecionado_principal = 0;
        effect = 0;

        return;
    }
    
    switch(key) {

        case KEY_UP :
            botao_selecionado_principal--;
            effect--;
            break;


        case KEY_DOWN :
            botao_selecionado_principal++;
            effect++;
            break;


        case 10 : case 13 : switch(botao_selecionado_principal) {

                            case 0 : 
                                closeMenu(MENU_MAIN_MENU);
                                // startGame(); cujo codigo seria, por exemplo, utilizar as funcoes: create_asylum; print_asylum; drawGameInterface();
                                create_asylum(g_renderstate->nrows - ALTURA_LOGO - 2, g_renderstate->ncols-2, ALTURA_LOGO+1, 1);
                                print_asylum(g_renderstate->nrows - ALTURA_LOGO - 2, g_renderstate->ncols-2, ALTURA_LOGO+1, 1);
                                drawGameInterface();
                                break;

                            case 1 : 
                                displayMenu(MENU_SAVE);
                                break; //saves

                            case 2 : 
                                displayMenu(MENU_OPTIONS); 
                                break;

                            case 3 : 
                                exit(0);
                                endwin();
                        }

    }
    
}