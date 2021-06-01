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

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

void SDL_ExitWithError(const char *message);

int main(int argc, char **argv){
    // creation pointer
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    

    // Lancement SDL
    if(SDL_Init(SDL_INIT_VIDEO) != 0)
        SDL_ExitWithError("Creation fenetre echouee");


    // Création fenêtre + rendu en même temps
    if (SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_HEIGHT, 0, &window, & renderer) != 0)
        SDL_ExitWithError("Impossible creer fenetre / rendu");

    //TODO Contenu de la page
    SDL_Surface *image = NULL;
    SDL_Texture *texture = NULL;

    image = SDL_LoadBMP("src/naruto.bmp");
    if (image == NULL){
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_ExitWithError("Impossible de charger l'image bg");
    }
    
    texture = SDL_CreateTextureFromSurface(renderer, image);
    SDL_FreeSurface(image);

    if (texture == NULL){
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_ExitWithError("Impossible de creer la texture");
    }

    SDL_Rect rectangle;

    if (SDL_QueryTexture(texture, NULL, NULL, &rectangle.w, &rectangle.h) != 0){
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_ExitWithError("Impossible de charger la texture");
    }

    rectangle.x = (WINDOW_WIDTH - rectangle.w) / 2;
    rectangle.y = (WINDOW_HEIGHT - rectangle.h) / 2;

    if (SDL_RenderCopy(renderer, texture, NULL, &rectangle) != 0){
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_ExitWithError("Impossible de d'afficher la texture");
    }

    SDL_RenderPresent(renderer);

    SDL_Delay(3000);

    // Fin contenu de page 

    SDL_DestroyTexture(texture);
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

