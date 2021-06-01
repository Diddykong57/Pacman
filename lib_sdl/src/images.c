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


void clean_resources(SDL_Window *w, SDL_Renderer *r, SDL_Texture *t){
    if (t != NULL)
        SDL_DestroyTexture(t);
    if (r != NULL)
        SDL_DestroyRenderer(r);
    if (w != NULL)
        SDL_DestroyWindow(w);
    
    SDL_Quit();
}

void SDL_ExitWithError(const char *message);

int main(int argc, char **argv){
    // creation pointer
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Surface *image = NULL;
    SDL_Texture *texture = NULL;
    SDL_Rect dest_rect = {0,0,640,480};
    

    // Lancement SDL
    if(SDL_Init(SDL_INIT_VIDEO) != 0)
        SDL_ExitWithError("Creation fenetre echouee");


    // Création fenêtre + rendu en même temps
    if (SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_HEIGHT, 0, &window, & renderer) != 0)
        SDL_ExitWithError("Impossible creer fenetre / rendu");

    //TODO Contenu de la page

    image = IMG_Load("src/naruto_sasuke.jpg");
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

    if (SDL_QueryTexture(texture, NULL, NULL, &dest_rect.w, &dest_rect.h) != 0){
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_ExitWithError("Impossible de charger la texture");
    }

    dest_rect.x = (WINDOW_WIDTH - dest_rect.w) / 2;
    dest_rect.y = (WINDOW_HEIGHT - dest_rect.h) / 2;

    if (SDL_RenderCopy(renderer, texture, NULL, &dest_rect) != 0){
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_ExitWithError("Impossible de d'afficher la texture");
    }

    SDL_RenderPresent(renderer);
    SDL_Delay(3000);

    // Fin contenu de page 

    clean_resources(window, renderer, texture);

    return EXIT_SUCCESS;
}

void SDL_ExitWithError(const char *message){
    SDL_Log("Erreur : %s > %s\n", message, SDL_GetError());
    SDL_Quit();
    exit(EXIT_FAILURE);
}

