#include <SDL.h>
//? gcc src/main.c -o bin/prog -I include -L lib -lmingw32 -lSDL2main -lSDL2
//? gcc src/main.c -o bin/prog -I include -L lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image (avec jpeg, autres...)
//? gcc src/main.c -o bin/prog -I include -L lib -lmingw32 -lSDL2main -lSDL2 -mwindows (le terminal ne se lance pas)

#include <SDL_image.h>
#include <stdio.h>
#include <stdlib.h>

#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 630
#define FPS_LIMIT 16

void SDL_ExitWithError(const char *message);
void SDL_limitFPS(unsigned int limit);

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
    unsigned int frame_limit = 0; 

    /*
        FPS
        1000 / 30 = 33 
        1000 / 60 = 16 
    */

    frame_limit = SDL_GetTicks() + FPS_LIMIT;
    SDL_limitFPS(frame_limit);
    frame_limit = SDL_GetTicks() + FPS_LIMIT;

    while(program_launched){
        SDL_Event event;

        while(SDL_PollEvent(&event)){
            switch (event.type){
                

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

void SDL_limitFPS(unsigned int limit){
    unsigned int ticks = SDL_GetTicks();
    if(limit < ticks)
        return;
    else if(limit > ticks + FPS_LIMIT)
        SDL_Delay(FPS_LIMIT);
    else
        SDL_Delay(limit - ticks);
}