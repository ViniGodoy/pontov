/******************************************************************************
*
* COPYRIGHT Paulo V. W. Radtke ALL RIGHTS RESERVED.
*
* This software cannot be copied, stored, distributed without  
* Vinícius G.Mendonça prior authorization.
*
* This file was made available on http://www.pontov.com.br and it is free 
* to be restributed or used under Creative Commons license 2.5 br: 
* http://creativecommons.org/licenses/by-sa/2.5/br/
*
*******************************************************************************
* Este software nao pode ser copiado, armazenado, distribuido sem autorização 
* a priori de Paulo V. W. Radtke
*
* Este arquivo foi disponibilizado no site http://www.pontov.com.br e esta 
* livre para distribuição seguindo a licença Creative Commons 2.5 br: 
* http://creativecommons.org/licenses/by-sa/2.5/br/
*
******************************************************************************/
#include <stdlib.h>
#include <list>

#if	defined(linux)
	#include <SDL/SDL.h>
#else
	#include <SDL.h>
#endif

#include "Sprite.h"

#define WIDTH 800
#define HEIGHT 600

static SDL_Surface *pScreen_gl;    // Ponteiro para o bitmap

static void MainLoop()
{
	using namespace std;
	using namespace pontov;

	typedef list<SpritePtr_t> SpriteList_t;
	SpriteList_t sprites;
	
	bool exit = false;
    while(!exit)
    {     
		SDL_Event ev;

		while ( SDL_PollEvent(&ev) ) 
		{
			switch(ev.type)
			{
				case SDL_QUIT:
					exit = true;
					break;
				
				case SDL_KEYDOWN:
					if(ev.key.keysym.sym == SDLK_ESCAPE)
						exit = true;
					else if(ev.key.keysym.sym == SDLK_SPACE)
					{
						SpritePtr_t ptr(new Sprite_c(rand() % 2 ? "carro_verde.bmp" : "carro_azul.bmp", 0, 0));
						sprites.push_back(ptr);
					}
					break;
			}
		}

    	// Limpa a tela
    	SDL_FillRect(pScreen_gl, NULL, SDL_MapRGB(pScreen_gl->format, 255, 255, 255));

		for(SpriteList_t::iterator it = sprites.begin(), end = sprites.end(); it != end; ++it)
		{
			SpritePtr_t ptr(*it);

			ptr->SetPosX(ptr->GetPosX()+1);
			ptr->Blit(*pScreen_gl);

			if(ptr->GetPosX() > WIDTH)
			{
				it = sprites.erase(it);
				if(it == end)
					break;
			}
		}
                
        SDL_UpdateRect(pScreen_gl, 0, 0, 0, 0);
    }
}

int main(int argc, char *argv[])
{
	// Inicializa a SDL
    if ( SDL_Init(SDL_INIT_VIDEO) < 0 ) {
        fprintf(stderr, "Nao consegui inicializar a SDL: %s\n", SDL_GetError());
        exit(1);
    }    
	atexit(SDL_Quit);

    pScreen_gl = SDL_SetVideoMode(WIDTH, HEIGHT, 32, SDL_SWSURFACE);
    if ( pScreen_gl == NULL ) 
    {
        fprintf(stderr, "Falhou inicializacao do video: %s\n", SDL_GetError());
        exit(1);
    }    	

	MainLoop();

	exit(0);

    return 0; 
}


