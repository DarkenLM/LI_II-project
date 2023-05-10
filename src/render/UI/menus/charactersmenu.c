#include "charactersmenu.h"
#include "util/ncurses.h"
#include "../../render.h"

#define BOTOES 3
#define CLASSES 3
#define ESPACAMENTO 2
#define TAMANHO_MAX_BOTAO 20
#define TAMANHO_MAX_CLASSE 20

static unsigned short int botao_selecionado_principal = 0, effect = 0;
static char *botoes[BOTOES] = {"menu.characters.priest", "menu.characters.detective", "menu.characters.mercenary"};




void drawCharactersMenu(Menu menu) {
    

    char *botaoMaior = tamanho_maxPalavra(BOTOES, botoes);
    unsigned short int tamanhoBotaoMaior = strlen(botaoMaior);

    static char *classeMessage = NULL;
    classeMessage = (g_renderstate->language == en_US) ? "Choose your Character Class:" : "Escolha a Classe do seu Jogador:";


    /* Print do logo */

    printer(menu->wnd, yMAX/4 - ALTURA_LOGO, xMAX/2 - LARGURA_LOGO/2);


    /* Print da frase para escolher a classe do personagem com effect A_UNDERLINE */

    wattron(menu->wnd, A_UNDERLINE);
    mvwprintw(menu->wnd, yMAX/3, xMAX/2 - strlen(classeMessage)/2 + 1, "%s", classeMessage);
    wattroff(menu->wnd, A_UNDERLINE);


    /* Cria o retângulo à volta das classes */

    rectangle(menu->wnd, 
              yMAX/3 + ESPACAMENTO           , xMAX/2 - tamanhoBotaoMaior/2 -1,
              yMAX/3 + ESPACAMENTO + BOTOES*2, xMAX/2 + tamanhoBotaoMaior/2 + (g_renderstate->language == en_US ? 1 : 0)
             );


    /* Print das classes com effect A_REVERSE no que está selecionado 
     +1 necessário no mvwprintw, devido aos arredondamentos para o floor */

    for(int i = 0, separador = 0 ; i < BOTOES ; i++, separador += 1) {

        if(i == effect) 
            wattron(menu->wnd, A_REVERSE);
        
        mvwprintw(menu->wnd, yMAX/3 + ESPACAMENTO + separador + i +1, xMAX/2 - strlen(get_localized_string(g_renderstate->language, botoes[i]))/2, "%s", get_localized_string(g_renderstate->language, botoes[i]));

        if(i == effect)
            wattroff(menu->wnd, A_REVERSE);
            
    }


    /* Criação da janela abaixo das classes para colocar a devida informação de cada classe */

        WINDOW *info = malloc(sizeof(WINDOW));
        info = newwin(
                      yMAX/3                             , xMAX/2, 
                      yMAX/3 + ESPACAMENTO + BOTOES*2 + 2, xMAX/4
        );

        /* Retângulo à volta da janela */

        box(info, 0, 0);


        /* Colocação do texto com a descrição de cada classe */         // !!!!!!

        wattron(info, A_BOLD | A_UNDERLINE);


        switch(botao_selecionado_principal) {
            
            case 0 : {
                mvwprintw(info, 1, 2, "%s", botoes[0]);
                wattroff(info, A_BOLD | A_UNDERLINE);
                // Print da descrição da class
                break;
            }
            
            case 1 : {
                mvwprintw(info, 1, 2, "%s", botoes[1]);
                wattroff(info, A_BOLD | A_UNDERLINE);
                // Print da descrição da class
                break;
            }
            
            case 2 : {
                mvwprintw(info, 1, 2, "%s", botoes[2]);
                wattroff(info, A_BOLD | A_UNDERLINE);
                // Print da descrição da class
                break;
            }

    }

        /* Atualização de ambas as janelas */

        wrefresh(menu->wnd);
        wrefresh(info);

}






void tick_CharactersMenu() {
    return;
}


void handle_CharactersMenu_keybinds(int key) {

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

                            case Priest : {
                                g_gamestate->player->entity->basedamage = 3;
                                g_gamestate->player->entity->class = Priest;
                                //startgame
                                break;            
                            }

                            case Detective : {
                                g_gamestate->player->entity->basedamage = 3;
                                g_gamestate->player->entity->class = Detective;
                                //startgame
                                break;             
                            }

                            case Mercenary : {
                                g_gamestate->player->entity->basedamage = 3;
                                g_gamestate->player->entity->class = Mercenary;
                                //startgame
                                break;             
                            }

                        }

    }



}