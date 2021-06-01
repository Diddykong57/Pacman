#include <SDL.h>
//? gcc src/main.c -o bin/prog -I include -L lib -lmingw32 -lSDL2main -lSDL2
//? gcc src/main.c -o bin/prog -I include -L lib -lmingw32 -lSDL2main -lSDL2 -mwindows (le terminal ne se lance pas)

/*
    SDL_RENDERER_SOFTWARE (travail avec processeur)
    SDL_RENDERER_ACCELERATED (accélération matérielle -> carte graphique)
    SDL_RENDERER_PRESENTVSYNC (synchro verticale avec écran)
    SDL_RENDERER_TARGETTEXTURE (ciblage texture, faire le rendu)
*/

#include <stdio.h>
#include <stdlib.h>

void SDL_ExitWithError(const char *message);

int main(int argc, char **argv){
    // creation pointer
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    

    // Lancement SDL
    if(SDL_Init(SDL_INIT_VIDEO) != 0)
        SDL_ExitWithError("Creation fenetre echouee");

    //TODO Execution du programme...

    // Création fenêtre + rendu en même temps
    if (SDL_CreateWindowAndRenderer(800, 600, 0, &window, & renderer) != 0)
        SDL_ExitWithError("Impossible creer fenetre / rendu");

    // Contenu de la page
    if(SDL_SetRenderDrawColor(renderer, 112, 168, 237, SDL_ALPHA_OPAQUE) != 0)
        SDL_ExitWithError("Impossible de changer la couleur pur le rendu");

    if(SDL_RenderDrawPoint(renderer, 100, 450) != 0)
        SDL_ExitWithError("Impossible de dessiner un point");

    if(SDL_RenderDrawLine(renderer, 300, 300, 400, 200) != 0)
        SDL_ExitWithError("Impossible de dessiner une ligne");
    if(SDL_RenderDrawLine(renderer, 400, 200, 500, 300) != 0)
        SDL_ExitWithError("Impossible de dessiner une ligne");

    SDL_Rect rectangle;
    rectangle.x = 300;
    rectangle.y = 300;
    rectangle.w = 200;
    rectangle.h = 120;
    if(SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE) != 0)
        SDL_ExitWithError("Impossible de changer la couleur pour le rendu");

    // SDL_RenderFillRect  --> rempli le rectangle
    if(SDL_RenderDrawRect(renderer, &rectangle) != 0)
        SDL_ExitWithError("Impossible de dessiner un rectangle");

    SDL_Rect porte;
    porte.x = 370;
    porte.y = 370;
    porte.w = 40;
    porte.h = 50;

    if(SDL_RenderFillRect(renderer, &porte) != 0)
        SDL_ExitWithError("Impossible de dessiner la porte");

    SDL_RenderPresent(renderer);

    SDL_Delay(3000);


    if(SDL_SetRenderDrawColor(renderer, 51, 239, 255, SDL_ALPHA_OPAQUE) != 0)
        SDL_ExitWithError("Impossible de changer la couleur pour le rendu");
    //Nettoie l'écran
    // if(SDL_RenderClear(renderer))
    //     SDL_ExitWithError("Effacement rendu echouee");

    // Raffraichi le rendu

    if(SDL_RenderDrawRect(renderer, &rectangle) != 0)
        SDL_ExitWithError("Impossible de dessiner un rectangle");

    SDL_RenderPresent(renderer);
    SDL_Delay(3000);


    // Fin contenu de page 

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}

void SDL_ExitWithError(const char *message){
    SDL_Log("Erreur : %s > %s\n", message, SDL_GetError());
    SDL_Quit();
    exit(EXIT_FAILURE);
}

