#include <SDL.h>
//? gcc src/main.c -o bin/prog -I include -L lib -lmingw32 -lSDL2main -lSDL2
//? gcc src/main.c -o bin/prog -I include -L lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image (avec jpeg, autres...)
//? gcc src/main.c -o bin/prog -I include -L lib -lmingw32 -lSDL2main -lSDL2 -mwindows (le terminal ne se lance pas)

/*
    SDL_RENDERER_SOFTWARE (travail avec processeur)
    SDL_RENDERER_ACCELERATED (accélération matérielle -> carte graphique)
    SDL_RENDERER_PRESENTVSYNC (synchro verticale avec écran)
    SDL_RENDERER_TARGETTEXTURE (ciblage texture, faire le rendu)
*/
#include <SDL_image.h>
#include <stdio.h>
#include <stdlib.h>

#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 630

void SDL_ExitWithError(const char *message);

int main(int argc, char **argv){
    // creation pointer
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    

    // Lancement SDL
    if(SDL_Init(SDL_INIT_VIDEO) != 0)
        SDL_ExitWithError("Creation fenetre echouee");


    // Création fenêtre + rendu
    if (SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_HEIGHT, 0, &window, & renderer) != 0)
        SDL_ExitWithError("Impossible creer fenetre / rendu");

    //TODO Contenu de la page

    SDL_bool program_launched = SDL_TRUE;

    while(program_launched){
        SDL_Event event;

        while(SDL_PollEvent(&event)){
            switch (event.type){
                /*
                    SDL_BUTTON_LEFT
                    SDL_BUTTON_MIDDLE
                    SDL_BUTTON_RIGHT
                */
                case SDL_MOUSEBUTTONDOWN:
                    // event.motion.x (coord x souris) ou xrel (position relative)
                     printf("Clic coord(%d,%d)\n", event.button.x, event.motion.y);
                    if (event.button.clicks >= 2)
                        printf("Double-clic poto !\n");
                    break;

                case SDL_MOUSEMOTION:
                    //printf("(%d,%d)\n", event.motion.x, event.motion.y);
                    break;

                case SDL_QUIT:
                    program_launched = SDL_FALSE;
                    break;
                
                default:
                    break;
            }
        }
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    // Fin contenu de page 

    return EXIT_SUCCESS;
}

void SDL_ExitWithError(const char *message){
    SDL_Log("Erreur : %s > %s\n", message, SDL_GetError());
    SDL_Quit();
    exit(EXIT_FAILURE);
}

